/*
 * Canio.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#include "../elemento/CanioMetalico.h"

CanioMetalico::CanioMetalico(float x, float y) {
	this->imagen = "sprites/objetos_varios.png";
	setSource(140,70,70,70);
	setDest(x, y, 70, 70);
}

CanioMetalico::~CanioMetalico() {
	// TODO Auto-generated destructor stub
}

