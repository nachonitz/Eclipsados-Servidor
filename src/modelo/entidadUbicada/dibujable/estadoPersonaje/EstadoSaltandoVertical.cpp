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

	alturaActualSalto = alturaInicial;
	alturaMaximaSalto = alturaInicial + 25;

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

	if (alturaActualSalto < alturaMaximaSalto) {
		nivelActual->movimientoSalto(info.numeroDeCliente);
		alturaActualSalto = nivelActual->getAlturaJugador(info.numeroDeCliente);

	}

	if(alturaActualSalto > alturaMaximaSalto) {

		nivelActual->terminoSalto(info.numeroDeCliente);

		nuevoEstado = new EstadoQuieto(info.flip);

	}

	return nuevoEstado;
}

