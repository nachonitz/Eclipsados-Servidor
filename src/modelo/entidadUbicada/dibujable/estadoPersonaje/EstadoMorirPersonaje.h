/*
 * EstadoMorirPersonaje.h
 *
 *  Created on: Nov 27, 2019
 *      Author: fackz
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOMORIRPERSONAJE_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOMORIRPERSONAJE_H_


#include "EstadoPersonaje.h"


class EstadoMorirPersonaje : public EstadoPersonaje {

public:
	EstadoMorirPersonaje(SDL_RendererFlip flip, int vidas) : EstadoMorirPersonaje(flip,vidas,nullptr) {};
	EstadoMorirPersonaje(SDL_RendererFlip flip, int vidas, Elemento* elementoEnMano);

	virtual ~EstadoMorirPersonaje();

	EstadoPersonaje* procesarAccion(informacionRec info);
	virtual Hitbox getHitboxActual() {return hitbox[hbxActual];}


private:

	Hitbox hitbox[4];
	int hbxActual, vidas;

};



#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOMORIRPERSONAJE_H_ */
