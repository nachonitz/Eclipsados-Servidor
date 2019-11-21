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


EstadoCaminandoEnemigo::EstadoCaminandoEnemigo(SDL_RendererFlip flip) {

	this->flip = flip;

	this->flip = flip;
	ciclo.fil=1;
	ciclo.w=220;
	ciclo.h = 264;
	ciclo.cantSprites=6;
	ciclo.vel=5;

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

