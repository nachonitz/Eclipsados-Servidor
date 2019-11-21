/*
 * Objeto.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#include "../elemento/Elemento.h"

Elemento::Elemento() {

	//estadoActual = new EstadoElemento(SDL_FLIP_NONE);

}

Elemento::~Elemento() {

}


void Elemento::setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren) {
	asignador.setTexture(*this, ren);
}

void Elemento::recibirDanio(int danio){

	estadoActual = new EstadoRecibiendoDanioElemento(SDL_FLIP_NONE);
	estadoActual->actualizarAnimacion(src);
}
