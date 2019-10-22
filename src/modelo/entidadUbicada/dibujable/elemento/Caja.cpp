/*
 * Caja.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#include "../elemento/Caja.h"

Caja::Caja(float x, float y) {
	this->imagen = "sprites/objetos_varios.png";
	setSource(0,200,100,100);
	setDest(x, y, 100, 100);
}

Caja::~Caja() {
	// TODO Auto-generated destructor stub
}

