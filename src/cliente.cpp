#include "cliente.h"


Cliente::Cliente(Servidor* server){

	c = sizeof(struct sockaddr_in);

	//Accept
	socks = (accept( server->getSocketDesc(), (struct	 sockaddr *)&cliente, (socklen_t *) &c));
	if (socks < 0){
		Logger::getInstance()->log(ERROR, "No se pudo conectar con un nuevo cliente.");

		perror("Acceptance Failed. Error");
		close(socks);
		exit(-1);
	}else{
		Logger::getInstance()->log(INFO, "Conexion con nuevo cliente exitosa!");

		puts("Connection Accepted");
		puts("Connection Successful");
	}

}

std::string Cliente::getUsuario() {
	return std::string(credencialCliente.usuario);
}

Cliente::~Cliente(){

	close(socks);
	printf("Socket numero: %d Closed\n", socks);
	Logger::getInstance()->log(DEBUG, "Cerrado socket.");


}


struct informacionRec Cliente::recieveInfo(){

	struct informacionRec info;
	int recibido = 0;
	while (recibido < sizeof(struct informacionRec)){
		recibido += recv(socks, &info+recibido, sizeof(struct informacionRec)-recibido, 0);
		if (recibido < 0)
			info.numeroDeCliente = -1;
	}
	return info;

}

bool Cliente::estadoTransferencia(){

	bool estadoTransferencia;

	recv(socks, &estadoTransferencia, sizeof(bool), 0);

	return estadoTransferencia;

}

void Cliente::assignCredentials(struct credencial cred) {
	this->credencialCliente = cred;
}


bool Cliente::tieneEstasCredenciales(struct credencial credencialesCliente) {


	bool user = strcmp(this->credencialCliente.usuario, credencialesCliente.usuario) ==0;

	Logger::getInstance()->log(DEBUG, "CHEQUEANDO USER: " + std::string(this->credencialCliente.usuario) + " VS " + std::string(credencialesCliente.usuario));

	Logger::getInstance()->log(DEBUG, "RESULTADO USER: " +std::to_string(user));

	bool pass = strcmp(this->credencialCliente.contrasenia, credencialesCliente.contrasenia) == 0;


	Logger::getInstance()->log(DEBUG, "CHEQUEANDO PASS: " + std::string(this->credencialCliente.contrasenia) + " VS " + std::string(credencialesCliente.contrasenia));

	Logger::getInstance()->log(DEBUG, "RESULTADO PASS: " +std::to_string(pass));

	return user && pass;

}



struct credencial Cliente::recieveCredentials(){

	struct credencial credencialesPorValidar;
	Logger::getInstance()->log(DEBUG, "RECIBIENDO...");
	int recibido = recv(socks, &credencialesPorValidar, sizeof(struct credencial), 0);
	if (recibido <= 0){
		Logger::getInstance()->log(DEBUG, "NO SE PUDO RECIBIR LA CREDENCIAL");
	}
	Logger::getInstance()->log(DEBUG, "SE PUDO RECIBIR LA CREDENCIAL");
	Logger::getInstance()->log(DEBUG, "RECIBIDAS CREDENCIALES: " + std::string(credencialesPorValidar.usuario) + " - " + std::string(credencialesPorValidar.contrasenia));
	return credencialesPorValidar;
}

/*void Cliente::setUser(char userName[1000]){

	recibirMensaje(userName);
	strcat(name, sClient.mrec);


}*/
