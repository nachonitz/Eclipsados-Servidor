/*
 * ParserXML.cpp
 *
 *  Created on: Sep 17, 2019
 *      Author: franco
 */

#include "ParserXML.h"

#include <algorithm>

using namespace tinyxml2;

/*
Hay distintos tipos de errores:
	- no se puede abrir el archivo custom
	- no existe alguna seccion del xml (FirstChildElement == null)
	- el valor no es del tipo correcto (se esperaba int y dio bool,string,etc)
*/

ParserXML::ParserXML(std::string rutaConfig){

	pConfig = new XMLDocument;

	XMLError eArchivo = pConfig->LoadFile(rutaConfig.c_str());

	//TODO: y si falla en abrir el default?
	XMLError eDefault = configDefault.LoadFile("xmlServerDefault.xml");

	if (eArchivo != XML_SUCCESS) {

		//TODO: necesitara proveer mas informacion?
		std::string lineaError = pConfig->ErrorLineNum() ? ". Linea de error: " + std::to_string(pConfig->ErrorLineNum()) : ". Linea desconocida";

		Logger::getInstance()->log(ERROR, "Archivo XML personalizado no encontrado o corrupto. Error del tipo: " + std::string(pConfig->ErrorName()) +
									lineaError + ". Se utilizara el defecto.");

		delete pConfig;

		//usar default, en vez de custom
		pConfig = &configDefault;
	}

	pHandler = new XMLHandle(pConfig);

}

void ParserXML::setDebugLevelFromDefault() {
	const char *debugLevel =
			configDefault.FirstChildElement("configuracionServidor")->FirstChildElement(
					"debugLevel")->GetText();
	if (strcmp(debugLevel, "DEBUG") == 0) {
		Logger::getInstance()->setLevel(DEBUG);
	} else if (strcmp(debugLevel, "INFO") == 0) {
		Logger::getInstance()->setLevel(INFO);
	} else if (strcmp(debugLevel, "ERROR") == 0) {
		Logger::getInstance()->setLevel(ERROR);
	}

	Logger::getInstance()->log(ERROR,
			"Opcion invalida o inexistente en <debugLevel>, utilizando la indicada por xmlDefault...");
}

