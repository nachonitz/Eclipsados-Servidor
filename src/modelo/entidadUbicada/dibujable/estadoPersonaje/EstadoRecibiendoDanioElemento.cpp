/*
 * EstadoRecibiendoDanioElemento.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#include "EstadoRecibiendoDanioElemento.h"

#include "EstadoQuieto.h"


EstadoRecibiendoDanioElemento::EstadoRecibiendoDanioElemento(SDL_RendererFlip flip) {

	this->flip = flip;
	ciclo.fil=3;
	ciclo.w=100;
	ciclo.h = 100;
	ciclo.cantSprites=1;
	ciclo.vel=5;

	ciclo.tick=0;

	this->hitbox[0].set(0,0,100,100,HBX_DEPTH_DEFECTO);



}

EstadoRecibiendoDanioElemento::~EstadoRecibiendoDanioElemento() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoRecibiendoDanioElemento::procesarAccion(informacionRec info) {


//borrar del mapa
}


