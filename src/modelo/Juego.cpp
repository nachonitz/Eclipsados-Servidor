/*
 * Juego.cpp
 *
 *  Created on: Sep 3, 2019
 *      Author: franco
 */

#include "Juego.h"
#include "../Logger.h"

Juego::Juego(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos) {

	this->cuchillos = cantCuchillos;
	this->cajas = cantCajas;
	this->canios = cantCanios;
	this->barriles = cantBarriles;
	this->enemigos = cantEnemigos;

	this-> personaje = new Personaje;
	this-> entidad = new EntidadUbicada(personaje);

  Logger::getInstance()->log(INFO, "******** NIVEL 1 ********");
	this-> nivel = new Nivel(1,entidad, cantCuchillos, cantCajas, cantCanios, cantBarriles, cantEnemigos);

}

Juego::~Juego() {
	// TODO Auto-generated destructor stub
	delete entidad;
	delete personaje;
}

PosicionGlobal* Juego::getPosicionJugador() {
	return entidad->getPosicionGlobal();
}

void Juego::moverEnemigos(){
	nivel->moverEnemigos();
}

void Juego::movimientoArriba() {
	nivel->movimientoArriba();
}

void Juego::movimientoSalto() {
	nivel->movimientoSalto();
}

void Juego::terminadoSalto() {
	nivel->terminoSalto();
}

void Juego::movimientoAbajo() {
	nivel->movimientoAbajo();
}

void Juego::movimientoDerecha() {
	nivel->movimientoDerecha();
}


void Juego::movimientoIzquierda() {
	nivel->movimientoIzquierda();
}

Personaje* Juego::getJugador() {
	return nivel->getPersonaje();
}

bool Juego::terminoElNivel(){
	return this->nivel->terminoElNivel();
}

void Juego::cambiarDeNivel(){
  Logger::getInstance()->log(INFO, "******** NIVEL 2 ********");
	entidad->seCambioElNivel(personaje);
	delete(nivel);
	//delete(entidad);
	//entidad = new EntidadUbicada(personaje);
	nivel = new Nivel(2,entidad, cuchillos, cajas, canios, barriles, enemigos);

}


