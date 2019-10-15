/*
 * Objeto.h
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_OBJETO_H_
#define SRC_MODELO_OBJETO_H_

#include "../Dibujable.h"

class Elemento : public Dibujable{
public:
	Elemento();
	virtual ~Elemento();

	void setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren);
};

#endif /* SRC_MODELO_OBJETO_H_ */
