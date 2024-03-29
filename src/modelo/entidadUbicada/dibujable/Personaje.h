#ifndef PERSONAJE_H_
#define PERSONAJE_H_
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace  std;
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "estadoPersonaje/EstadoQuieto.h"
#include "estadoPersonaje/EstadoRecibiendoDanioPersonaje.h"
#include "estadoPersonaje/EstadoMorirPersonaje.h"

//#define SPEED 10

#include "Dibujable.h"

class Personaje : public Dibujable {
private:
	struct cycle {
		int fil;
		int w;
		int h;
		int cantSprites;
		int vel;
		int tick;
	};
	//vector<cycle> animaciones;
/*	SDL_Texture* tex;
	SDL_RendererFlip spriteFlip;
	int animActual;
	int empezar;*/

	EstadoPersonaje* estadoActual;
	int score, vidas, energia;
	bool muerto;

	bool testMode = false;

	bool hitboxEnabled = true;
	bool reconectado = false;

public:
	Personaje();
	virtual ~Personaje();

	virtual Hitbox getHitbox();

	//int crearCiclo(int f, int w, int h, int cant, int vel);
	//void setAnimacionActual(int c, SDL_RendererFlip flip);
	void updateAnim();
	//void updateDest(int x, int y);
	//SDL_Rect getDest() const {return dest;}
	//SDL_Rect getSource() const {return src;}
	//SDL_Texture* getTexture() const {return tex;}
	SDL_RendererFlip getFlip() const {return estadoActual->getFlip();}
	int getTicks(){return estadoActual->getTicks();}
	//void setDest(int x, int y, int w, int h);
	//void setSource(int x, int y, int w, int h);
	//void setImage(SDL_Renderer *ren);
	bool llegoAlBorde(int Xpos, int WindowSizeHorizontal);

	void procesarAccion(struct informacionRec info);

	void resetearEstado();
	EstadoPersonaje* getEstadoActual(){return this->estadoActual;}
	int getElementoEnMano();
	int getScore(){return score;}
	int getVidas(){return vidas;}
	int getEnergia(){return energia;}
	bool getEstadoMuerto(){return muerto;}
	void aumentarScore(int incremento){this->score += incremento;}

	virtual int recibirDanio(int danio);

	bool toggleTestMode() {testMode = !testMode; return testMode;};

	void disableTestMode() {testMode = false;}

	void disableHitbox();

	void enableHitbox();
	void reconexion(){
		reconectado = true;
	}

	bool seReconecto(){
		return reconectado;
	}
};

#endif /* PERSONAJE_H_ */
