/*
 * EstadoCaminandoEnemigoEnemigo.cpp
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#include "EstadoAgachado.h"
#include "EstadoCaminando.h"
#include "EstadoGolpeando.h"
#include "EstadoQuieto.h"
#include "EstadoSaltando.h"
#include "EstadoSaltandoConPatada.h"

#include "../../../nivel/Nivel.h"


EstadoCaminandoEnemigo::EstadoCaminandoEnemigo(SDL_RendererFlip flip, int f, int w, int h, int cantSprites, int vel, int tick) {

	this->flip = flip;
	this->ciclo.fil=f;
	this->ciclo.w=w;
	this->ciclo.h = h;
	this->ciclo.cantSprites=cantSprites;
	this->ciclo.vel=vel;

	this->ciclo.tick=tick;

	/*for(int i = 0; i < 6; i++){
		hitbox[i].set(39,12,159,243,HBX_DEPTH_DEFECTO);
	}*/
	//hitbox[1].set(666f,666f,666f,666f,666f);
	// ...

}

EstadoCaminandoEnemigo::~EstadoCaminandoEnemigo() {
	// TODO Auto-generated destructor stub
}


EstadoPersonaje* EstadoCaminandoEnemigo::procesarAccion(informacionRec info) {

	hbxActual = ciclo.tick;

	if(hbxActual < 0){
		ciclo.tick = 0;
	}
	EstadoPersonaje* nuevoEstado = this;

	return nuevoEstado;
}

