/*
 * EstadoSaltandoConPatada.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"
#include "EstadoSaltandoVertical.h"

#include "../../../nivel/Nivel.h"


EstadoSaltandoVertical::EstadoSaltandoVertical(SDL_RendererFlip flip, float alturaInicial, Elemento* elemento) {

	alturaActualSalto = 0;	//comienza en el piso
	alturaDestInicial = round(alturaInicial);

	this->flip = flip;

	ciclo.fil=5;

	ciclo.w=JUGADOR_SIZE_HORIZONTAL;
	ciclo.h = JUGADOR_SIZE_VERTICAL;
	ciclo.cantSprites=7;
	ciclo.vel=8;

	this->elementoEnMano = elemento;

	ciclo.tick=0;

}

EstadoSaltandoVertical::~EstadoSaltandoVertical() {
	// TODO Auto-generated destructor stub
}


EstadoPersonaje* EstadoSaltandoVertical::procesarAccion(informacionRec info) {

	EstadoPersonaje* nuevoEstado = this;

	//recordar que el eje z esta invertido, por temas de SDL
	if (alturaActualSalto <= 0) {
		nivelActual->movimientoSalto(info.numeroDeCliente, hitbox[hbxActual],0);
		alturaActualSalto = nivelActual->getAlturaGlobalJugador(info.numeroDeCliente);

	}

	if(alturaActualSalto > 0) {

        ciclo.tick = 0;

		nivelActual->terminoSalto(info.numeroDeCliente, alturaDestInicial);

		nuevoEstado = new EstadoQuieto(info.flip, elementoEnMano);

	}

	return nuevoEstado;
}

