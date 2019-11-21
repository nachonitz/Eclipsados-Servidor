/*
 * EstadoCaminandoEnemigo.h
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOCAMINANDOENEMIGO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOCAMINANDOENEMIGO_H_

#include "EstadoPersonaje.h"

class EstadoCaminandoEnemigo: public EstadoPersonaje {
public:
	EstadoCaminandoEnemigo(SDL_RendererFlip flip);

	virtual ~EstadoCaminandoEnemigo();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return hitbox[hbxActual];}


private:
	void seguirCaminando();

	Hitbox hitbox[12];

	int hbxActual = 0;
};



#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOCAMINANDOENEMIGO_H_ */
