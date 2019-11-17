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


EstadoCaminando::EstadoCaminando(SDL_RendererFlip flip) {

	this->flip = flip;

	ciclo.fil=1;
	ciclo.w=120;
	ciclo.h = 120;
	ciclo.cantSprites=12;
	ciclo.vel=4;

	ciclo.tick=0;

}

EstadoCaminando::~EstadoCaminando() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoCaminando::procesarAccion(informacionRec info) {
	/*if (info.animacionActual != ACCION_CAMINAR)
		throw std::invalid_argument("EstadoCaminando: intento procesar animacionActual != ACCION_CAMINAR!");
	*/

	EstadoPersonaje* nuevoEstado = this;

	if (info.animacionActual == ACCION_CAMINAR) {
		seguirCaminando(info);
		return nuevoEstado;
	}

	switch(info.animacionActual){

		case ACCION_SALTO:
			nuevoEstado = new EstadoSaltando(info.flip, nivelActual->getAlturaLocalJugador(info.numeroDeCliente));
			break;

		case ACCION_GOLPEAR:
			nuevoEstado = new EstadoGolpeando(info.flip);
			break;

		case ACCION_AGACHADO:
			nuevoEstado = new EstadoAgachado(info.flip);
			break;

		case ACCION_SALTO_PATADA:
			nuevoEstado = new EstadoSaltandoConPatada(info.flip, nivelActual->getAlturaLocalJugador(info.numeroDeCliente));
			break;

		case ACCION_PARADO:
			nuevoEstado = new EstadoQuieto(info.flip);
			break;
	}

	return nuevoEstado;

}


void EstadoCaminando::seguirCaminando(informacionRec info) {
	switch(info.movimiento){
		case RIGHT:
			nivelActual->movimientoDerecha(info.numeroDeCliente);
			break;

		case LEFT:
			nivelActual->movimientoIzquierda(info.numeroDeCliente);
			break;

		case UP:
			nivelActual->movimientoArriba(info.numeroDeCliente);
			break;

		case DOWN:
			nivelActual->movimientoAbajo(info.numeroDeCliente);
			break;

		case STAND: break;
	}
}


