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

	int recibirDanio(int danio);

	EstadoPersonaje* getEstadoActual(){return this->estadoActual;}

	int getScore(){return PUNTOS_CANIO;}

	int getDanioElemento(){return DANIO_CANIO;}

	int getVidas(){return this->vidas;}

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CANIOMETALICO_H_ */
