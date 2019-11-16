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
	int alturaMaximaSalto, alturaActualSalto;

public:
	EstadoSaltandoVertical(SDL_RendererFlip flip, int alturaActual);
	virtual ~EstadoSaltandoVertical();

	EstadoPersonaje* procesarAccion(informacionRec info, EntidadUbicada& entidad);

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOVERTICAL_H_ */
