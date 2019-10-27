/*
 * Juego.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: franco
 */

#include "Juego.h"
#include "../Logger.h"

Juego::Juego(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos, int cantJugadores) {

	this->cuchillos = cantCuchillos;
	this->cajas = cantCajas;
	this->canios = cantCanios;
	this->barriles = cantBarriles;
	this->enemigos = cantEnemigos;
	this->animacionActual = ACCION_PARADO;

	FactoryEntidadUbicada factory;

	for (int i = 0; i < cantJugadores; i++) {

		this->jugadores.push_back(factory.crearEntidadConPersonaje());

	}

  Logger::getInstance()->log(INFO, "******** NIVEL 1 ********");
	this-> nivel = new Nivel(1,jugadores, cantCuchillos, cantCajas, cantCanios, cantBarriles, cantEnemigos);

}

Juego::~Juego() {
	// TODO Auto-generated destructor stub
	for (EntidadUbicada* entidad : jugadores) {
		delete entidad->getDibujable();
		delete entidad;
	}
}

PosicionGlobal* Juego::getPosicionJugador(int numeroJugador) {
	return jugadores.at(numeroJugador)->getPosicionGlobal();
}

void Juego::moverEnemigos(){
	nivel->moverEnemigos();
}

void Juego::movimientoArriba(int numeroJugador) {
	nivel->movimientoArriba(numeroJugador);
}

void Juego::movimientoSalto(int numeroJugador) {
	nivel->movimientoSalto(numeroJugador);
}

void Juego::terminadoSalto(int numeroJugador) {
	nivel->terminoSalto(numeroJugador);
}

void Juego::movimientoAbajo(int numeroJugador) {
	nivel->movimientoAbajo(numeroJugador);
}

void Juego::movimientoDerecha(int numeroJugador) {
	//nivel->moverCapaDerecha();
	nivel->movimientoDerecha(numeroJugador);
}


void Juego::movimientoIzquierda(int numeroJugador) {
	nivel->movimientoIzquierda(numeroJugador);
}

Personaje* Juego::getJugador(int numeroJugador) {
	return nivel->getPersonaje(numeroJugador);
}

bool Juego::terminoElNivel(){
	return this->nivel->terminoElNivel();
}

void Juego::cambiarDeNivel(){

	//TODO AAAAAAAAAAAAAAAAAAA CAMBIARNIVEL
  Logger::getInstance()->log(INFO, "******** NIVEL 2 ********");
	//entidad->seCambioElNivel(personaje);
	delete(nivel);
	//delete(entidad);
	//entidad = new EntidadUbicada(personaje);
	//nivel = new Nivel(2,entidad, cuchillos, cajas, canios, barriles, enemigos);

}

void Juego::procesarInfo(struct informacionRec infoRec){

	int numeroDeCliente = infoRec.numeroDeCliente;

	switch(infoRec.movimiento){
	case RIGHT: this->movimientoDerecha(numeroDeCliente);
	break;
	case LEFT: this->movimientoIzquierda(numeroDeCliente);
	break;
	case UP: this->movimientoArriba(numeroDeCliente);
	break;
	case DOWN: this->movimientoAbajo(numeroDeCliente);
	break;
	case STAND: break;
	}
	Personaje* cody = (Personaje *)jugadores.at(numeroDeCliente)->getDibujable();

	if(animacionActual != infoRec.animacionActual){
		cody->setAnimacionActual(infoRec.animacionActual, infoRec.flip);
		animacionActual = infoRec.animacionActual;
	}

	nivel->actualizarAnimaciones();

}


