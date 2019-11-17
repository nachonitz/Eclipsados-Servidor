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
	EstadoCaminando(SDL_RendererFlip flip);
	virtual ~EstadoCaminando();

	EstadoPersonaje* procesarAccion(informacionRec info);

private:
	void seguirCaminando(informacionRec info);
};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOCAMINANDO_H_ */
