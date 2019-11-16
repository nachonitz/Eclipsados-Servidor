/*
 * EstadoSaltandoConPatada.h
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOCONPATADA_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOCONPATADA_H_

#include "EstadoPersonaje.h"

class EstadoSaltandoConPatada : public EstadoPersonaje {
private:
	int alturaMaximaSalto, alturaActualSalto;

	void resolverMovimientoHorizontal(int numeroCliente);

public:
	EstadoSaltandoConPatada(SDL_RendererFlip flip, int alturaActual);
	virtual ~EstadoSaltandoConPatada();

	EstadoPersonaje* procesarAccion(informacionRec info, EntidadUbicada& entidad);

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOCONPATADA_H_ */
