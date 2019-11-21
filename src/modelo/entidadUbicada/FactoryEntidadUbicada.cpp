/*
 * FactoryEntidadUbicada.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: franco
 */

#include "FactoryEntidadUbicada.h"

FactoryEntidadUbicada::FactoryEntidadUbicada() {
	// TODO Auto-generated constructor stub

}

FactoryEntidadUbicada::~FactoryEntidadUbicada() {
	// TODO Auto-generated destructor stub
}


EntidadUbicada* FactoryEntidadUbicada::crearEntidadConPersonaje() {
	Dibujable* personaje = new Personaje;
	return new EntidadUbicada(personaje);
}

EntidadUbicada* FactoryEntidadUbicada::crearEntidadConEnemigo(float horizontal, float vertical, int tipoEnemigo) {
	Dibujable* enemigo = new Enemigo(horizontal, vertical, tipoEnemigo);
	return new EntidadUbicada(enemigo, horizontal, vertical);
}

/*EntidadUbicada* FactoryEntidadUbicada::crearEntidadConBarril() {
	Dibujable* barril = new Barril();
	return new EntidadUbicada(barril);
}*/


EntidadUbicada* FactoryEntidadUbicada::crearEntidadConBarril(float horizontal, float vertical) {
	Dibujable* barril = new Barril(horizontal, vertical);
	return new EntidadUbicada(barril, horizontal, vertical);
}

EntidadUbicada* FactoryEntidadUbicada::crearEntidadConCuchillo(float horizontal, float vertical) {
	Dibujable* cuchillo= new Cuchillo(horizontal, vertical);
	return new EntidadUbicada(cuchillo, horizontal, vertical);
}

EntidadUbicada* FactoryEntidadUbicada::crearEntidadConCanio(float horizontal, float vertical) {
	Dibujable* canio = new CanioMetalico(horizontal, vertical);
	return new EntidadUbicada(canio, horizontal, vertical);
}


EntidadUbicada* FactoryEntidadUbicada::crearEntidadConCaja(float horizontal, float vertical) {
	Dibujable* caja = new Caja(horizontal, vertical);
	return new EntidadUbicada(caja, horizontal, vertical);
}
