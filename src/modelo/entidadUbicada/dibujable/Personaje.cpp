#include "Personaje.h"

#include "../../../Logger.h"


Personaje::Personaje() {

	estadoActual = new EstadoQuieto(SDL_FLIP_NONE);
	this->score = 0;
	this->energia = 100;
	this->vidas = 3;
	this->imagen = "sprites/SpriteCodyCompleto.png"; //obsoleto!
	this->muerto = false;
}


Personaje::~Personaje() {
	//SDL_DestroyTexture(tex); Lo saco porque lo hice en dibujable
}

void Personaje::procesarAccion(struct informacionRec info) {

	this->estadoActual = estadoActual->procesarAccion(info);

}

void Personaje::resetearEstado() {
	delete estadoActual;
	this->estadoActual = new EstadoQuieto(SDL_FLIP_NONE);
}

Hitbox Personaje::getHitbox() {
	if (hitboxEnabled)
		return estadoActual->getHitboxActual();
	return Hitbox(0,0,0,0,0);	// null hitbox
}

void Personaje::disableHitbox(){
	hitboxEnabled = false;
}

void Personaje::enableHitbox(){
	hitboxEnabled = true;
}

void Personaje::updateAnim(){

	estadoActual->actualizarAnimacion(src);

}

int Personaje::getElementoEnMano() {
	return estadoActual->getElementoEnMano();
}

int Personaje::recibirDanio(int danio){

	if (!this->estadoActual->puedeRecibirDanio()) {
		return 0;
	}

	this->energia -= danio;

	if(this->energia <= 0 && this->vidas > 0){

		if (testMode)
			return 0;

		this->vidas --;
		if(this->vidas <= 0){
			estadoActual = estadoActual->morir(this->vidas);
			this->muerto = true;
			return 0;
		}
		this->energia = 100;
		estadoActual = estadoActual->morir(this->vidas);
		return 0;
	}

	estadoActual = estadoActual->recibirDanio();
	return 0;
}


/*void Personaje::setAnimacionActual(int c, SDL_RendererFlip flip) {
	empezar = 0;
	animaciones[c].tick = 0;
	animActual = c;
	spriteFlip = flip;
}*/
/*
bool Personaje::llegoAlBorde(int Xpos, int WindowSizeHorizontal){
	bool llegoAlBorde = false;

	if(Xpos <= 100){
		llegoAlBorde = false;
	}
	else if(Xpos >= WindowSizeHorizontal - 200 ){
		llegoAlBorde = false;
	}

	return llegoAlBorde;
}
*/
/*void Personaje::setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren) {
	asignador.setTexture(*this, ren);
}*/

