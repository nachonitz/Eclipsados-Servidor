/*
 * EstadoElemento.h
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOELEMENTO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOELEMENTO_H_

#include "EstadoPersonaje.h"

class EstadoElemento: public EstadoPersonaje {
public:
	EstadoElemento(SDL_RendererFlip flip);

	virtual ~EstadoElemento();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return Hitbox();}

private:

	Hitbox hitbox[1];

	int hbxActual = 0;


};



#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOELEMENTO_H_ */
