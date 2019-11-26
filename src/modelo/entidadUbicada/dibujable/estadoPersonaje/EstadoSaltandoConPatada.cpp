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

	this->elementoEnMano = elemento;

	/*for (int i = 0; i < 6; i++){
		hitbox[i].set(52,32,114,210,HBX_DEPTH_DEFECTO);
	}

	hitbox[2].set(3,20,227,200,HBX_DEPTH_DEFECTO);
	hitbox[3].set(3,20,227,200,HBX_DEPTH_DEFECTO);
	hitbox[4].set(3,20,227,200,HBX_DEPTH_DEFECTO);*/
}

EstadoSaltandoConPatada::~EstadoSaltandoConPatada() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoSaltandoConPatada::procesarAccion(informacionRec info) {

	EstadoPersonaje* nuevoEstado = this;


	if (alturaActualSalto <= 0) {
		if(ciclo.tick >= 2 && ciclo.tick <= 4){
			nivelActual->movimientoSalto(info.numeroDeCliente, hitbox[hbxActual], DANIO_PATADA);
		}else{
			nivelActual->movimientoSalto(info.numeroDeCliente, hitbox[hbxActual], 0);
			alturaActualSalto = nivelActual->getAlturaGlobalJugador(info.numeroDeCliente);
			resolverMovimientoHorizontal(info.numeroDeCliente);
			}
	}
	hbxActual ++;

	if(alturaActualSalto > 0){
		hbxActual = 0;
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
