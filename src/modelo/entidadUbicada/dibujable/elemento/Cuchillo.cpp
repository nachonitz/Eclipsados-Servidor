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
	this->score = PUNTOS_CUCHILLO;
	this->vidas = 3;
	hitboxElemento.set(14, 18, 31, 0, HBX_DEPTH_DEFECTO);
	estadoActual = new EstadoElemento(SDL_FLIP_NONE, 0, 0, 0);
}

Cuchillo::~Cuchillo() {
	// TODO Auto-generated destructor stub
}

int Cuchillo::recibirDanio(int danio){

	this->vidas --;
	return this->score;
}
