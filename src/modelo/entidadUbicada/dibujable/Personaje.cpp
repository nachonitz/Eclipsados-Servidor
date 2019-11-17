#include "Personaje.h"

#include "../../../Logger.h"



Personaje::Personaje() {

	estadoActual = new EstadoQuieto(SDL_FLIP_NONE);


	this->imagen = "sprites/SpriteCodyCompleto.png";
}


Personaje::~Personaje() {
	//SDL_DestroyTexture(tex); Lo saco porque lo hice en dibujable
}

void Personaje::procesarAccion(struct informacionRec info, EntidadUbicada& entidadResponsable) {

	this->estadoActual = estadoActual->procesarAccion(info, entidadResponsable);

}

void Personaje::resetearEstado() {
	delete estadoActual;
	this->estadoActual = new EstadoQuieto(SDL_FLIP_NONE);
}

/*
int Personaje::crearCiclo(int f, int w, int h, int cantSprites, int vel){
	cycle ciclo;
	ciclo.fil=f-1;
	ciclo.w=w;
	ciclo.cantSprites=cantSprites;
	ciclo.vel=vel;
	ciclo.tick=0;
	ciclo.h = h;

	animaciones.push_back(ciclo);
	return animaciones.size()-1;


}
*/

void Personaje::updateAnim(){

	estadoActual->actualizarAnimacion(src);

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

