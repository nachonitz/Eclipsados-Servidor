/*
 * EstadoMorirEnemigo.h
 *
 *  Created on: Nov 23, 2019
 *      Author: notebook
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOMORIRENEMIGO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOMORIRENEMIGO_H_

#include "EstadoPersonaje.h"


class EstadoMorirEnemigo: public EstadoPersonaje {
public:
	EstadoMorirEnemigo(SDL_RendererFlip flip, int fil, int width, int hight, int cantSprites, int vel, int tick);
	virtual ~EstadoMorirEnemigo();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return Hitbox();}

private:

	Hitbox hitbox[3];

	int hbxActual = 0;

};




#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOMORIRENEMIGO_H_ */
