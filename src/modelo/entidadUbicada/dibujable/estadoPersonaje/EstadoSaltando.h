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
	int alturaActualSalto, alturaMaximaSalto;
	void resolverMovimientoHorizontal(int numeroCliente);


public:
	EstadoSaltando(SDL_RendererFlip flip, int alturaInicial);
	virtual ~EstadoSaltando();

	EstadoPersonaje* procesarAccion(informacionRec info, EntidadUbicada& entidad);

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDO_H_ */
