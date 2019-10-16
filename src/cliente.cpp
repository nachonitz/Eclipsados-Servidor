#include "../../../../eclipse-workspace/Servidor/Cliente-Servidor/src/cliente.h"


Cliente::Cliente(Servidor* server){

	c = sizeof(struct sockaddr_in);

	//Accept
	socks = (accept( server->getSocketDesc(), (struct	 sockaddr *)&cliente, (socklen_t *) &c));
	if (socks < 0){
		perror("Acceptance Failed. Error");
		close(socks);
		exit(-1);
	}else{
		puts("Connection Accepted");
		puts("Connection Successful");
	}

}

Cliente::~Cliente(){

	close(socks);
	printf("Socket numero: %d Closed\n", socks);

}


void Cliente::recibirMensaje(char reply[1000]){

	bzero(reply, 1000);
	recv(socks, reply, 1000, 0);
	printf("Cliente:\n");
	printf("%s\n", reply);

}
