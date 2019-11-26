#include "Personaje.h"

#include "../../../Logger.h"



Personaje::Personaje() {

	estadoActual = new EstadoQuieto(SDL_FLIP_NONE);
	this->score = 0;
	this->energia = 100;
	this->vidas = 3;
	this->imagen = "sprites/SpriteCodyCompleto.png"; //obsoleto!
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
	return estadoActual->getHitboxActual();
}

void Personaje::updateAnim(){

	estadoActual->actualizarAnimacion(src);

}

int Personaje::getElementoEnMano() {
	return estadoActual->getElementoEnMano();
}

int Personaje::recibirDanio(int danio){
	this->energia -= danio;
	if(this->energia == 0 && this->vidas > 0){
		this->vidas --;
		this->energia = 100;
	}

	//estadoActual = new EstadoRecibiendoDanioPersonaje(info.flip);

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

