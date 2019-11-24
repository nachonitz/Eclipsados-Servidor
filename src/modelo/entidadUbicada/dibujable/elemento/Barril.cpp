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
	this->vida = 1;
	hitboxElemento.set(0, 0, 100, 100, HBX_DEPTH_DEFECTO);
	estadoActual = new EstadoElemento(SDL_FLIP_NONE, 200, 190, 2);
}

Barril::~Barril() {
	// TODO Auto-generated destructor stub
	hitboxElemento.set(0,0,0,0,0);
}

void Barril::recibirDanio(int danio){
	vida --;
	estadoActual = new EstadoRecibiendoDanioElemento(SDL_FLIP_NONE);
	estadoActual->actualizarAnimacion(src);
	informacionRec info;
	estadoActual = estadoActual->procesarAccion(info);
}

