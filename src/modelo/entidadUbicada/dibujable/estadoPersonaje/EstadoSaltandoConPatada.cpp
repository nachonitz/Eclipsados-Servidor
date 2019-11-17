/*
 * EstadoSaltandoConPatada.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"
#include "EstadoSaltandoConPatada.h"

#include "../../../nivel/Nivel.h"

EstadoSaltandoConPatada::EstadoSaltandoConPatada(SDL_RendererFlip flip, float alturaInicial) {

	alturaActualSalto = 0;
	alturaDestInicial = round(alturaInicial);

	this->flip = flip;
	ciclo.fil=4;
	ciclo.w=120;
	ciclo.h = 120;
	ciclo.cantSprites=6;
	ciclo.vel=9;

	ciclo.tick=0;

}

EstadoSaltandoConPatada::~EstadoSaltandoConPatada() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoSaltandoConPatada::procesarAccion(informacionRec info) {

	EstadoPersonaje* nuevoEstado = this;

	if (alturaActualSalto <= 0) {
		nivelActual->movimientoSalto(info.numeroDeCliente);
		alturaActualSalto = nivelActual->getAlturaGlobalJugador(info.numeroDeCliente);

		resolverMovimientoHorizontal(info.numeroDeCliente);

	}

	if(alturaActualSalto > 0){

		nivelActual->terminoSalto(info.numeroDeCliente, alturaDestInicial);
		nuevoEstado = new EstadoQuieto(info.flip);

	}

	return nuevoEstado;
}

void EstadoSaltandoConPatada::resolverMovimientoHorizontal(int numeroCliente) {

	if (flip == SDL_FLIP_NONE)
		nivelActual->movimientoDerecha(numeroCliente);

	else if (flip == SDL_FLIP_HORIZONTAL)
		nivelActual->movimientoIzquierda(numeroCliente);

}
