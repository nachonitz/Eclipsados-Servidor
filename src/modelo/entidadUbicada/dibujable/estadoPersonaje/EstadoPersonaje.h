/*
 * EstadoPersonaje.h
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_H_

class Nivel;

#include "../../EntidadUbicada.h"

#include "../Hitbox.h"

class EstadoPersonaje {
public:

	virtual EstadoPersonaje* procesarAccion(informacionRec info) = 0;

	virtual void actualizarAnimacion(SDL_Rect& srcDibujable);

	SDL_RendererFlip getFlip() const {return flip;}
	int getTicks(){return ciclo.tick;}

	static void setNivel(Nivel* nivel);

	virtual ~EstadoPersonaje() {};

	virtual Hitbox getHitboxActual() = 0;

	int getElementoEnMano();

protected:
	struct cycle {
		int fil;
		int w;
		int h;
		int cantSprites;
		int vel;
		int tick;
	};

	cycle ciclo;

	SDL_RendererFlip flip;

	static Nivel* nivelActual;

	Elemento* elementoEnMano;

private:

	int empezar;
};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_H_ */
