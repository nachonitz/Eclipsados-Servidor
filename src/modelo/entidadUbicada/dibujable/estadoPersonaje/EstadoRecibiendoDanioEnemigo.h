/*
 * EstadoRecibiendoDanio.h
 *
 *  Created on: Nov 21, 2019
 *      Author: fackz
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_EstadoRecibiendoDanio_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_EstadoRecibiendoDanio_H_

#include "EstadoPersonaje.h"


class EstadoRecibiendoDanioEnemigo: public EstadoPersonaje {
public:
	EstadoRecibiendoDanioEnemigo(SDL_RendererFlip flip, int fil, int width, int hight, int cantSprites, int vel, int tick);
	virtual ~EstadoRecibiendoDanioEnemigo();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return Hitbox();}

private:

	Hitbox hitbox[2];

	int hbxActual = 0;

};



#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_EstadoRecibiendoDanio_H_ */
