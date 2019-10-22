/*
 * Barril.h
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_BARRIL_H_
#define SRC_MODELO_BARRIL_H_

#include "../elemento/Elemento.h"

class Barril : public Elemento {
public:
	Barril(float x, float y);
	virtual ~Barril();
};

#endif /* SRC_MODELO_BARRIL_H_ */
