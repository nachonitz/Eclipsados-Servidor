/*
 * EstadoSaltando.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"
#include "EstadoSaltando.h"

#include "../../../nivel/Nivel.h"



EstadoSaltando::EstadoSaltando(SDL_RendererFlip flip, int alturaInicial) {

	alturaActualSalto = alturaInicial;
	alturaMaximaSalto = alturaInicial + 25;

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

EstadoPersonaje* EstadoSaltando::procesarAccion(informacionRec info, EntidadUbicada& entidad) {

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

void EstadoSaltando::resolverMovimientoHorizontal(int numeroCliente) {

	Logger::getInstance()->log(DEBUG, "FLIP: " + std::to_string(flip) + ". NUMERO CLIENTE:" + std::to_string(numeroCliente));

	if (flip == SDL_FLIP_NONE)
		nivelActual->movimientoDerecha(numeroCliente);

	else if (flip == SDL_FLIP_HORIZONTAL)
		nivelActual->movimientoIzquierda(numeroCliente);

}


