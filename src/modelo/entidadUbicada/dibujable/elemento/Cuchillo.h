/*
 * Cuchillo.h
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CUCHILLO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CUCHILLO_H_

#include "../elemento/Elemento.h"

class Cuchillo : public Elemento {
public:
	Cuchillo(float x, float y);
	virtual ~Cuchillo();

	bool sePuedeAgarrar() override {return true;}

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ELEMENTO_CUCHILLO_H_ */
