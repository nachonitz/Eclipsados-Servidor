/*
 * EstadoRecibiendoDanioElemento.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#include "EstadoRecibiendoDanioElemento.h"
#include <iostream>
#include "EstadoQuieto.h"


EstadoRecibiendoDanioElemento::EstadoRecibiendoDanioElemento(SDL_RendererFlip flip) {

	this->flip = flip;
	ciclo.fil=3;
	ciclo.w=100;
	ciclo.h = 100;
	ciclo.cantSprites=1;
	ciclo.vel=5;

	ciclo.tick=0;

	//this->hitbox[0].set(6,52,90,47,HBX_DEPTH_DEFECTO);

	contadorPasoDelTiempo = 0;

}

void EstadoRecibiendoDanioElemento::actualizarAnimacion(SDL_Rect& srcDibujable) {

//Es un falso ciclo para que muestre la animacion de la caja/barril rotos

	contadorPasoDelTiempo ++;
	if(contadorPasoDelTiempo > 50){
		ciclo.tick = -1;
	}

}

EstadoRecibiendoDanioElemento::~EstadoRecibiendoDanioElemento() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoRecibiendoDanioElemento::procesarAccion(informacionRec info) {

	hbxActual = ciclo.tick;
	if(hbxActual < 0){
		return nullptr;
	}

	EstadoPersonaje* nuevoEstado = this;

	return nuevoEstado;
}


