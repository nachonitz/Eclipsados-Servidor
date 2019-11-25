/*
 * Objeto.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#include "../elemento/Elemento.h"

Elemento::Elemento() {

}

Elemento::~Elemento() {

}


void Elemento::setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren) {
	asignador.setTexture(*this, ren);
}

void Elemento::recibirDanio(int danio){

}

void Elemento::updateAnim(){

	estadoActual->actualizarAnimacion(src);
	informacionRec info;
	estadoActual = estadoActual->procesarAccion(info);
}
