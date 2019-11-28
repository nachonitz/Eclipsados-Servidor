/*
 * EstadoGolpeandoEnemigo.h
 *
 *  Created on: Nov 27, 2019
 *      Author: fackz
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOGOLPEANDOENEMIGO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOGOLPEANDOENEMIGO_H_

#include "EstadoPersonaje.h"


class EstadoGolpeandoEnemigo: public EstadoPersonaje {
public:
	EstadoGolpeandoEnemigo(SDL_RendererFlip flip,  EntidadUbicada* jugador, int fil, int width, int hight, int cantSprites, int vel, int tick, int tipoEnemigo);
	virtual ~EstadoGolpeandoEnemigo();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return Hitbox();}

private:

	Hitbox hitbox[3];

	int hbxActual = 0;

	int tickAnterior, tipoEnemigo;

	EntidadUbicada* jugador;

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOGOLPEANDOENEMIGO_H_ */
