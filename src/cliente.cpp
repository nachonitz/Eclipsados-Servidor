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


struct informacionRec Cliente::recieveInfo(){

	struct informacionRec info;
	recv(socks, &info, sizeof(struct informacionRec), 0);
	return info;

}

/*void Cliente::setUser(char userName[1000]){

	recibirMensaje(userName);
	strcat(name, sClient.mrec);


}*/
