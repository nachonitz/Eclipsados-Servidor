/*
 * EstadoElemento.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#include "EstadoElemento.h"

#include "EstadoQuieto.h"

EstadoElemento::EstadoElemento(SDL_RendererFlip flip) {

	this->flip = flip;

	ciclo.fil=1;
	ciclo.w=100;
	ciclo.h = 100;
	ciclo.cantSprites=1;
	ciclo.vel=4;

	ciclo.tick=0;

	//hitbox[0].set(123f,123f,123f,123f,123f);
	//hitbox[1].set(666f,666f,666f,666f,666f);
	// ...

}

EstadoElemento::~EstadoElemento() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoElemento::procesarAccion(informacionRec info) {

	hbxActual = ciclo.tick;

	EstadoPersonaje* nuevoEstado = this;

	return nuevoEstado;
}

