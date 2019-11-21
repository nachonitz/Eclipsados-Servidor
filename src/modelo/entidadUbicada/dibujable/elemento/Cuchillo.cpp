/*
 * Cuchillo.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#include "../elemento/Cuchillo.h"

Cuchillo::Cuchillo(float x, float y) {
	this->imagen = "sprites/objetos_varios.png";
	setSource(0,0,70,70);
	setDest(x, y, 70, 70);

	hitboxElemento.set(14, 18, 31, 31, HBX_DEPTH_DEFECTO);

}

Cuchillo::~Cuchillo() {
	// TODO Auto-generated destructor stub
}

