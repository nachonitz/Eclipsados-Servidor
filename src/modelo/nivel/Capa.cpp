
#include "Capa.h"

#include "../../Logger.h"

Capa::Capa() {

}

Capa::~Capa() {
}

void Capa::setDest(int x, int y, int w, int h){
	dest.x=x;
	dest.y=y;
	dest.w=w;
	dest.h=h;

}
void Capa::setSource(int x, int y, int w, int h){
	src.x=x;
	src.y=y;
	src.w=w;
	src.h=h;

}
void Capa::setImage(SDL_Renderer* ren, char const * imagen){

	SDL_Surface* surf = IMG_Load(imagen);


	if (surf == nullptr) {

	    tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 500, 500);

	    Uint32 * pixels = new Uint32[500* 500];

	    memset(pixels, 50*(this->velocidad), 500* 500* sizeof(Uint32));

	    SDL_UpdateTexture(tex, NULL, pixels, 500* sizeof(Uint32));

	    Logger::getInstance()->log(ERROR, "No se encuentra el sprite para capa, se mostrara una textura erronea.");
	}
	else
		tex = SDL_CreateTextureFromSurface(ren, surf);
}

void Capa::moverDerecha(){
		dest.x +=  velocidad;
}
void Capa::moverIzquierda(){
		dest.x -=  velocidad;
}

/*
bool Capa::llegoAlBordeDerecho(){
	if(src.x >= ANCHO_CAPA_PIXELES){
		return true;
	}
	return false;

}
bool Capa::llegoAlBordeIzquierdo(){
	if(src.x <= 0){
		return true;
	}
	return false;
}
*/
