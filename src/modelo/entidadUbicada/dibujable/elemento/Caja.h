/*
 * Caja.h
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CAJA_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CAJA_H_

#include "../elemento/Elemento.h"

class Caja : public Elemento {
public:
	Caja(float x, float y);
	virtual ~Caja();

	float getPosicionX(){return x;}
	float getPosicionY(){return y;}

	void recibirDanio(int danio);

	EstadoPersonaje* getEstadoActual(){return this->estadoActual;}

private:
	float x, y;
};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CAJA_H_ */
