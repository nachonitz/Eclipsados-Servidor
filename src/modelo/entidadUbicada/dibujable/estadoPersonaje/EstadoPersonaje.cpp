/*
 * EstadoPersonaje.cpp
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#include "EstadoQuieto.h"

#include "EstadoPersonaje.h"

#include "../../../nivel/Nivel.h"

Nivel* EstadoPersonaje::nivelActual = nullptr;


void EstadoPersonaje::setNivel(Nivel* nivel) {
	nivelActual = nivel;
}


void EstadoPersonaje::actualizarAnimacion(SDL_Rect& srcDibujable) {

	if (ciclo.tick < 0)
		ciclo.tick = 0;

	int x=ciclo.w*ciclo.tick, y=ciclo.fil*ciclo.h, w=ciclo.w, h=ciclo.h;

	srcDibujable.x=x;
	srcDibujable.y=y;
	srcDibujable.w=w;
	srcDibujable.h=h;

	if(empezar>ciclo.vel){
		ciclo.tick++;
		empezar=0;
	}

	empezar++;
	if(ciclo.tick >= ciclo.cantSprites) {
		ciclo.tick = -1;	//marco a procesarAccion que termino la animacion, por si deberia cambiar de estado
	}

};
