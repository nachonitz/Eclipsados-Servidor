/*
 * EstadoRecibiendoDanioPersonaje.cpp
 *
 *  Created on: Nov 27, 2019
 *      Author: fackz
 */

#include "EstadoRecibiendoDanioPersonaje.h"

#include "../../../nivel/Nivel.h"


EstadoRecibiendoDanioPersonaje::EstadoRecibiendoDanioPersonaje(SDL_RendererFlip flip, Elemento* elemento) {

	this->flip = flip;
	ciclo.fil=6;
	ciclo.w=JUGADOR_SIZE_HORIZONTAL;
	ciclo.h = JUGADOR_SIZE_VERTICAL;
	ciclo.cantSprites=2;
	ciclo.vel=10;

	ciclo.tick=0;
	this->hbxActual = 0;
	this->elementoEnMano = elemento;

	if (flip == SDL_FLIP_HORIZONTAL){
		for (int i = 0; i < 2; i++){
			hitbox[i].set(10,48,136,219,HBX_DEPTH_DEFECTO);
		}
	}
	else{
		for (int i = 0; i < 2; i++){
			hitbox[i].set(65,48,136,219,HBX_DEPTH_DEFECTO);
		}
	}


}

EstadoRecibiendoDanioPersonaje::~EstadoRecibiendoDanioPersonaje() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoRecibiendoDanioPersonaje::procesarAccion(informacionRec info) {


	if (ciclo.tick < 0){
		hbxActual = 0;
	return new EstadoQuieto(flip);
	}

	return this;		//ninguna accion, solo animacion de momento
}


