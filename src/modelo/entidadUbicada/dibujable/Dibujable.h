#ifndef SRC_MODELO_DIBUJABLE_H_
#define SRC_MODELO_DIBUJABLE_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../../defs.h"

#include "../../../AsignadorDeTexturas.h"

#include "Hitbox.h"

#include <string>

class Dibujable {
public:
	Dibujable();
	virtual ~Dibujable() {SDL_DestroyTexture(tex);};

	SDL_Rect getDest() const {return dest;}
	SDL_Rect getSource() const {return src;}
	SDL_Texture* getTexture() const {return tex;}

	void setDest(int x, int y, int w, int h);
	void setSource(int x, int y, int w, int h);
	void setImage(SDL_Renderer *ren, std::string imagen);
	void updateDest(int x, int y);

	void moverArriba();
	void moverAbajo();

//-L-> cambio velocidad_cody/2 para que los objetos se muevan con la primer capa
	//void moverIzquierda(){dest.x -= VELOCIDAD_CODY/2;}
	//void moverDerecha(){dest.x += VELOCIDAD_CODY/2;}
	void moverIzquierda(){dest.x -= VELOCIDAD_CODY;}
	void moverDerecha(){dest.x += VELOCIDAD_CODY;}
	void moverSalto();
	void terminoSalto(int alturaLocalInicial){velocidadSalto = VELOCIDAD_SALTO_INICIAL; dest.y = alturaLocalInicial;}


	bool estaBordeDerecho();
	bool estaBordeIzquierdo();

	int getWidth(){return src.w;}
	int getHeight(){return src.h;}

	virtual Hitbox getHitbox() = 0;

	virtual bool sePuedeAgarrar() {return false;}

	virtual void recibirDanio(int danio) = 0;


	//virtual void setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren) = 0;

protected:
	SDL_Texture* tex;
	SDL_Rect dest;
	SDL_Rect src;
	char const* imagen;
	float velocidadSalto;
};

#endif /* SRC_MODELO_DIBUJABLE_H_ */
