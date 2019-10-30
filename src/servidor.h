#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "modelo/Juego.h"
#include <map>
using namespace std;

struct credencial {
	char usuario[MAX_USER_LEN];
	char contrasenia[MAX_PASS_LEN];
	bool credencialValida;
	int myIdx;
} ;


class Servidor {
public:
	Servidor(char *puerto);
	Servidor();
	~Servidor();

	int getSocketDesc(){return socket_desc;}
	int sendInfo(int clientSocket, struct informacionEnv info);
	void reciveInfo();
	void reSendMessage(int client1Socket,  int client2Socket, char * message, char* user1Name, char* user2Name);
	void setPort(char* port);
	void verificarCredenciales(struct credencial* credencialPorValidar, std::map<std::string, std::string> & usuarios);

private:
	struct sockaddr_in server;
	int socket_desc;
	char info[1000];
	struct envio{
		char userName[1000];
		char mensaje[1000];
	};

	envio sClient1, sClient2, sServer;

};



#endif /* SERVIDOR_H_ */
