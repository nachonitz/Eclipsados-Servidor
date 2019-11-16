/*
 * EstadoSaltandoConPatada.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"
#include "EstadoSaltandoVertical.h"

EstadoSaltandoVertical::EstadoSaltandoVertical(SDL_RendererFlip flip, int alturaInicial) {

	alturaActualSalto = alturaInicial;
	alturaMaximaSalto = alturaInicial + 25;

	this->flip = flip;

	ciclo.fil=4;
	ciclo.w=120;
	ciclo.h = 120;
	ciclo.cantSprites=6;
	ciclo.vel=8;

	ciclo.tick=0;

}

EstadoSaltandoVertical::~EstadoSaltandoVertical() {
	// TODO Auto-generated destructor stub
}


EstadoPersonaje* EstadoSaltandoVertical::procesarAccion(informacionRec info, EntidadUbicada& entidad) {

	EstadoPersonaje* nuevoEstado = this;

	if (alturaActualSalto < alturaMaximaSalto) {
		entidad.moverLocalSalto();
		entidad.moverGlobalSalto();
		alturaActualSalto = entidad.getPosicionGlobal()->getVertical();

	}

	if(alturaActualSalto > alturaMaximaSalto){

		entidad.terminoGlobalSalto();
		entidad.terminoLocalSalto();

		nuevoEstado = new EstadoQuieto(info.flip);

	}

	return nuevoEstado;
}

