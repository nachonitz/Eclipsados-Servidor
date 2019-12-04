#include "cliente.h"
#include "servidor.h"
#include <pthread.h>
#include "modelo/Juego.h"
#include "modelo/nivel/Nivel.h"
#include <queue>
#include <string>
#include "ParserXML.h"
#include <map>

std::map<std::string, std::string> usuarios;

vector<Cliente*> clientes;
Servidor servidor;


int clientNumbers[] = {0,1,2,3};
int cantDesconectados = 0;
int cantClientes = 0;	// se leera del XML
int midGame = 0;

pthread_t hiloSendBroadcast[4];
pthread_t hiloDesconexionJugadores;
pthread_t hiloRecieveMessage[4];
pthread_t hiloValidarCredenciales[4];
pthread_t hiloTimer[4];
pthread_t procesarInformacion;
pthread_mutex_t mutexNivel;

pthread_t hiloMidGameConnects[CANT_HILOS_RECONEXION];


Juego* juego;
//pthread_mutex_t mutexProcesar							// ya no haria falta porque hay un solo thread modificando el juego
pthread_mutex_t mutexQueue;
pthread_mutex_t mutexPushCliente;
pthread_mutex_t mutexTimer[4];
pthread_mutex_t mutexDesconexion[4];

queue <struct informacionRec> colaInfoDeClientes;

int tiempoEsperaSend[4];
bool matarHilo[4] = {false, false, false, false};


void* timer(void*arg){
	int * arg_ptr = (int*)arg;
	int numberOfClient = *arg_ptr;
	Logger::getInstance()->log(DEBUG, "Hilo Timer creado " + std::to_string(numberOfClient));
	while (tiempoEsperaSend[numberOfClient] <= 5){
		sleep(1);
		pthread_mutex_lock(&mutexTimer[numberOfClient]);
		tiempoEsperaSend[numberOfClient] ++;
		pthread_mutex_unlock(&mutexTimer[numberOfClient]);
	}
	Logger::getInstance()->log(ERROR, "Tiempo de espera maximo alcanzado. Desconcetando al Jugador " + std::to_string(numberOfClient));
	juego->desconexionDeJugador(numberOfClient);
	matarHilo[numberOfClient] = true;
}

void* procesar_info(void*arg){
	bool cambioNivel = false;
	while(1){
		// vaciar TODA la cola y procesar toda la info
		//Logger::getInstance()->log(DEBUG, "Procesando datos recibidos.");
		pthread_mutex_lock(&mutexQueue);				//<-- creeria que, en rigor, deberian ir esos mutex pero no estoy seguro
		while (!colaInfoDeClientes.empty()) {
			struct informacionRec info = colaInfoDeClientes.front();
			juego->procesarInfo(info);
			colaInfoDeClientes.pop();
		}

		// actualizar modelo
		juego->moverEnemigos();
		juego->actualizarAnimaciones();
		pthread_mutex_unlock(&mutexQueue);


		pthread_mutex_lock(&mutexNivel);
		cambioNivel = juego->chequearCambioDeNivel();
		pthread_mutex_unlock(&mutexNivel);

		if(cambioNivel){
			cambioNivel = false;
			sleep(8);
		}

		SDL_Delay(FRAME_DELAY);
	}

		//Logger::getInstance()->log(DEBUG, "Obteniendo informacion actual del modelo.");
}

void* message_send(void*arg){
	int * arg_ptr = (int*)arg;
	int numberOfClient = *arg_ptr;
	while(!matarHilo[numberOfClient]){

		// enviar
		struct informacionEnv info = juego->getInformacion();
		//Logger::getInstance()->log(DEBUG, "Enviando info a clientes...");


		if (juego->jugadorConectado(numberOfClient)) {

			//Logger::getInstance()->log(DEBUG, "Enviando informacion a jugador conectado: " + std::to_string(i));

			int resultSend = servidor.sendInfo(clientes[numberOfClient]->getSocket(),info);

			if (resultSend <= 0) {
				juego->desconexionDeJugador(numberOfClient);
				Logger::getInstance()->log(INFO, "Jugador " + std::to_string(numberOfClient) + " desconectado! Nombre: " + clientes[numberOfClient]->getUsuario());
				matarHilo[numberOfClient] = true;
			}
			else
				juego->conexionDeJugador(numberOfClient);
		}

		SDL_Delay(FRAME_DELAY);
	}
}

