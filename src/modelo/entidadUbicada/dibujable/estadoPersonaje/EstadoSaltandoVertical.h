/*
 * EstadoSaltandoVertical.h
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOVERTICAL_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOVERTICAL_H_

#include "EstadoPersonaje.h"

class EstadoSaltandoVertical: public EstadoPersonaje {
private:
	float alturaActualSalto;
	int alturaDestInicial;

	Hitbox hitbox[7];

	int hbxActual = 0;

public:
	EstadoSaltandoVertical(SDL_RendererFlip flip, float alturaActual) : EstadoSaltandoVertical(flip,alturaActual,nullptr) {};
	EstadoSaltandoVertical(SDL_RendererFlip flip, float alturaActual, Elemento* elemento);

	virtual ~EstadoSaltandoVertical();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return hitbox[hbxActual];}


};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOVERTICAL_H_ */
