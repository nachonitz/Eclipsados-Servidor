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
	this->vidas = 2;
	this->score = PUNTOS_CAJA;
	hitboxElemento.set(0, 0, 100, 100, HBX_DEPTH_DEFECTO);
	estadoActual = new EstadoElemento(SDL_FLIP_NONE, 0, 200, 2);
	this->enElPiso = true;
}

Caja::~Caja() {
	// TODO Auto-generated destructor stub
	hitboxElemento.set(0,0,0,0,0);
}

int Caja::recibirDanio(int danio){
	int puntaje = PRIMER_GOLPE_A_CAJA;
	vidas --;
	if(vidas == 0){
		estadoActual = new EstadoRecibiendoDanioElemento(SDL_FLIP_NONE);
		setSource(0,300,100,100);
		estadoActual->actualizarAnimacion(src);
		informacionRec info;
		estadoActual = estadoActual->procesarAccion(info);
		puntaje = this->score;
		return this->score;
	}
	return puntaje;

}

