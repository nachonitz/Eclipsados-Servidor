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
	float x, y;


	Hitbox hitboxParado;

	Hitbox hitboxCaminando[6];

	Hitbox hitboxGolpeando[666];	//TODO: chequear tamanio

	int hbxActual = 0;

public:
	Enemigo(float horizontal, float vertical);
	virtual ~Enemigo();

	Hitbox getHitbox() {return hitboxParado;}

	int animacionActual(){return this->animActual;}
	int crearCiclo(int f, int w, int h, int cant, int vel);
	void setAnimacionActual(int c, SDL_RendererFlip flip);
	void updateAnim();
	void setFlip(SDL_RendererFlip flip);
	SDL_RendererFlip getFlip(){return spriteFlip;}
	void setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren);
	float getPosHorizontal(){return x;}
	float getPosVertical(){return y;}
};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ENEMIGO_H_ */
