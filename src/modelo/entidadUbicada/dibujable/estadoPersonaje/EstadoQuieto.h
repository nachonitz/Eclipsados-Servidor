/*
 * EstadoQuieto.h
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOQUIETO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOQUIETO_H_


#include "EstadoPersonaje.h"


class EstadoQuieto : public EstadoPersonaje {
public:
	EstadoQuieto(SDL_RendererFlip flip);
	virtual ~EstadoQuieto();

	EstadoPersonaje* procesarAccion(informacionRec info);
	virtual Hitbox getHitboxActual() {return hitbox;}


private:

	Hitbox hitbox;

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOQUIETO_H_ */
