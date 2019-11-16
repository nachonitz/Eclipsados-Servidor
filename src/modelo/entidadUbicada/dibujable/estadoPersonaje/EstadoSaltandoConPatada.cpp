/*
 * EstadoSaltandoConPatada.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"
#include "EstadoSaltandoConPatada.h"

#include "../../../nivel/Nivel.h"

EstadoSaltandoConPatada::EstadoSaltandoConPatada(SDL_RendererFlip flip, int alturaInicial) {

	alturaActualSalto = alturaInicial;
	alturaMaximaSalto = alturaInicial + 25;

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

EstadoPersonaje* EstadoSaltandoConPatada::procesarAccion(informacionRec info, EntidadUbicada& entidad) {

	EstadoPersonaje* nuevoEstado = this;

	if (alturaActualSalto < alturaMaximaSalto) {
		entidad.moverLocalSalto();
		entidad.moverGlobalSalto();
		alturaActualSalto = entidad.getPosicionGlobal()->getVertical();

		resolverMovimientoHorizontal(info.numeroDeCliente);

	}

	if(alturaActualSalto > alturaMaximaSalto){

		entidad.terminoGlobalSalto();
		entidad.terminoLocalSalto();

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
