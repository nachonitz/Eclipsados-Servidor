#include "cliente.h"
#include "servidor.h"
#include <pthread.h>
#include "modelo/Juego.h"
#include "modelo/nivel/Nivel.h"
#include <queue>


vector<Cliente*> clientes;
char mensaje[1000], client_reply[1000];
Servidor servidor;

//pthread_mutex_t mutex;
//pthread_mutex_init(&mutex,NULL);
int clientNumbers[] = {0,1,2,3};

pthread_t hiloSendBroadcast;
pthread_t hiloRecieveMessage[4];
Juego* juego;
//pthread_mutex_t mutexProcesar							// ya no haria falta porque hay un solo thread modificando el juego
pthread_mutex_t mutexQueue;


queue <struct informacionRec> colaInfoDeClientes;


void* message_send(void*arg){
	while(1){

		// vaciar TODA la cola y procesar toda la info
		//pthread_mutex_lock(&mutexQueue);				//<-- creeria que, en rigor, deberian ir esos mutex pero no estoy seguro
		while (!colaInfoDeClientes.empty()) {
			struct informacionRec info = colaInfoDeClientes.front();
			juego->procesarInfo(info);
			colaInfoDeClientes.pop();
		}
		//pthread_mutex_unlock(&mutexQueue);

		// enviar
		struct informacionEnv info = juego->getInformacion();

		for (int i = 0; i < cantClientes; i++)
			servidor.sendInfo(clientes[i]->getSocket(),info);
		juego->moverEnemigos();
		juego->actualizarAnimaciones();
		//----
		SDL_Delay(1000/60);
	}
}

void* message_recieve(void*arg){
	int * arg_ptr = (int*)arg;
	int numberOfClient = *arg_ptr;
	while(1){
		struct informacionRec infoRecv = clientes[numberOfClient]->recieveInfo();

		infoRecv.numeroDeCliente = numberOfClient;

		pthread_mutex_lock(&mutexQueue);
		colaInfoDeClientes.push(infoRecv);
		//juego->procesarInfo(infoRecv);
		pthread_mutex_unlock(&mutexQueue);
	}
}


int main(int argc, char *argv[]) {

	juego = new Juego(3,3,3,3,3,cantClientes);

	servidor.setPort(argv[1]);

	for(int i = 0; i < cantClientes; i++){

		Cliente* cliente = new Cliente(&servidor);
		clientes.push_back(cliente);

	}
	//servidor.reSendMessage(clientes[numberOfClient1]->getSocket(), clientes[numberOfClient2]->getSocket(), "Nombre de Usuario", "Server", "Server");
	//clientes[numberOfClient1]->setUser(client_reply);
	//clientes[numberOfClient2]->setUser(client_reply);

	//pthread_mutex_init(&mutexProcesar,NULL);

	pthread_mutex_init(&mutexQueue,NULL);

	pthread_create(&hiloSendBroadcast,NULL,message_send,NULL);

	for (int i = 0; i < cantClientes; i++) {
		pthread_create(&hiloRecieveMessage[i],NULL,message_recieve,&clientNumbers[i]);
	}

	pthread_join(hiloSendBroadcast,NULL);
	for (int i = 0; i < cantClientes; i++) {
		pthread_join(hiloRecieveMessage[i],NULL);
	}

	servidor.~Servidor();
	for(int i =0; i < cantClientes; i++){
		clientes[i]->~Cliente();
	}


	return 0;
}


