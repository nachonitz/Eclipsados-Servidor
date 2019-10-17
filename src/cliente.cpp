#include "cliente.h"


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

	bzero(sClient.userName, 1000);
	bzero(sClient.mrec, 1000);
	bzero(reply, 1000);
	recv(socks, &sClient, sizeof(struct rec), 0);
	printf("%s:\n", sClient.userName);
	printf("%s\n", sClient.mrec);
	strcat(reply, sClient.mrec);

}

void Cliente::setUser(char userName[1000]){

	recibirMensaje(userName);
	strcat(name, sClient.mrec);


}
