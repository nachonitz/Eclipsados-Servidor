/*
 * EstadoGolpeando.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoGolpeando.h"
#include "EstadoQuieto.h"


EstadoGolpeando::EstadoGolpeando(SDL_RendererFlip flip) {

	this->flip = flip;
	ciclo.fil=3;
	ciclo.w=120;
	ciclo.h = 120;
	ciclo.cantSprites=9;
	ciclo.vel=5;

	ciclo.tick=0;

}

EstadoGolpeando::~EstadoGolpeando() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoGolpeando::procesarAccion(informacionRec info) {
	if (ciclo.tick < 0)
		return new EstadoQuieto(info.flip);

	return this;		//ninguna accion, solo animacion de momento
}


