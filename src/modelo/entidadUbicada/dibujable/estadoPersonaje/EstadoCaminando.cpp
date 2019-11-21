/*
 * EstadoCaminando.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */


#include "EstadoAgachado.h"
#include "EstadoCaminando.h"
#include "EstadoGolpeando.h"
#include "EstadoQuieto.h"
#include "EstadoSaltando.h"
#include "EstadoSaltandoConPatada.h"

#include "../../../nivel/Nivel.h"


EstadoCaminando::EstadoCaminando(SDL_RendererFlip flip, Elemento* elemento) {

	this->flip = flip;

	ciclo.fil=1;
	ciclo.w=230;
	ciclo.h = 280;
	ciclo.cantSprites=12;
	ciclo.vel=4;

	ciclo.tick=0;

	this->elementoEnMano = elemento;

	//hitbox[0].set(123f,123f,123f,123f,123f);
	//hitbox[1].set(666f,666f,666f,666f,666f);
	// ...

}

EstadoCaminando::~EstadoCaminando() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoCaminando::procesarAccion(informacionRec info) {

	hbxActual = ciclo.tick;

	EstadoPersonaje* nuevoEstado = this;

	if (info.animacionActual == ACCION_CAMINAR) {
		seguirCaminando(info);
		return nuevoEstado;
	}

	switch(info.animacionActual){

		case ACCION_SALTO:
			nuevoEstado = new EstadoSaltando(info.flip, nivelActual->getAlturaLocalJugador(info.numeroDeCliente), elementoEnMano);
			break;

		case ACCION_GOLPEAR:
			nuevoEstado = new EstadoGolpeando(info.flip, elementoEnMano);
			break;

		case ACCION_AGACHADO:
			if (elementoEnMano == nullptr)
				nuevoEstado = new EstadoAgachado(info.flip);
			break;

		case ACCION_SALTO_PATADA:
			nuevoEstado = new EstadoSaltandoConPatada(info.flip, nivelActual->getAlturaLocalJugador(info.numeroDeCliente), elementoEnMano);
			break;

		case ACCION_PARADO:
			nuevoEstado = new EstadoQuieto(info.flip, elementoEnMano);
			break;
	}

	return nuevoEstado;

}

void EstadoCaminando::seguirCaminando(informacionRec info) {
	switch(info.movimiento){
		case RIGHT:
			nivelActual->movimientoDerecha(info.numeroDeCliente, hitbox[hbxActual]);
			break;

		case LEFT:
			nivelActual->movimientoIzquierda(info.numeroDeCliente, hitbox[hbxActual]);
			break;

		case UP:
			nivelActual->movimientoArriba(info.numeroDeCliente, hitbox[hbxActual]);
			break;

		case DOWN:
			nivelActual->movimientoAbajo(info.numeroDeCliente, hitbox[hbxActual]);
			break;

		case STAND: break;
	}
}


