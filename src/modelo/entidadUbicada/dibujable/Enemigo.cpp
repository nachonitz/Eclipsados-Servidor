/*
 * Enemigo.cpp
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#include "Enemigo.h"

Enemigo::Enemigo(float horizontal, float vertical, int tipoEnemigo) {
	/*x = horizontal;
	y = vertical;*/
	this->setDest(horizontal, vertical, 220, 264);
	this->tipoEnemigo = tipoEnemigo;
	hitboxParado.set(66, 18, 123, 235, HBX_DEPTH_DEFECTO);

}

Enemigo::~Enemigo() {
	// TODO Auto-generated destructor stub
}

void Enemigo::setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren) {
	asignador.setTexture(*this, ren);
	setSource(0,0,100,125);
}

int Enemigo::crearCiclo(int f, int w, int h, int cantSprites, int vel){
	cycle tmp;
	tmp.fil=f-1;
	tmp.w=w;
	tmp.cantSprites=cantSprites;
	tmp.vel=vel;
	tmp.tick=0;
	tmp.h = h;
	animaciones.push_back(tmp);
	return animaciones.size()-1;
}

void Enemigo::updateAnim(){

	setSource(animaciones[animActual].w*animaciones[animActual].tick, animaciones[animActual].fil*animaciones[animActual].h, animaciones[animActual].w, animaciones[animActual].h);
	if(empezar>animaciones[animActual].vel){
		animaciones[animActual].tick++;
		empezar=0;
	}
	empezar++;
	if(animaciones[animActual].tick >= animaciones[animActual].cantSprites) {
		animaciones[animActual].tick = 0;
	}
}

void Enemigo::setAnimacionActual(int c, SDL_RendererFlip flip) {
	empezar = 0;
	animaciones[c].tick = 0;
	animActual = c;
	spriteFlip = flip;
}

void Enemigo::setFlip(SDL_RendererFlip flip){

	spriteFlip = flip;
}


