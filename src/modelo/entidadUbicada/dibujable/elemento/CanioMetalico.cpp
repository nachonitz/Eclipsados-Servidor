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

	hitboxElemento.set(6, 13, 51, 0, HBX_DEPTH_DEFECTO);
	estadoActual = new EstadoElemento(SDL_FLIP_NONE, 140, 70, 1);

}

CanioMetalico::~CanioMetalico() {
	// TODO Auto-generated destructor stub
}

void CanioMetalico::recibirDanio(int danio){


}

