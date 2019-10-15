#include "Personaje.h"

Personaje::Personaje() {
	this->imagen = "sprites/SpriteCodyCompleto.png";
}


Personaje::~Personaje() {
	//SDL_DestroyTexture(tex); Lo saco porque lo hice en dibujable
}


int Personaje::crearCiclo(int f, int w, int h, int cantSprites, int vel){
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

void Personaje::updateAnim(){

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

void Personaje::setAnimacionActual(int c, SDL_RendererFlip flip) {
	empezar = 0;
	animaciones[c].tick = 0;
	animActual = c;
	spriteFlip = flip;
}
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
void Personaje::setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren) {
	asignador.setTexture(*this, ren);
}

