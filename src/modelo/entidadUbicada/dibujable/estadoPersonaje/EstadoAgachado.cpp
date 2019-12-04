/*
 * EstadoAgachado.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */


#include "EstadoAgachado.h"

#include "EstadoQuieto.h"

#include "../../../nivel/Nivel.h"



EstadoAgachado::EstadoAgachado(SDL_RendererFlip flip) {

	this->flip = flip;
	ciclo.fil=0;
	ciclo.w=JUGADOR_SIZE_HORIZONTAL;
	ciclo.h = JUGADOR_SIZE_VERTICAL;
	ciclo.cantSprites=4;
	ciclo.vel=5;

	ciclo.tick=0;

	//hitbox[0].set(...);
	// ...

}

EstadoAgachado::~EstadoAgachado() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoAgachado::procesarAccion(informacionRec info) {

	if ((ciclo.tick == 1 || ciclo.tick == 2) && elementoEnMano == nullptr) {
		elementoEnMano = nivelActual->agarrarObjeto(info.numeroDeCliente, this->hitbox[hbxActual]);
	}

	if (ciclo.tick < 0) {
        ciclo.tick = 0;
		return new EstadoQuieto(info.flip, elementoEnMano);
	}

	return this;		//ninguna accion, solo animacion de momento
}


