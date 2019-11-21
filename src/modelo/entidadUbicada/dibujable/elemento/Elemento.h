/*
 * Objeto.h
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_OBJETO_H_
#define SRC_MODELO_OBJETO_H_

#include "../Dibujable.h"
#include "../estadoPersonaje/EstadoElemento.h"
#include "../estadoPersonaje/EstadoRecibiendoDanioElemento.h"

class Elemento : public Dibujable{
protected:
	Hitbox hitboxElemento;
	EstadoPersonaje* estadoActual;

public:
	Elemento();
	virtual ~Elemento();

	Hitbox getHitbox() {return hitboxElemento;}

	void setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren);

	void recibirDanio(int danio);

};

#endif /* SRC_MODELO_OBJETO_H_ */
