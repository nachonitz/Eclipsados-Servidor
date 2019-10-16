#include "cliente.h"


Cliente::Cliente(Servidor* server){

	c = sizeof(struct sockaddr_in);

	socks = socket(AF_INET, SOCK_STREAM, 0);

	//Accept
	socks = (accept( server->getSocketDesc(), (struct	 sockaddr *)&cliente, (socklen_t *) &c));
	if (socks < 0){
		perror("Acceptance Failed. Error");
		close(socks);
		exit(-1);
	}else{
		printf("Accepting Connection...\n");
		printf("Connection Successful on socket: %d\n", socks);
	}

}

Cliente::~Cliente(){

	close(socks);
	printf("Socket numero: %d Closed\n", socks);

}


void Cliente::recibirMensaje(char reply[1000], char name[1000]){

	bzero(reply, 1000);
	recv(socks, reply, 1000, 0);
	printf("%s:\n", name);
	printf("%s\n", reply);

}

void Cliente::guardarNombreUsuario(){

	bzero(nombre, 1000);
	recv(socks, nombre, 1000, 0);


}

void Cliente::setUsuario(char name[1000]){

	strcat(nombre, name);
	bzero(name, 1000);

}

