#include "servidor.h"


Servidor::Servidor(char *puerto){
	setPort(puerto);
	strcat(sServer.userName, "Server");
}
Servidor::Servidor(){

}
Servidor::~Servidor(){

	close(socket_desc);
	printf("Socket numero %d Closed\n", socket_desc);

}

int Servidor::sendInfo(int clientSocket, struct informacionEnv info){
	int enviado = 0;
	while(enviado < sizeof(int)){
		enviado += send(clientSocket, &info.cantAnimados+enviado, sizeof(info.cantAnimados)-enviado, MSG_NOSIGNAL);
		if (enviado < 0){
			return -1;
		}
	}
	enviado = 0;
	while(enviado < sizeof(int)){
		enviado += send(clientSocket, &info.cantJugadores+enviado, sizeof(info.cantJugadores)-enviado, MSG_NOSIGNAL);
		if (enviado < 0){
			return -1;
		}
	}
	enviado = 0;
	while(enviado < sizeof(int)){
		enviado += send(clientSocket, &info.cantElementos+enviado, sizeof(info.cantElementos)-enviado, MSG_NOSIGNAL);
		if (enviado < 0){
			return -1;
		}
	}

	for(int i=0; i < info.cantAnimados; i++){
		enviado = 0;
		while(enviado < sizeof(struct animado)){
			enviado += send(clientSocket, &info.animados[i]+enviado , sizeof(info.animados[i])-enviado, MSG_NOSIGNAL);
			if (enviado < 0){
				return -1;
			}
		}
	}
	for(int i=0; i < 3; i++){
		enviado = 0;
		while(enviado < sizeof(struct capa)){
			enviado += send(clientSocket, &info.capas[i]+enviado, sizeof(info.capas[i])-enviado, MSG_NOSIGNAL);
			if (enviado < 0){
				return -1;
			}
		}
	}
	for(int i=0; i < info.cantElementos; i++){
		enviado = 0;
		while(enviado < sizeof(struct elemento)){
			enviado += send(clientSocket, &info.cantElementos+enviado, sizeof(info.elementos[i])-enviado, MSG_NOSIGNAL);
			if (enviado < 0){
				return -1;
			}
		}
	}
	return 1;
}

void Servidor::reSendMessage(int client1Socket, int client2Socket, char* message, char* user1Name, char* user2Name){

	bzero(sClient1.userName, 1000);
	bzero(sClient2.userName, 1000);
	bzero(sClient1.mensaje, 1000);
	bzero(sClient2.mensaje, 1000);

	strcat(sClient1.userName, user2Name);
	strcat(sClient1.mensaje, message);
	strcat(sClient2.userName, user1Name);
	strcat(sClient2.mensaje, message);

	send(client1Socket, &sClient1, sizeof(struct envio), 0);
	send(client2Socket, &sClient2, sizeof(struct envio), 0);

}

void Servidor::reciveInfo(){

}
void Servidor::setPort(char* puerto){
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( atoi(puerto) );

	//Esto es para poder reusar el address sin esperar a que se resetee en caso de no cerrarlo bien
	int activado = 1;
	setsockopt(socket_desc,SOL_SOCKET, SO_REUSEADDR,&activado, sizeof(activado));

	//Creando Socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);

	if(socket_desc == -1){
		perror("Could not create socket. Error \n");
		exit(-1);
	}
	printf("Socket created: %d\n", socket_desc);

	//Bind
	if( bind(socket_desc, (struct sockaddr *)&server, sizeof(server) ) != 0){
		printf("Server Bind Failed. Errno %i: %s\n",errno,strerror(errno));
		exit(-1);
	}else{
		printf("Bind Done \n");
	}

	//Listen
	printf("Listening on port %s. Waiting for acceptance... \n", puerto);
	listen(socket_desc, MAX_CLIENTES + 2);
	fflush(stdout);
}

void Servidor::verificarCredenciales(struct credencial* credencialPorValidar, std::map<std::string, std::string> & usuarios){

	auto pair = usuarios.find(credencialPorValidar->usuario);

	if (pair != usuarios.end() && pair->second == std::string(credencialPorValidar->contrasenia)) {
		Logger::getInstance()->log(INFO, "Jugador logeado! Nombre: " + pair->first);
		credencialPorValidar->credencialValida = true;
	}
}
