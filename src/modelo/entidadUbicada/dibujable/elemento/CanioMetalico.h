/*
 * Canio.h
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CANIOMETALICO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CANIOMETALICO_H_

#include "../elemento/Elemento.h"

class CanioMetalico : public Elemento {
public:
	CanioMetalico(float x, float y);
	virtual ~CanioMetalico();

	bool sePuedeAgarrar() override {return true;}

	void recibirDanio(int danio);

	EstadoPersonaje* getEstadoActual(){return this->estadoActual;}

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CANIOMETALICO_H_ */
