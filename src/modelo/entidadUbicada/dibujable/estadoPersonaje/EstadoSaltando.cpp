/*
 * EstadoSaltando.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"
#include "EstadoSaltando.h"

#include "../../../nivel/Nivel.h"



EstadoSaltando::EstadoSaltando(SDL_RendererFlip flip, float alturaInicial) {

	alturaActualSalto = 0;
	alturaDestInicial = round(alturaInicial);

	this->flip = flip;
	ciclo.fil=2;
	ciclo.w=120;
	ciclo.h = 120;
	ciclo.cantSprites=8;
	ciclo.vel=6;

	ciclo.tick=0;


}

EstadoSaltando::~EstadoSaltando() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoSaltando::procesarAccion(informacionRec info) {

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

void EstadoSaltando::resolverMovimientoHorizontal(int numeroCliente) {

	if (flip == SDL_FLIP_NONE)
		nivelActual->movimientoDerecha(numeroCliente);

	else if (flip == SDL_FLIP_HORIZONTAL)
		nivelActual->movimientoIzquierda(numeroCliente);

}


