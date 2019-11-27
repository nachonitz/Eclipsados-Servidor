/*
 * EstadoRecibiendoDaño.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#include "EstadoRecibiendoDanioEnemigo.h"

#include "EstadoCaminandoEnemigo.h"


EstadoRecibiendoDanioEnemigo::EstadoRecibiendoDanioEnemigo(SDL_RendererFlip flip) {

	this->flip = flip;
	ciclo.fil=3;
	ciclo.w=220;
	ciclo.h = 264;
	ciclo.cantSprites=2;
	ciclo.vel=10;

	ciclo.tick=0;

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
		return new EstadoCaminandoEnemigo(flip);
	}

	return this;		//ninguna accion, solo animacion de momento
}
