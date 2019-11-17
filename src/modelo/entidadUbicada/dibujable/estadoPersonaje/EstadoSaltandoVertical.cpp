/*
 * EstadoSaltandoConPatada.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"
#include "EstadoSaltandoVertical.h"

#include "../../../nivel/Nivel.h"


EstadoSaltandoVertical::EstadoSaltandoVertical(SDL_RendererFlip flip, float alturaInicial) {

	alturaActualSalto = 0;	//comienza en el piso
	alturaDestInicial = round(alturaInicial);

	this->flip = flip;

	ciclo.fil=5;
	ciclo.w=120;
	ciclo.h = 120;
	ciclo.cantSprites=7;
	ciclo.vel=8;

	ciclo.tick=0;

}

EstadoSaltandoVertical::~EstadoSaltandoVertical() {
	// TODO Auto-generated destructor stub
}


EstadoPersonaje* EstadoSaltandoVertical::procesarAccion(informacionRec info) {

	EstadoPersonaje* nuevoEstado = this;

	//recordar que el eje z esta invertido, por temas de SDL
	if (alturaActualSalto <= 0) {
		nivelActual->movimientoSalto(info.numeroDeCliente);
		alturaActualSalto = nivelActual->getAlturaGlobalJugador(info.numeroDeCliente);

	}

	if(alturaActualSalto > 0) {

		nivelActual->terminoSalto(info.numeroDeCliente, alturaDestInicial);

		nuevoEstado = new EstadoQuieto(info.flip);

	}

	return nuevoEstado;
}