void ParserXML::parsearConfig(int *cantEnemigos, int *cantCuchillos, int *cantCajas, int *cantCanios, int *cantBarriles, int *cantJugadores, std::map<std::string, std::string>& usuarios) {

	if (pConfig == &configDefault) {
		//TODO: estoy parseando el default, no debo chequear errores
		//parsearConfigDefault(cantEnemigos, cantCuchillos, cantCajas, cantCanios, cantBarriles, nivel1, nivel2);
	}

	XMLElement* pEscenarioDEFAULT = configDefault.FirstChildElement("configuracionServidor")->FirstChildElement("escenario");

	XMLHandle hRaiz = pHandler->FirstChildElement("configuracionServidor");

	XMLElement* elementDebug;

	if ((elementDebug = hRaiz.FirstChildElement("debugLevel").ToElement()) != nullptr) {

		const char* debugLevel = elementDebug->GetText();

		if (strcmp(debugLevel, "DEBUG") == 0) {
			Logger::getInstance()->setLevel(DEBUG);
			Logger::getInstance()->log(INFO, "Cambiando debugLevel al indicado por xml: DEBUG");

		}
		else if (strcmp(debugLevel, "INFO") == 0) {
			Logger::getInstance()->setLevel(INFO);
			Logger::getInstance()->log(INFO, "Cambiando debugLevel al indicado por xml: INFO");

		}
		else if (strcmp(debugLevel, "ERROR") == 0) {
			Logger::getInstance()->setLevel(ERROR);
			Logger::getInstance()->log(INFO, "Cambiando debugLevel al indicado por xml: ERROR");
		}
		else {
			setDebugLevelFromDefault();
		}
	}

	else {
		setDebugLevelFromDefault();
	}


	asignarValor(cantJugadores, "jugadores", hRaiz, configDefault.FirstChildElement("configuracionServidor"));
	Logger::getInstance()->log(INFO, "Cantidad de jugadores maximos a aceptar: " + std::to_string(*cantJugadores));

	XMLHandle hEscenario = hRaiz.FirstChildElement("escenario");

	asignarValor(cantCuchillos, "cuchillo", hEscenario.FirstChildElement("cantidades"), pEscenarioDEFAULT->FirstChildElement("cantidades"));
	Logger::getInstance()->log(DEBUG, std::string("Cantidad de cuchillos: " + std::to_string(*cantCuchillos)));

	asignarValor(cantCajas, "caja", hEscenario.FirstChildElement("cantidades"), pEscenarioDEFAULT->FirstChildElement("cantidades"));
	Logger::getInstance()->log(DEBUG, std::string("Cantidad de cajas: " + std::to_string(*cantCajas)));

	asignarValor(cantBarriles, "barril", hEscenario.FirstChildElement("cantidades"), pEscenarioDEFAULT->FirstChildElement("cantidades"));
	Logger::getInstance()->log(DEBUG, std::string("Cantidad de barriles: " + std::to_string(*cantBarriles)));

	asignarValor(cantCanios, "canio", hEscenario.FirstChildElement("cantidades"), pEscenarioDEFAULT->FirstChildElement("cantidades"));
	Logger::getInstance()->log(DEBUG, std::string("Cantidad de caños: " + std::to_string(*cantCanios)));

	asignarValor(cantEnemigos, "enemigo", hEscenario.FirstChildElement("cantidades"), pEscenarioDEFAULT->FirstChildElement("cantidades"));
	Logger::getInstance()->log(DEBUG, std::string("Cantidad de enemigos: " + std::to_string(*cantEnemigos)));


	XMLElement* eUsuarios = hRaiz.FirstChildElement("usuarios").ToElement();

	if (eUsuarios != nullptr)
		asignarMapa(usuarios, eUsuarios, "usuario");

	if (usuarios.size() < 4) {
		Logger::getInstance()->log(INFO, "Se encontraron menos de 4 usuarios correctamente definidos en xmlCustom, se agregaran los definidos por xmlDefault...");
		asignarMapa(usuarios, configDefault.FirstChildElement("configuracionServidor")->FirstChildElement("usuarios"), "usuario");
	}

	Logger::getInstance()->log(INFO, "Finalizado el parseo del XML");
}

ParserXML::~ParserXML() {

	delete pHandler;

	if (pConfig != &configDefault)
		delete pConfig;

}

void ParserXML::asignarValor(int* variable, const char* nombre, XMLHandle base, XMLElement* backup) {

	XMLElement* pElemento = base.FirstChildElement(nombre).ToElement();

	XMLError error = XML_SUCCESS;

	if (pElemento)
		error = pElemento->QueryIntText(variable);

	if (!pElemento || error != XML_SUCCESS) {

		Logger::getInstance()->log(ERROR, "Etiqueta <" + std::string(nombre) + "> inexistente o con datos erroneos/nulos. Utilizando valor predeterminado.");
		backup->FirstChildElement(nombre)->QueryIntText(variable);
	}


}


void ParserXML::asignarMapa(std::map<std::string, std::string> &mapa, XMLElement* eBase, const char * nombreItems) {
	//asume que los elementos estan en orden
  Logger::getInstance()->log(INFO, "Leyendo usuarios de XML...");
	for(XMLElement* e = eBase->FirstChildElement(nombreItems); e != NULL; e = e->NextSiblingElement(nombreItems)) {

		XMLElement* eNombre = e->FirstChildElement("nombre");
		XMLElement* ePass = e->FirstChildElement("password");

		if (eNombre && ePass) {
			std::string nombre = eNombre->GetText();

			std::string pass = ePass->GetText();


			// a lower case...
			std::transform(nombre.begin(), nombre.end(), nombre.begin(), ::tolower);

			std::transform(pass.begin(), pass.end(), pass.begin(), ::tolower);

			mapa.insert({ nombre, pass });
			Logger::getInstance()->log(DEBUG, "Agregado usuario " + nombre + " con password de longitud: " + std::to_string(pass.length()));
		}

		else {
			Logger::getInstance()->log(ERROR, "Usuario con secciones erroneas en linea " + std::to_string(e->GetLineNum()) + ". Recordar que se esperan las secciones 'nombre' y 'password'.");
		}

	}
}
