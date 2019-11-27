/*
 * EstadoRecibiendoDanioPersonaje.h
 *
 *  Created on: Nov 27, 2019
 *      Author: fackz
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADORECIBIENDODANIOPERSONAJE_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADORECIBIENDODANIOPERSONAJE_H_

#include "EstadoPersonaje.h"


class EstadoRecibiendoDanioPersonaje : public EstadoPersonaje {

public:
	EstadoRecibiendoDanioPersonaje(SDL_RendererFlip flip, Elemento* elemento);

	EstadoRecibiendoDanioPersonaje(SDL_RendererFlip flip) : EstadoRecibiendoDanioPersonaje(flip, nullptr) {};

	virtual ~EstadoRecibiendoDanioPersonaje();

	EstadoPersonaje* procesarAccion(informacionRec info);
	virtual Hitbox getHitboxActual() {return hitbox[hbxActual];}


private:

	Hitbox hitbox[2];

	int hbxActual;

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADORECIBIENDODANIOPERSONAJE_H_ */
