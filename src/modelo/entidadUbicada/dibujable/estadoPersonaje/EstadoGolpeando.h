/*
 * EstadoGolpeando.h
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOGOLPEANDO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOGOLPEANDO_H_

#include "EstadoPersonaje.h"

class EstadoGolpeando: public EstadoPersonaje {
public:
	EstadoGolpeando(SDL_RendererFlip flip) : EstadoGolpeando(flip, nullptr) {};
	EstadoGolpeando(SDL_RendererFlip flip, Elemento* elemento);

	virtual ~EstadoGolpeando();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return Hitbox();}

private:

	Hitbox hitbox[9];

	int hbxActual = 0;

	int tickAnterior;


};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOGOLPEANDO_H_ */
