/*
 * Objeto.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#include "../elemento/Elemento.h"

Elemento::Elemento() {
	// TODO Auto-generated constructor stub

}

Elemento::~Elemento() {
	// TODO Auto-generated destructor stub
}


void Elemento::setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren) {
	asignador.setTexture(*this, ren);
}
