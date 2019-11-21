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

	this->hitbox[0].set(50,46,124,209,HBX_DEPTH_DEFECTO);

	this->hitbox[1].set(44,11,103,245,HBX_DEPTH_DEFECTO);


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
