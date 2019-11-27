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

#include "estadoPersonaje/EstadoCaminandoEnemigo.h"
#include "estadoPersonaje/EstadoRecibiendoDanioEnemigo.h"
#include "estadoPersonaje/EstadoMorirEnemigo.h"


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
	int tipoEnemigo;

	EstadoPersonaje* estadoActual;

	Hitbox hitboxParado;

	Hitbox hitboxCaminando[6];

	Hitbox hitboxGolpeando[666];	//TODO: chequear tamanio

	int hbxActual = 0;
	int vidas, energia, score;

public:
	Enemigo(float horizontal, float vertical, int tipoEnemigo);
	virtual ~Enemigo();

	Hitbox getHitbox() {return hitboxParado;}		//TODO: HARDCODEADO SIEMPRE PARADO!

	int animacionActual(){return this->animActual;}
	int crearCiclo(int f, int w, int h, int cant, int vel);
	void setAnimacionActual(int c, SDL_RendererFlip flip);
	void updateAnim();
	void setFlip(SDL_RendererFlip flip);
	SDL_RendererFlip getFlip(){return spriteFlip;}
	void setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren);
	float getPosHorizontal(){return x;}
	float getPosVertical(){return y;}
	int getVidas(){return this->vidas;}
	EstadoPersonaje* getEstadoActual(){return this->estadoActual;}
	int getTipoEnemigo(){return this->tipoEnemigo;}
	void procesarAccion(struct informacionRec info);

	void moverArribaEnemigo();
	void moverAbajoEnemigo();
	void moverIzquierdaEnemigo(){dest.x -= VELOCIDAD_CODY-1;}
	void moverDerechaEnemigo(){dest.x += VELOCIDAD_CODY-1;}

	int recibirDanio(int danio);
};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ENEMIGO_H_ */
