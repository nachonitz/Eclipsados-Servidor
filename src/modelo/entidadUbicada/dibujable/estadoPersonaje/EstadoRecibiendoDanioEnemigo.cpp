/*
 * EstadoRecibiendoDaño.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#include "EstadoRecibiendoDanioEnemigo.h"

#include "EstadoCaminandoEnemigo.h"


EstadoRecibiendoDanioEnemigo::EstadoRecibiendoDanioEnemigo(SDL_RendererFlip flip, int f, int w, int h, int cantSprites, int vel, int tick, int tipoEnemigo) {

	this->flip = flip;
	this->ciclo.fil=f;
	this->ciclo.w=w;
	this->ciclo.h = h;
	this->ciclo.cantSprites=cantSprites;
	this->ciclo.vel=vel;
	this->tipoEnemigo = tipoEnemigo;

	this->ciclo.tick=tick;

	/*if (flip == SDL_FLIP_HORIZONTAL){
		for (int i = 0; i < 2; i++){
			hitbox[i].set(10,48,136,219,HBX_DEPTH_DEFECTO);
		}
	}
	else{
		for (int i = 0; i < 2; i++){
			hitbox[i].set(65,48,136,219,HBX_DEPTH_DEFECTO);
		}
	}*/


}

EstadoRecibiendoDanioEnemigo::~EstadoRecibiendoDanioEnemigo() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoRecibiendoDanioEnemigo::procesarAccion(informacionRec info) {


	if (ciclo.tick < 0){
		hbxActual = 0;
		if (this->tipoEnemigo != FINAL_BOSS){
			return new EstadoCaminandoEnemigo(flip,1, 220, 264, 6, 7, 0);
		}else{
			return new EstadoCaminandoEnemigo(flip,0,325,280,6,7,0);
		}

	}

	return this;		//ninguna accion, solo animacion de momento
}
