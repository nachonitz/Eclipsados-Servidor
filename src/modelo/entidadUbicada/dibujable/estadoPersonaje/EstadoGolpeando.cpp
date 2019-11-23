/*
 * EstadoGolpeando.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoGolpeando.h"
#include "EstadoQuieto.h"
#include "../../../nivel/Nivel.h"


EstadoGolpeando::EstadoGolpeando(SDL_RendererFlip flip, Elemento* elemento) {

	this->flip = flip;
	ciclo.fil=3;
	ciclo.w=230;
	ciclo.h = 280;
	ciclo.cantSprites=9;
	ciclo.vel=5;

	ciclo.tick=0;

	this->elementoEnMano = elemento;

	for (int i = 0; i < 9; i++){
		hitbox[i].set(50,52,136,214,HBX_DEPTH_DEFECTO);
	}

	hitbox[1].set(54,47,172,222,HBX_DEPTH_DEFECTO);
	hitbox[3].set(13,84,217,184,HBX_DEPTH_DEFECTO);
	hitbox[8].set(76,6,11,263,HBX_DEPTH_DEFECTO);


}

EstadoGolpeando::~EstadoGolpeando() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoGolpeando::procesarAccion(informacionRec info) {

	if(ciclo.tick == 1 || ciclo.tick == 3 || ciclo.tick == 8){
		nivelActual->hacerDanio(info.numeroDeCliente, this->hitbox[hbxActual], 20);
	}
	hbxActual ++;

	if (ciclo.tick < 0){
		hbxActual = 0;
		return new EstadoQuieto(info.flip, elementoEnMano);
	}

	return this;		//ninguna accion, solo animacion de momento
}


