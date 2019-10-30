#include "cliente.h"
#include "servidor.h"
#include <pthread.h>
#include "modelo/Juego.h"
#include "modelo/nivel/Nivel.h"
#include <queue>

#include "ParserXML.h"

#include <map>

std::map<std::string, std::string> usuarios;

vector<Cliente*> clientes;
char mensaje[1000], client_reply[1000];
Servidor servidor;

//pthread_mutex_t mutex;
//pthread_mutex_init(&mutex,NULL);
int clientNumbers[] = {0,1,2,3};

int cantClientes = 2;

pthread_t hiloSendBroadcast;
pthread_t hiloRecieveMessage[4];
pthread_t hiloValidarCredenciales[4];

pthread_t hiloMidGameConnects[CANT_HILOS_RECONEXION];


Juego* juego;
//pthread_mutex_t mutexProcesar							// ya no haria falta porque hay un solo thread modificando el juego
pthread_mutex_t mutexQueue;
pthread_mutex_t mutexPushCliente;

queue <struct informacionRec> colaInfoDeClientes;


void* message_send(void*arg){
	while(1){

		// vaciar TODA la cola y procesar toda la info
		//Logger::getInstance()->log(DEBUG, "Procesando datos recibidos.");
		pthread_mutex_lock(&mutexQueue);				//<-- creeria que, en rigor, deberian ir esos mutex pero no estoy seguro
		while (!colaInfoDeClientes.empty()) {
			struct informacionRec info = colaInfoDeClientes.front();
			juego->procesarInfo(info);
			colaInfoDeClientes.pop();
		}
		pthread_mutex_unlock(&mutexQueue);

		// actualizar modelo
		juego->moverEnemigos();
		juego->actualizarAnimaciones();
		juego->chequearCambioDeNivel();

		//Logger::getInstance()->log(DEBUG, "Obteniendo informacion actual del modelo.");

		// enviar
		struct informacionEnv info = juego->getInformacion();

		//Logger::getInstance()->log(DEBUG, "Enviando info a clientes...");

		for (int i = 0; i < cantClientes; i++) {

			if (juego->jugadorConectado(i)) {

				Logger::getInstance()->log(DEBUG, "Enviando informacion a jugador conectado: " + std::to_string(i));

				int resultSend = servidor.sendInfo(clientes[i]->getSocket(),info);

				if (resultSend <= 0)
					juego->desconexionDeJugador(i);
				else
					juego->conexionDeJugador(i);
			}
		}
		SDL_Delay(1000/60);
	}
}

void* message_recieve(void*arg){
	int * arg_ptr = (int*)arg;
	int numberOfClient = *arg_ptr;
	while(1){
		//Logger::getInstance()->log(DEBUG, "Recibiendo informacion del cliente numero " + to_string(numberOfClient) + ".");

		struct informacionRec infoRecv = clientes[numberOfClient]->recieveInfo();

		if (infoRecv.numeroDeCliente >= 0) {

			infoRecv.numeroDeCliente = numberOfClient;

			pthread_mutex_lock(&mutexQueue);
			colaInfoDeClientes.push(infoRecv);
			pthread_mutex_unlock(&mutexQueue);
		}

/*		if (!juego->jugadorConectado(numberOfClient)) {
			//close(clientes[numberOfClient]->getSocket());
			//break;
		}*/
	}
}

