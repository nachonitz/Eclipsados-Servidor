/*
 * EstadoAgachado.h
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOAGACHADO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOAGACHADO_H_

#include "EstadoPersonaje.h"

class EstadoAgachado: public EstadoPersonaje {
public:
	EstadoAgachado(SDL_RendererFlip flip);
	virtual ~EstadoAgachado();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return Hitbox();}


};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOAGACHADO_H_ */
