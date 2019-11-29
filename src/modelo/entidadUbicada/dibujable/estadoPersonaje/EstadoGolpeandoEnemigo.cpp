/*
 * EstadoGolpeandoEnemigoEnemigo.cpp
 *
 *  Created on: Nov 27, 2019
 *      Author: fackz
 */

#include "EstadoGolpeandoEnemigo.h"
#include "EstadoQuieto.h"
#include "../../../nivel/Nivel.h"


EstadoGolpeandoEnemigo::EstadoGolpeandoEnemigo(SDL_RendererFlip flip, EntidadUbicada* jugador , int f, int w, int h, int cantSprites, int vel, int tick, int tipoEnemigo) {

	this->flip = flip;
	this->ciclo.fil=f;
	this->ciclo.w=w;
	this->ciclo.h = h;
	this->ciclo.cantSprites=cantSprites;
	this->ciclo.vel=vel;

	this->ciclo.tick=tick;
	tickAnterior = 0;
	this->jugador = jugador;
	this->tipoEnemigo = tipoEnemigo;

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
		if(this->tipoEnemigo != FINAL_BOSS){
			return new EstadoCaminandoEnemigo(this->flip,1, 220, 264, 5, 7, 0);
		}else{
			 return new EstadoCaminandoEnemigo(flip,0,325,280,6,7,0);
		}
	}

	return this;		//ninguna accion, solo animacion de momento
}


