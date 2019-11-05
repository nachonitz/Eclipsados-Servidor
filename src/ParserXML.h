/*
 * ParserXML.h
 *
 *  Created on: Sep 17, 2019
 *      Author: franco
 */



#ifndef SRC_PARSERXML_H_
#define SRC_PARSERXML_H_

#define CANT_CAPAS 3
#define CANT_SPRITES 5

#define MAX_CANT_VALOR 50		//un valor asignado mediante asignarValor no puede superar esta cantidad, sino ira al default

#include <string>

#include <vector>

#include "tinyxml2/tinyxml2.h"
#include <map>

#include "Logger.h"

class ParserXML {
public:
	ParserXML(std::string rutaConfig);

	void parsearConfig(int *cantEnemigos, int *cantCuchillos, int *cantCajas, int *cantCanios, int *cantBarriles, int* cantJugadores, std::map<std::string, std::string> &usuarios);

	virtual ~ParserXML();

	void asignarValor(int* variable, const char* nombre, tinyxml2::XMLHandle base, tinyxml2::XMLElement* backup);

	void asignarMapa(std::map<std::string, std::string> &mapa, tinyxml2::XMLElement* eBase, const char * nombreItems);


private:
	tinyxml2::XMLDocument configDefault;

	tinyxml2::XMLDocument* pConfig;

	tinyxml2::XMLHandle* pHandler;

	void setDebugLevelFromDefault();
};

#endif /* SRC_PARSERXML_H_ */
