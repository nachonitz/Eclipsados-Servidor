/*
 * EstadoSaltando.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"
#include "EstadoSaltando.h"

#include "../../../nivel/Nivel.h"



EstadoSaltando::EstadoSaltando(SDL_RendererFlip flip, float alturaInicial, Elemento* elemento) {

	alturaActualSalto = 0;
	alturaDestInicial = round(alturaInicial);

	this->flip = flip;
	ciclo.fil=2;
	ciclo.w=JUGADOR_SIZE_HORIZONTAL;
	ciclo.h = JUGADOR_SIZE_VERTICAL;
	ciclo.cantSprites=8;
	ciclo.vel=6;

	ciclo.tick=0;

	this->elementoEnMano = elemento;

	// hitbox[j].set(...)
	// ...

	//TODO: CAMBIAR SEGUN FLIP!

	hitbox[2].set(67,37,102,179,HBX_DEPTH_DEFECTO);

	hitbox[3].set(70,22,111,195,HBX_DEPTH_DEFECTO);

	hitbox[4].set(38,55,147,124,HBX_DEPTH_DEFECTO);

	hitbox[5].set(58,44,119,136,HBX_DEPTH_DEFECTO);

	hitbox[6].set(48,56,155,119,HBX_DEPTH_DEFECTO);

	hitbox[7].set(62,71,122,145,HBX_DEPTH_DEFECTO);

}

EstadoSaltando::~EstadoSaltando() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoSaltando::procesarAccion(informacionRec info) {

	EstadoPersonaje* nuevoEstado = this;

	if (alturaActualSalto <= 0) {
		nivelActual->movimientoSalto(info.numeroDeCliente, hitbox[hbxActual],0);
		alturaActualSalto = nivelActual->getAlturaGlobalJugador(info.numeroDeCliente);

		resolverMovimientoHorizontal(info.numeroDeCliente);

	}

	if(alturaActualSalto > 0){

        ciclo.tick = 0;

		nivelActual->terminoSalto(info.numeroDeCliente, alturaDestInicial);

		nuevoEstado = new EstadoQuieto(info.flip, elementoEnMano);

	}

	return nuevoEstado;
}

void EstadoSaltando::resolverMovimientoHorizontal(int numeroCliente) {

	if (flip == SDL_FLIP_NONE)
		nivelActual->movimientoDerecha(numeroCliente, hitbox[hbxActual]);

	else if (flip == SDL_FLIP_HORIZONTAL)
		nivelActual->movimientoIzquierda(numeroCliente, hitbox[hbxActual]);

}


