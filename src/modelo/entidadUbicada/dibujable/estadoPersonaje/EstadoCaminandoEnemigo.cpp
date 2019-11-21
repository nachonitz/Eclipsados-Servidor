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


EstadoCaminandoEnemigo::EstadoCaminandoEnemigo(SDL_RendererFlip flip, int fil, int w, int h, int cantSprites, int vel) {

	this->flip = flip;

	this->ciclo.fil= fil;
	this->ciclo.w= w;
	this->ciclo.h = h;
	this->ciclo.cantSprites= cantSprites;
	this->ciclo.vel= vel;

	ciclo.tick=0;

	//hitbox[0].set(123f,123f,123f,123f,123f);
	//hitbox[1].set(666f,666f,666f,666f,666f);
	// ...

}

EstadoCaminandoEnemigo::~EstadoCaminandoEnemigo() {
	// TODO Auto-generated destructor stub
}


EstadoPersonaje* EstadoCaminandoEnemigo::procesarAccion(informacionRec info) {

	hbxActual = ciclo.tick;

	EstadoPersonaje* nuevoEstado = this;

	return nuevoEstado;
}