void* message_recieve(void*arg){
	int * arg_ptr = (int*)arg;
	int numberOfClient = *arg_ptr;
	/*tiempoEsperaSend[numberOfClient] = 0;
	pthread_create(&hiloTimer[numberOfClient],NULL,timer,&numberOfClient);*/
	while(!matarHilo[numberOfClient]){
		//Logger::getInstance()->log(DEBUG, "Recibiendo informacion del cliente numero " + to_string(numberOfClient) + ".");

		struct informacionRec infoRecv = clientes[numberOfClient]->recieveInfo();

		if (!juego->jugadorConectado(numberOfClient)) {
			matarHilo[numberOfClient] = true;
			break;
		}

		if (infoRecv.numeroDeCliente >= 0) {

			infoRecv.numeroDeCliente = numberOfClient;

			pthread_mutex_lock(&mutexQueue);
			colaInfoDeClientes.push(infoRecv);
			pthread_mutex_unlock(&mutexQueue);
		}

		pthread_mutex_lock(&mutexTimer[numberOfClient]);
		tiempoEsperaSend[numberOfClient] = 0;
		pthread_mutex_unlock(&mutexTimer[numberOfClient]);

	}
}

void* manageMidGameConnects(void* arg) {

	struct credencial credencialesCliente;

	Cliente* cliente = new Cliente(&servidor);

	midGame ++;

	pthread_create(&hiloMidGameConnects[midGame],NULL,manageMidGameConnects,0);

	Logger::getInstance()->log(INFO, "Cliente conectado a medio juego! Pidiendo credenciales");

	while(!credencialesCliente.credencialValida){
		credencialesCliente = cliente->recieveCredentials();
		servidor.verificarCredenciales(&credencialesCliente, usuarios);

		for(int i = 0; i < cantClientes; i++){
			if(clientes[i]->tieneEstasCredenciales(credencialesCliente)){
				if(!juego->jugadorConectado(i)){
					credencialesCliente.myID = clientes[i]->getIDx();
				}
				else{
					credencialesCliente.credencialValida = false;
				}
			}
		}

		Logger::getInstance()->log(DEBUG, "ENVIANDO RESULTADO DE VERIFICACION: " + std::to_string(credencialesCliente.credencialValida));
		send(cliente->getSocket(), &credencialesCliente, sizeof(struct credencial), MSG_NOSIGNAL);
	}

	cliente->assignCredentials(credencialesCliente);

	bool noMandoNada = true;

	for (int i = 0; i < clientes.size(); i++) {


		Logger::getInstance()->log(DEBUG, "chequeando si algun cliente viejo toma su lugar...");

		Logger::getInstance()->log(DEBUG, "Viendo jugador si conectado: " + std::to_string(juego->jugadorConectado(i)));

		if (clientes[i]->tieneEstasCredenciales(credencialesCliente) && !juego->jugadorConectado(i)) {
			Logger::getInstance()->log(DEBUG, "ENCONTRADO CLIENTE VIEJO! ");
			delete clientes[i];
			clientes[i] = cliente;
			tiempoEsperaSend[i] = 0;
			noMandoNada = true;
			matarHilo[i] = false;
			send(cliente->getSocket(), &noMandoNada, sizeof(bool), 0);
			juego->conexionDeJugador(i);
			pthread_create(&hiloRecieveMessage[i],NULL,message_recieve,&clientNumbers[i]);
			pthread_create(&hiloSendBroadcast[i],NULL,message_send,&clientNumbers[i]);
			pthread_mutex_init(&mutexTimer[i],NULL);
			pthread_create(&hiloTimer[i],NULL,timer,&clientNumbers[i]);
			tiempoEsperaSend[i] = 0;
			break;
		}

		noMandoNada = false;

	}

	if (!noMandoNada)
		send(cliente->getSocket(), &noMandoNada, sizeof(bool), 0);

}

void* validateCredentials(void*arg){
	while (1){
		int * arg_ptr = (int*)arg;
		int numberOfClient = *arg_ptr;
		struct credencial credencialesCliente;
		credencialesCliente.credencialValida = false;

		Cliente* cliente = new Cliente(&servidor);
		pthread_mutex_lock(&mutexPushCliente);
		clientes.push_back(cliente);
		numberOfClient= clientes.size()-1;
		pthread_mutex_unlock(&mutexPushCliente);

		Logger::getInstance()->log(INFO, "Cliente numero " + to_string(clientes.size()) + " conectado.");
		int enviado;
		while(!credencialesCliente.credencialValida){
			credencialesCliente = clientes[numberOfClient]->recieveCredentials();
			servidor.verificarCredenciales(&credencialesCliente, usuarios);

			credencialesCliente.myID = numberOfClient;

			//VERIFICO QUE NO SE CONECTE OTRO CON EL MISMO USUARIO
			for (int i = 0; i<clientes.size();i++){
				if (i == numberOfClient){
					continue;
				}
				if (clientes[i]->tieneEstasCredenciales(credencialesCliente)){
					credencialesCliente.credencialValida = false;
				}
			}
			Logger::getInstance()->log(DEBUG, "ENVIANDO RESULTADO DE VERIFICACION: " + std::to_string(credencialesCliente.credencialValida));
			enviado = send(clientes[numberOfClient]->getSocket(), &credencialesCliente, sizeof(struct credencial), 0);
			if (enviado <= 0){
				break;
			}
		}
		if (enviado <= 0){
			pthread_mutex_lock(&mutexPushCliente);
			clientes.pop_back();
			pthread_mutex_unlock(&mutexPushCliente);
			Logger::getInstance()->log(ERROR, "Cliente desconectado en pantalla de inicio sin loggearse.");
			continue;
		}else{
			Logger::getInstance()->log(INFO, "Se conecto con credenciales el cliente " + std::to_string(numberOfClient));
			clientes[numberOfClient]->assignCredentials(credencialesCliente);
			break;
		}

	}

}

