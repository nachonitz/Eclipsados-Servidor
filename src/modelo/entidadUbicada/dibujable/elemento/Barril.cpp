/*
 * Barril.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#include "../elemento/Barril.h"

Barril::Barril(float x, float y) {
	this->imagen = "sprites/objetos_varios.png";
	setSource(200,190,100,100);
	setDest(x, y, 100, 100);

	hitboxElemento.set(0, 0, 100, 100, HBX_DEPTH_DEFECTO);
}

Barril::~Barril() {
	// TODO Auto-generated destructor stub
}

