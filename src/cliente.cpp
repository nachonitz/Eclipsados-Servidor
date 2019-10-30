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
	int res = recv(socks, &info, sizeof(struct informacionRec), 0);

	if (res < 0)
		info.numeroDeCliente = -1;

	return info;

}

struct credencial Cliente::recieveCredentials(){

	struct credencial credencialesPorValidar;
	Logger::getInstance()->log(DEBUG, "RECIBIENDO...");
	recv(socks, &credencialesPorValidar, sizeof(struct credencial), 0);
	Logger::getInstance()->log(DEBUG, "RECIBIDAS CREDENCIALES: " + std::string(credencialesPorValidar.usuario) + " - " + std::string(credencialesPorValidar.contrasenia));
	return credencialesPorValidar;
}

/*void Cliente::setUser(char userName[1000]){

	recibirMensaje(userName);
	strcat(name, sClient.mrec);


}*/
