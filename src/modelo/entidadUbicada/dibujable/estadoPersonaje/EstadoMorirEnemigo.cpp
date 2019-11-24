/*
 * EstadoMorirEnemigo.cpp
 *
 *  Created on: Nov 23, 2019
 *      Author: notebook
 */

#include "EstadoMorirEnemigo.h"

#include "EstadoQuieto.h"


EstadoMorirEnemigo::EstadoMorirEnemigo(SDL_RendererFlip flip) {

	this->flip = flip;
	ciclo.fil=4;
	ciclo.w=220;
	ciclo.h = 264;
	ciclo.cantSprites=3;
	ciclo.vel=8;

	ciclo.tick=0;

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
