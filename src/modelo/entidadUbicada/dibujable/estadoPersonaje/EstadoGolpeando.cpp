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
	ciclo.w=JUGADOR_SIZE_HORIZONTAL;
	ciclo.h = JUGADOR_SIZE_VERTICAL;
	ciclo.cantSprites=3;
	ciclo.vel=5;

	ciclo.tick=0;
	tickAnterior = 0;

	this->elementoEnMano = elemento;



	if (flip == SDL_FLIP_HORIZONTAL){
		for (int i = 0; i < 9; i++){
			hitbox[i].set(10,48,136,219,HBX_DEPTH_DEFECTO);
		}
		hitbox[1].set(10,48,117,219,HBX_DEPTH_DEFECTO);
		hitbox[3].set(13,84,217,184,HBX_DEPTH_DEFECTO);
		hitbox[8].set(76,6,11,263,HBX_DEPTH_DEFECTO);
	}
	else{
		for (int i = 0; i < 9; i++){
			hitbox[i].set(65,48,136,219,HBX_DEPTH_DEFECTO);
		}
		hitbox[1].set(65,48,172,219,HBX_DEPTH_DEFECTO);
		hitbox[3].set(13,84,217,184,HBX_DEPTH_DEFECTO);
		hitbox[8].set(76,6,11,263,HBX_DEPTH_DEFECTO);
	}



}

EstadoGolpeando::~EstadoGolpeando() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoGolpeando::procesarAccion(informacionRec info) {
	bool hizoDanio;
	hbxActual = ciclo.tick;

	if(tickAnterior != ciclo.tick){
		if(ciclo.tick == 1 /*|| ciclo.tick == 3 || (ciclo.tick >= 6 && ciclo.tick <= 8)*/ ){
			if(this->elementoEnMano){
				hizoDanio = nivelActual->hacerDanio(info.numeroDeCliente, this->hitbox[hbxActual], this->elementoEnMano->getDanioElemento(), this->elementoEnMano->getScore());
				if(hizoDanio){
					elementoEnMano->registrarUnUso();
				}
				if(this->elementoEnMano->getVidas() <=0){
					this->elementoEnMano = nullptr;
				}
			}else{
				nivelActual->hacerDanio(info.numeroDeCliente, this->hitbox[hbxActual], DANIO_PUNIO, PUNTOS_PUNIO);
			}
			tickAnterior = ciclo.tick;
		}
	}

	if (ciclo.tick < 0){
		ciclo.tick = 0;
		tickAnterior = 0;
		return new EstadoQuieto(info.flip, elementoEnMano);
	}

	return this;		//ninguna accion, solo animacion de momento
}


