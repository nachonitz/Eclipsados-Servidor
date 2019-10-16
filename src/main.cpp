#include "../../../../eclipse-workspace/Servidor/Cliente-Servidor/src/cliente.h"
#include "../../../../eclipse-workspace/Servidor/Cliente-Servidor/src/servidor.h"
#include <pthread.h>

vector<Cliente*> clientes;
char mensaje[1000], client_reply[1000];
Servidor servidor;

void* message_send(void*arg){
	while(1){
		servidor.sendInfo(clientes[0]->getSocket(),clientes[1]->getSocket());
	}
}

void* message_recieve(void*arg){
	int * arg_ptr = (int*)arg;
	int numberOfClient = *arg_ptr;
	while(1){
		clientes[numberOfClient]->recibirMensaje(client_reply);
		servidor.reSendMessage(clientes[0]->getSocket(),clientes[1]->getSocket(), client_reply);
	}
}


int main(int argc, char *argv[]) {

	//pthread_mutex_t mutex;
	//pthread_mutex_init(&mutex,NULL);
	int numberOfClient1 = 0;
	int numberOfClient2 = 1;
	pthread_t hiloSendBroadcast;
	pthread_t hiloRecieveMessage1;
	pthread_t hiloRecieveMessage2;

	servidor.setPort(argv[1]);

	for(int i = 0; i < 2; i++){

		Cliente* cliente = new Cliente(&servidor);
		clientes.push_back(cliente);

	}
/*
	while(1){


		message_send(NULL);
		message_recieve(&numberOfClient1);
		message_recieve(&numberOfClient2);

		if( strcmp(mensaje, "quit\n") == 0 || strcmp(client_reply, "quit\n") == 0){
			break;
		}


	}
*/
	pthread_create(&hiloSendBroadcast,NULL,message_send,NULL);
	pthread_create(&hiloRecieveMessage1,NULL,message_recieve,&numberOfClient1);
	pthread_create(&hiloRecieveMessage2,NULL,message_recieve,&numberOfClient2);

	pthread_join(hiloSendBroadcast,NULL);
	pthread_join(hiloRecieveMessage1,NULL);
	pthread_join(hiloRecieveMessage2,NULL);

	servidor.~Servidor();
	for(int i =0; i < 2; i++){
		clientes[i]->~Cliente();
	}


	return 0;
}


