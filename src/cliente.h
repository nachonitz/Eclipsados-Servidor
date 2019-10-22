#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "servidor.h"

class Cliente {
public:
	Cliente(Servidor* server);
	~Cliente();
	struct informacionRec recieveInfo();
	int getSocket(){return socks;}
	void setUser(char userName[1000]);
	char* getUserName(){return name;}

private:
	struct sockaddr_in cliente;
	int c;
	int socks;
	char reply[1000];
	char name[1000];
	struct rec{
		char userName[1000];
		char mrec[1000];
	};
	rec sClient;

};



#endif /* CLIENTE_H_ */
