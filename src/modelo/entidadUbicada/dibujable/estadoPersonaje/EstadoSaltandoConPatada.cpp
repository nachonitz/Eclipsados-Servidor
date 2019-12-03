/*
 * EstadoSaltandoConPatada.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"
#include "EstadoSaltandoConPatada.h"

#include "../../../nivel/Nivel.h"

EstadoSaltandoConPatada::EstadoSaltandoConPatada(SDL_RendererFlip flip, float alturaInicial, Elemento* elemento) {

	alturaActualSalto = 0;
	alturaDestInicial = round(alturaInicial);

	this->flip = flip;
	ciclo.fil=4;
	ciclo.w=JUGADOR_SIZE_HORIZONTAL;
	ciclo.h = JUGADOR_SIZE_VERTICAL;
	ciclo.cantSprites=6;
	ciclo.vel=9;

	ciclo.tick=0;
	tickAnterior = 0;

	this->elementoEnMano = elemento;

	for (int i = 0; i < 6; i++){
		//hitbox[i].set(52,32,114,210,HBX_DEPTH_DEFECTO);
	}
	if (flip == SDL_FLIP_HORIZONTAL){
		hitbox[3].set(3,48,165,219,HBX_DEPTH_DEFECTO);
	}
	else{
		/*hitbox[2].set(67,37,102,179,HBX_DEPTH_DEFECTO);

		hitbox[3].set(70,22,111,195,HBX_DEPTH_DEFECTO);

		hitbox[4].set(38,55,147,124,HBX_DEPTH_DEFECTO);

		hitbox[5].set(58,44,119,136,HBX_DEPTH_DEFECTO);*/
		hitbox[3].set(65,48,227,219,HBX_DEPTH_DEFECTO);
	}

}

EstadoSaltandoConPatada::~EstadoSaltandoConPatada() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoSaltandoConPatada::procesarAccion(informacionRec info) {

    EstadoPersonaje* nuevoEstado = this;

    hbxActual = ciclo.tick;

    if (alturaActualSalto <= 0) {
        if(ciclo.tick == 3 && tickAnterior != ciclo.tick){
            nivelActual->movimientoSalto(info.numeroDeCliente, hitbox[hbxActual], DANIO_PATADA);
            tickAnterior = ciclo.tick;
        }else{
            nivelActual->movimientoSalto(info.numeroDeCliente, hitbox[hbxActual], 0);
            }
        alturaActualSalto = nivelActual->getAlturaGlobalJugador(info.numeroDeCliente);
        resolverMovimientoHorizontal(info.numeroDeCliente);
    }

    if(alturaActualSalto > 0){
        ciclo.tick = 0;
        tickAnterior = 0;
        nivelActual->terminoSalto(info.numeroDeCliente, alturaDestInicial);
        nuevoEstado = new EstadoQuieto(info.flip, elementoEnMano);

    }

    return nuevoEstado;
}


void EstadoSaltandoConPatada::resolverMovimientoHorizontal(int numeroCliente) {

	if (flip == SDL_FLIP_NONE)
		nivelActual->movimientoDerecha(numeroCliente, hitbox[hbxActual]);

	else if (flip == SDL_FLIP_HORIZONTAL)
		nivelActual->movimientoIzquierda(numeroCliente, hitbox[hbxActual]);

}
