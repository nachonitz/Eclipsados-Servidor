/*
 * EstadoGolpeando.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoGolpeando.h"
#include "EstadoQuieto.h"


EstadoGolpeando::EstadoGolpeando(SDL_RendererFlip flip, Elemento* elemento) {

	this->flip = flip;
	ciclo.fil=3;
	ciclo.w=230;
	ciclo.h = 280;
	ciclo.cantSprites=9;
	ciclo.vel=5;

	ciclo.tick=0;

	this->elementoEnMano = elemento;

}

EstadoGolpeando::~EstadoGolpeando() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoGolpeando::procesarAccion(informacionRec info) {
	if (ciclo.tick < 0)
		return new EstadoQuieto(info.flip, elementoEnMano);

	return this;		//ninguna accion, solo animacion de momento
}


