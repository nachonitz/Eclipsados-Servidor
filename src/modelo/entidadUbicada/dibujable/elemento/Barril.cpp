/*
 * Barril.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#include "../elemento/Barril.h"

Barril::Barril(float x, float y) {
	this->imagen = "sprites/objetos_varios.png";
	setSource(200,200,100,100);
	setDest(x, y, 100+90, 100+160);
	this->vidas = 1;
	this->score = PUNTOS_BARRIL;
	hitboxElemento.set(19+30, 19+42, 58+35, 69+105, HBX_DEPTH_DEFECTO);
	estadoActual = new EstadoElemento(SDL_FLIP_NONE, 200, 200, 2);
}

Barril::~Barril() {
	// TODO Auto-generated destructor stub
	hitboxElemento.set(0,0,0,0,0);
}

int Barril::recibirDanio(int danio){
	vidas --;
	estadoActual = new EstadoRecibiendoDanioElemento(SDL_FLIP_NONE);
	setSource(200,300,100,100);
	estadoActual->actualizarAnimacion(src);
	informacionRec info;
	estadoActual = estadoActual->procesarAccion(info);
	return this->score;
}

