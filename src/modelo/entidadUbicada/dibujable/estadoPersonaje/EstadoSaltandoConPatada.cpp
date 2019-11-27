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
	ciclo.w=230;
	ciclo.h = 280;
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
