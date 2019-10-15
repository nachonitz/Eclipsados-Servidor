/*
 * Enemigo.h
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ENEMIGO_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ENEMIGO_H_

#include "Dibujable.h"
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace  std;


class Enemigo : public Dibujable {
private:
	struct cycle {
		int fil;
		int w;
		int h;
		int cantSprites;
		int vel;
		int tick;
	};
	vector<cycle> animaciones;
	SDL_Texture* tex;
	SDL_RendererFlip spriteFlip;
	int animActual;
	int empezar;
	bool rev,nAb;
	int newAnim;
public:
	Enemigo();
	virtual ~Enemigo();

	int crearCiclo(int f, int w, int h, int cant, int vel);
	void setAnimacionActual(int c, SDL_RendererFlip flip);
	void updateAnim();
	void setFlip(SDL_RendererFlip flip);
	SDL_RendererFlip getFlip(){return spriteFlip;}
	void setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren);
};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ENEMIGO_H_ */