void* manageMidGameConnects(void* arg) {

	struct credencial credencialesCliente;

	Cliente* cliente = new Cliente(&servidor);

	Logger::getInstance()->log(INFO, "Cliente conectado a medio juego! Pidiendo credenciales");

	while(!credencialesCliente.credencialValida){
		credencialesCliente = cliente->recieveCredentials();
		servidor.verificarCredenciales(&credencialesCliente, usuarios);

		//credencialesCliente.myIdx = numberOfClient;

		Logger::getInstance()->log(DEBUG, "ENVIANDO RESULTADO DE VERIFICACION: " + std::to_string(credencialesCliente.credencialValida));
		send(cliente->getSocket(), &credencialesCliente, sizeof(struct credencial), 0);
	}

	cliente->assignCredentials(credencialesCliente);

	bool noMandoNada = true;

	for (int i = 0; i < clientes.size(); i++) {


		Logger::getInstance()->log(DEBUG, "chequeando si algun cliente viejo toma su lugar...");

		Logger::getInstance()->log(DEBUG, "Viendo jugador si conectado: " + std::to_string(juego->jugadorConectado(i)));

		if (clientes[i]->tieneEstasCredenciales(credencialesCliente) && !juego->jugadorConectado(i)) {
			Logger::getInstance()->log(DEBUG, "ENCONTRADO CLIENTE VIEJO! ");
			clientes[i] = cliente;
			noMandoNada = true;
			send(cliente->getSocket(), &noMandoNada, sizeof(bool), 0);
			juego->conexionDeJugador(i);
			break;
		}

		noMandoNada = false;

	}

	if (!noMandoNada)
		send(cliente->getSocket(), &noMandoNada, sizeof(bool), 0);

}

void* validateCredentials(void*arg){
	int * arg_ptr = (int*)arg;
	int numberOfClient = *arg_ptr;
	struct credencial credencialesCliente;

	Cliente* cliente = new Cliente(&servidor);
	pthread_mutex_lock(&mutexPushCliente);
	clientes.push_back(cliente);
	pthread_mutex_unlock(&mutexPushCliente);

	Logger::getInstance()->log(INFO, "Cliente numero " + to_string(clientes.size()) + " conectado.");

	while(!credencialesCliente.credencialValida){
		credencialesCliente = clientes[numberOfClient]->recieveCredentials();
		servidor.verificarCredenciales(&credencialesCliente, usuarios);

		credencialesCliente.myIdx = numberOfClient;

		Logger::getInstance()->log(DEBUG, "ENVIANDO RESULTADO DE VERIFICACION: " + std::to_string(credencialesCliente.credencialValida));
		send(clientes[numberOfClient]->getSocket(), &credencialesCliente, sizeof(struct credencial), 0);
	}

	clientes[numberOfClient]->assignCredentials(credencialesCliente);

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


	Logger::getInstance()->log(DEBUG, "Creando clientes e iniciado accepts...");


	//servidor.reSendMessage(clientes[numberOfClient1]->getSocket(), clientes[numberOfClient2]->getSocket(), "Nombre de Usuario", "Server", "Server");
	//clientes[numberOfClient1]->setUser(client_reply);
	//clientes[numberOfClient2]->setUser(client_reply);

	//pthread_mutex_init(&mutexProcesar,NULL);

	Logger::getInstance()->log(DEBUG, "Inicializar MUTEX en main.");

	pthread_mutex_init(&mutexQueue,NULL);
	pthread_mutex_init(&mutexPushCliente,NULL);

	//-> Comienzo hilos para el loggin
	for (int i = 0; i < cantClientes; i++) {
		pthread_create(&hiloValidarCredenciales[i],NULL,validateCredentials,&clientNumbers[i]);
	}



	for (int i = 0; i < cantClientes; i++) {
		pthread_join(hiloValidarCredenciales[i],NULL);
	}

	bool noMandoNada = true;
	for(int i =0 ; i< cantClientes; i++){
		send(clientes[i]->getSocket(), &noMandoNada, sizeof(bool), 0);
	}


	//-> Comienzo hilos de juego
	pthread_create(&hiloSendBroadcast,NULL,message_send,NULL);

	for (int i = 0; i < cantClientes; i++) {
		pthread_create(&hiloRecieveMessage[i],NULL,message_recieve,&clientNumbers[i]);
	}

	for (int i = 0; i < CANT_HILOS_RECONEXION; i++) {
		pthread_create(&hiloMidGameConnects[i],NULL,manageMidGameConnects,0);
	}


	Logger::getInstance()->log(DEBUG, "Inicializar JOIN en main.");

	pthread_join(hiloSendBroadcast,NULL);

	for (int i = 0; i < cantClientes; i++) {
		pthread_join(hiloRecieveMessage[i],NULL);
	}

//	servidor.~Servidor();
//	for(int i =0; i < cantClientes; i++){
//		clientes[i]->~Cliente();
//	}


	delete Logger::getInstance();

	return 0;
}


