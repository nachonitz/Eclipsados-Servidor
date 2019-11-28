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
	this->tipoEnemigo = tipoEnemigo;
	this->vidas = 1;
	this->score = PUNTOS_ENEMIGO;
	if(tipoEnemigo != FINAL_BOSS){
		this->setDest(horizontal, vertical, 220, 264);
		this->energia = 100;
		hitboxParado.set(66, 18, 123, 235, HBX_DEPTH_DEFECTO);
		estadoActual = new EstadoCaminandoEnemigo(spriteFlip,0, 220, 264, 6, 7, 0);
	}else{
		this->setDest(horizontal, vertical, 325, 280);
		this->energia = 500;
		hitboxParado.set(66, 18, 123, 235, HBX_DEPTH_DEFECTO);
		estadoActual = new EstadoCaminandoEnemigo(spriteFlip,0,325,280,3,7,3);
	}

}

Enemigo::~Enemigo() {
	// TODO Auto-generated destructor stub
}

void Enemigo::moverArribaEnemigo(){
	if(dest.y > WINDOW_SIZE_VERTICAL - MARGEN_PISO_ARRIBA){
		dest.y -= (VELOCIDAD_CODY-1)/2;
	}
}

void Enemigo::moverAbajoEnemigo(){
	if(dest.y < WINDOW_SIZE_VERTICAL - MARGEN_PISO_ABAJO){
		dest.y += (VELOCIDAD_CODY-1)/2;
	}
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
	if(estadoActual != NULL){
		this->estadoActual = estadoActual->procesarAccion(info);
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

int Enemigo::recibirDanio(int danio){
	this->energia -= danio;
	if(this->energia <= 0 && this->vidas > 0){
		this->vidas --;
	}
	if(this->vidas == 0){
		estadoActual = new EstadoMorirEnemigo(spriteFlip,4, 220, 264, 3, 10, 0);
		return this->score;
	}else{
		estadoActual = new EstadoRecibiendoDanioEnemigo(spriteFlip,3, 220, 264, 2, 10, 0);
		return 0;
	}

}

void Enemigo::golpear(EntidadUbicada* jugador){

	estadoActual = new EstadoGolpeandoEnemigo(spriteFlip, jugador, 2, 220, 264, 3, 7, 0, this->tipoEnemigo);
}


