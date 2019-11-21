/*
 * EstadoQuieto.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */


#include "EstadoAgachado.h"
#include "EstadoCaminando.h"
#include "EstadoGolpeando.h"
#include "EstadoQuieto.h"
#include "EstadoSaltando.h"
#include "EstadoSaltandoConPatada.h"
#include "EstadoSaltandoVertical.h"

#include "../../../nivel/Nivel.h"



EstadoQuieto::EstadoQuieto(SDL_RendererFlip flip) {

	this->flip = flip;

	ciclo.fil=0;
	ciclo.w=230;
	ciclo.h = 280;
	ciclo.cantSprites=1;
	ciclo.vel=10;

	ciclo.tick=0;

	//hitbox(123.0,123.0,123.0,123.0,123.0);

}

EstadoQuieto::~EstadoQuieto() {
	// TODO Auto-generated destructor stub
}

EstadoPersonaje* EstadoQuieto::procesarAccion(informacionRec info) {

	EstadoPersonaje* nuevoEstado = this;

	switch(info.animacionActual){

		case ACCION_SALTO_VERTICAL:
			nuevoEstado = new EstadoSaltandoVertical(info.flip, nivelActual->getAlturaLocalJugador(info.numeroDeCliente));
			break;

		case ACCION_GOLPEAR:
			nuevoEstado = new EstadoGolpeando(info.flip);
			break;

		case ACCION_AGACHADO:
			nuevoEstado = new EstadoAgachado(info.flip);
			break;

		case ACCION_CAMINAR:
			nuevoEstado = new EstadoCaminando(info.flip);
			break;

		case ACCION_PARADO:
			return this;
	}

	return nuevoEstado;

}


