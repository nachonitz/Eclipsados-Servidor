#include "servidor.h"
#include "cliente.h"
#include <pthread.h>


	struct Usuarios{
		vector<Cliente*> clientes;
	};
	char mensaje[1000], client_recep[1000], client_send[1000];
	int cantClientes = 2;

	Usuarios* usuarios;
	Servidor* servidor;

	pthread_mutex_t mutex;
	pthread_t recibir;
	pthread_t enviar;



void* ExecuteThread1(void* HiloUno){


	for(int i = 0; i < cantClientes; i++){
		//pthread_mutex_lock(&mutex);
		usuarios->clientes[i]->recibirMensaje(client_recep,usuarios->clientes[i]->getNombre());
		//pthread_mutex_unlock(&mutex);
	}

}

void* ExecuteThread2(void* HiloDos){

	/*int j = (cantClientes - 1);
	for(j; j < 0; j--){*/
		//pthread_mutex_lock(&mutex);
		bzero(client_send, 1000);
		strcat(client_send, client_recep);
		servidor->sendMensajeDeClientes(usuarios->clientes[0]->getSocket(), client_send, usuarios->clientes[1]->getNombre());
		//pthread_mutex_unlock(&mutex);
	//}

}


int main(int argc, char *argv[]) {

	pthread_mutex_init(&mutex, NULL);

	usuarios = new Usuarios();
	servidor = new Servidor(argv[1]);

	for(int i = 0; i < cantClientes; i++){

		Cliente* cliente = new Cliente(servidor);
		usuarios->clientes.push_back(cliente);

	}

	for(int i = 0; i < cantClientes; i++){

		servidor->pedirUsuario(usuarios->clientes[i]->getSocket());
		usuarios->clientes[i]->recibirMensaje(client_recep, "Usuario");
		usuarios->clientes[i]->setUsuario(client_recep);
	}

	for(int i = 0; i < cantClientes; i++){
		bzero(client_send, 1000);
		strcat(client_send, "Welcome\n");
		servidor->sendMensajeDeClientes(usuarios->clientes[i]->getSocket(), client_send, "Server:");
		bzero(client_send, 1000);
	}

	while(1){


		pthread_create( &recibir, NULL, ExecuteThread1, (void *) "Hilo Uno");

		pthread_create( &enviar, NULL, ExecuteThread2, (void *) "Hilo Dos");


		if( strcmp(client_recep, "quit\n") == 0 || strcmp(client_send, "quit\n") == 0){
			pthread_exit(&recibir);
			pthread_exit(&enviar);
			break;
		}

		//pthread_join(recibir,NULL);
		//pthread_join(enviar,NULL);

	}




	servidor->~Servidor();
	for(int i =0; i < cantClientes; i++){
		usuarios->clientes[i]->~Cliente();
	}

	return 0;
}

