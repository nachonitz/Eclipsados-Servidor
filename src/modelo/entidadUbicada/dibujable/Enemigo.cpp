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
	this->vidas = 1;
	this->energia = 100;
	hitboxParado.set(66, 18, 123, 235, HBX_DEPTH_DEFECTO);

	estadoActual = new EstadoCaminandoEnemigo(spriteFlip);

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

	estadoActual->actualizarAnimacion(src);
}

void Enemigo::procesarAccion(struct informacionRec info) {
	this->estadoActual = estadoActual->procesarAccion(info);
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

void Enemigo::recibirDanio(int danio){
	this->energia -= danio;
	if(this->energia == 0 && this->vidas > 0){
		this->vidas --;
	}
	estadoActual = new EstadoRecibiendoDanioEnemigo(spriteFlip);

}


