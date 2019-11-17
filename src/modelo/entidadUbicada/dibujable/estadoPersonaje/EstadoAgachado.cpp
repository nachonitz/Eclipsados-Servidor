/*
 * EstadoAgachado.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */


#include "EstadoAgachado.h"

#include "EstadoQuieto.h"


EstadoAgachado::EstadoAgachado(SDL_RendererFlip flip) {

	this->flip = flip;
	ciclo.fil=0;
	ciclo.w=120;
	ciclo.h = 120;
	ciclo.cantSprites=4;
	ciclo.vel=5;

	ciclo.tick=0;

}

EstadoAgachado::~EstadoAgachado() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoAgachado::procesarAccion(informacionRec info, EntidadUbicada& entidad) {

	if (ciclo.tick < 0)
		return new EstadoQuieto(info.flip);

	return this;		//ninguna accion, solo animacion de momento
}