void* desconexion_jugadores(void*arg){

	while(1){
		cantDesconectados = 0;

		pthread_mutex_lock(&mutexNivel);

		for(int i = 0; i < cantClientes; i++){
			if(!juego->jugadorConectado(i)){
				cantDesconectados ++;
			}
		}

		pthread_mutex_unlock(&mutexNivel);

		if(cantDesconectados == cantClientes){
			Logger::getInstance()->log(INFO, "Todos los jugadores desconectados, apagando servidor...");
			printf("All Players Disconnected\n");
			printf("Server Shutting Down\n");
			exit(0);
		}
	}
}


int main(int argc, char *argv[]) {

	std::string customXmlPath = "xmlServerCustom.xml";

	Logger::getInstance()->createLogFile();

	Logger::getInstance()->setLevel(DEBUG);

	int cantCuchillos = 0, cantBarriles = 0, cantEnemigos = 0, cantCanios = 0, cantCajas = 0;

	ParserXML parser(customXmlPath);

	parser.parsearConfig(&cantEnemigos, &cantCuchillos, &cantCajas, &cantCanios, &cantBarriles, &cantClientes, usuarios);

	Logger::getInstance()->log(DEBUG, "Creando modelo...");

	juego = new Juego(cantCuchillos, cantCajas, cantCanios, cantBarriles, cantEnemigos,cantClientes);

	servidor.setPort(argv[1]);

	Logger::getInstance()->log(DEBUG, "Inicializar MUTEX en main.");

	pthread_mutex_init(&mutexQueue,NULL);
	pthread_mutex_init(&mutexPushCliente,NULL);
	pthread_mutex_init(&mutexNivel,NULL);

	//-> Comienzo hilos para el loggin
	for (int i = 0; i < cantClientes; i++) {
		pthread_create(&hiloValidarCredenciales[i],NULL,validateCredentials,&clientNumbers[i]);
	}

	//Espera a que todos se registren
	for (int i = 0; i < cantClientes; i++) {
		pthread_join(hiloValidarCredenciales[i],NULL);
	}

	std::string nombres [MAX_CLIENTES];
	for (int i = 0; i < cantClientes; i++) {
		nombres[i] = clientes[i]->getUsuario();
	}
	juego->setNombresUsuario(nombres, cantClientes);

	//Espera 2 segundos para que al ultimo logeado le muestre el personaje
	sleep(2);

	bool noMandoNada = true;
	for(int i =0 ; i< cantClientes; i++){
		send(clientes[i]->getSocket(), &noMandoNada, sizeof(bool), 0);
	}


	//-> Comienzo hilos de juego
	pthread_create(&procesarInformacion,NULL,procesar_info,NULL);

	for (int i = 0; i < cantClientes; i++) {
		pthread_create(&hiloSendBroadcast[i],NULL,message_send,&clientNumbers[i]);
	}
	pthread_create(&hiloDesconexionJugadores,NULL,desconexion_jugadores,NULL);

	for (int i = 0; i < cantClientes; i++) {
		pthread_mutex_init(&mutexTimer[clientNumbers[i]],NULL);
		pthread_create(&hiloTimer[i],NULL,timer,&clientNumbers[i]);
		pthread_create(&hiloRecieveMessage[i],NULL,message_recieve,&clientNumbers[i]);
		tiempoEsperaSend[clientNumbers[i]] = 0;
	}

	pthread_create(&hiloMidGameConnects[midGame],NULL,manageMidGameConnects,0);

	Logger::getInstance()->log(DEBUG, "Inicializar JOIN en main.");

	for (int i = 0; i < cantClientes; i++) {
		pthread_join(hiloSendBroadcast[i],NULL);
	}
	pthread_join(hiloDesconexionJugadores,NULL);

	for (int i = 0; i < cantClientes; i++) {
		pthread_join(hiloRecieveMessage[i],NULL);
	}

	delete Logger::getInstance();

	return 0;
}


