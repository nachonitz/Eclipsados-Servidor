/*
 * EstadoSaltando.h
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDO_H_


#include "EstadoPersonaje.h"

class EstadoSaltando : public EstadoPersonaje {
private:
	float alturaActualSalto;
	int alturaDestInicial;

	void resolverMovimientoHorizontal(int numeroCliente);

	Hitbox hitbox[8];

	int hbxActual = 0;


public:
	EstadoSaltando(SDL_RendererFlip flip, float alturaInicial, Elemento* elemento);

	EstadoSaltando(SDL_RendererFlip flip, float alturaInicial) : EstadoSaltando(flip,alturaInicial, nullptr) {};

	virtual ~EstadoSaltando();

	EstadoPersonaje* procesarAccion(informacionRec info);
	virtual Hitbox getHitboxActual() {return hitbox[hbxActual];}


};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDO_H_ */
