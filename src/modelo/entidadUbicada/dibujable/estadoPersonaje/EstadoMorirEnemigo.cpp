/*
 * EstadoMorirEnemigo.cpp
 *
 *  Created on: Nov 23, 2019
 *      Author: notebook
 */

#include "EstadoMorirEnemigo.h"

#include "EstadoQuieto.h"


EstadoMorirEnemigo::EstadoMorirEnemigo(SDL_RendererFlip flip, int f, int w, int h, int cantSprites, int vel, int tick) {

	this->flip = flip;
	this->ciclo.fil=f;
	this->ciclo.w=w;
	this->ciclo.h = h;
	this->ciclo.cantSprites=cantSprites;
	this->ciclo.vel=vel;

	this->ciclo.tick=tick;

	/*for(int i=0; i<3; i++){
		this->hitbox[i].set(0,0,0,0,HBX_DEPTH_DEFECTO);
	}*/



}

EstadoMorirEnemigo::~EstadoMorirEnemigo() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoMorirEnemigo::procesarAccion(informacionRec info) {

	hbxActual = ciclo.tick;
	if(hbxActual < 0){
		return nullptr;
	}

	EstadoPersonaje* nuevoEstado = this;

	return nuevoEstado;
}
