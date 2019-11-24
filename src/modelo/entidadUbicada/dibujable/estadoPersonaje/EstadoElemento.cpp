/*
 * EstadoElemento.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#include "EstadoElemento.h"

#include "EstadoQuieto.h"

EstadoElemento::EstadoElemento(SDL_RendererFlip flip, int w, int h, int fil) {

	this->flip = flip;

	ciclo.fil=fil;
	ciclo.w=w;
	ciclo.h = h;
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

