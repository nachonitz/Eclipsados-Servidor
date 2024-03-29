/*
 * EstadoMorirPersonaje.cpp
 *
 *  Created on: Nov 27, 2019
 *      Author: fackz
 */

#include "EstadoMorirPersonaje.h"
#include "EstadoQuieto.h"


#include "../../../nivel/Nivel.h"


EstadoMorirPersonaje::EstadoMorirPersonaje(SDL_RendererFlip flip, int vidas, Elemento* elemento) {

	this->flip = flip;
	ciclo.fil=6;
	ciclo.w=JUGADOR_SIZE_HORIZONTAL;
	ciclo.h = JUGADOR_SIZE_VERTICAL;
	ciclo.cantSprites=7;
	ciclo.vel=12;

	ciclo.tick=3;
	hbxActual=0;
	this->elementoEnMano = elemento;
	this->vidas = vidas;

	if(this->vidas == 0){
		for (int i = 0; i < 4; i++){
			hitbox[i].set(0,0,0,0,0);
		}
		return;
	}

	if (flip == SDL_FLIP_HORIZONTAL){
		for (int i = 0; i < 4; i++){
			hitbox[i].set(10,48,136,219,HBX_DEPTH_DEFECTO);
		}
	}
	else{
		for (int i = 0; i < 4; i++){
			hitbox[i].set(65,48,136,219,HBX_DEPTH_DEFECTO);
		}
	}


}

EstadoMorirPersonaje::~EstadoMorirPersonaje() {
	// TODO Auto-generated destructor stub
}


EstadoPersonaje* EstadoMorirPersonaje::procesarAccion(informacionRec info) {

	EstadoPersonaje* nuevoEstado;
	hbxActual = ciclo.tick;

	if(hbxActual < 0 && vidas != 0){
		return nuevoEstado = new EstadoQuieto(info.flip,this->elementoEnMano);
	}

	nuevoEstado = this;

	return nuevoEstado;
}


