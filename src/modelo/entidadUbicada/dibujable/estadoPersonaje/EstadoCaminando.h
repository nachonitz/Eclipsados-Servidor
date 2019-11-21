/*
 * EstadoCaminando.h
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOCAMINANDO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOCAMINANDO_H_

#include "EstadoPersonaje.h"

class EstadoCaminando: public EstadoPersonaje {
public:
	EstadoCaminando(SDL_RendererFlip flip) :EstadoCaminando(flip,nullptr) {};
	EstadoCaminando(SDL_RendererFlip flip, Elemento* elemento);
	EstadoCaminando(SDL_RendererFlip flip, int fil, int w, int h, int cantSprites, int vel);

	virtual ~EstadoCaminando();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return hitbox[hbxActual];}


private:
	void seguirCaminando(informacionRec info);

	Hitbox hitbox[12];

	int hbxActual = 0;
};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOCAMINANDO_H_ */
