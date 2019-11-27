/*
 * EstadoGolpeandoEnemigoEnemigo.cpp
 *
 *  Created on: Nov 27, 2019
 *      Author: fackz
 */

#include "EstadoGolpeandoEnemigo.h"
#include "EstadoQuieto.h"
#include "../../../nivel/Nivel.h"


EstadoGolpeandoEnemigo::EstadoGolpeandoEnemigo(SDL_RendererFlip flip, EntidadUbicada* jugador) {

	this->flip = flip;
	ciclo.fil=2;
	ciclo.w=220;
	ciclo.h = 264;
	ciclo.cantSprites=3;
	ciclo.vel=7;

	ciclo.tick=0;
	tickAnterior = 0;
	this->jugador = jugador;

	/*if (flip == SDL_FLIP_HORIZONTAL){
		for (int i = 0; i < 3; i++){
			hitbox[i].set(10,48,136,219,HBX_DEPTH_DEFECTO);
		}
		hitbox[1].set(10,48,117,219,HBX_DEPTH_DEFECTO);
	}
	else{
		for (int i = 0; i < 3; i++){
			hitbox[i].set(65,48,136,219,HBX_DEPTH_DEFECTO);
		}
		hitbox[1].set(65,48,172,219,HBX_DEPTH_DEFECTO);
	}*/



}

EstadoGolpeandoEnemigo::~EstadoGolpeandoEnemigo() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoGolpeandoEnemigo::procesarAccion(informacionRec info) {

	hbxActual = ciclo.tick;

	if(tickAnterior != ciclo.tick && ciclo.tick == 1){
		nivelActual->hacerDanioEnemigo(this->jugador, this->hitbox[hbxActual], DANIO_ENEMIGO);
		tickAnterior = ciclo.tick;
	}

	if (ciclo.tick < 0){
		ciclo.tick = 0;
		tickAnterior = 0;
		//enemigoGolpeando = false;
		return new EstadoCaminandoEnemigo(this->flip);
	}

	return this;		//ninguna accion, solo animacion de momento
}


