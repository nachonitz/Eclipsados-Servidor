#ifndef NIVEL_H_
#define NIVEL_H_



#include <stdio.h>
#include <vector>
#include "../Sonido.h"
#include "../entidadUbicada/EntidadUbicada.h"
#include "../entidadUbicada/FactoryEntidadUbicada.h"
#include "../nivel/Capa.h"
#include <stdlib.h>
#include <time.h>
#include "../../Logger.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
//#include "cody.h"

class Nivel {
public:
	Nivel(int NumeroNivel,EntidadUbicada* jugador, int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos);
	virtual ~Nivel();

	void setImagesCapas(SDL_Renderer *ren, char const* imagen1, char const* imagen2, char const* imagen3);

	void movimientoArriba();
	void movimientoAbajo();
	void movimientoIzquierda();
	void movimientoDerecha();
	void movimientoSalto();
	void terminoSalto();
	bool terminoElNivel();

	void moverEnemigos();

	Capa* getCapa1(){return &capa1;}
	Capa* getCapa2(){return &capa2;}
	Capa* getCapa3(){return &capa3;}

	vector<EntidadUbicada*> getElementos(){return elementos;}
	vector<EntidadUbicada*> getEnemigos(){return enemigos;}

	Personaje* getPersonaje();

private:
	void moverCapasDerecha();
	void moverCapasIzquierda();
	void moverElementosIzquierda();
	void moverElementosDerecha();
	void moverEnemigosIzquierda();
	void moverEnemigosDerecha();

	int generarXaleatorio();
	int generarYaleatorio();
	int generarYaleatorioObjetos();

	int movimientoEnemigos;

	void ubicarEnemigosYElementos(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos);


	void inicializarCapa(Capa capa);

	FactoryEntidadUbicada factory;

	std::vector<EntidadUbicada*> enemigos;
	std::vector<EntidadUbicada*> elementos;

	EntidadUbicada* cody;

	Capa capa1;
	Capa capa2;
	Capa capa3;
	//Cody cody;

	int pos_borde_izquierda = 0;
	int pos_borde_derecha = WINDOW_SIZE_HORIZONTAL;

	Sonido *musicaFondo;


};
#endif /* NIVEL_H_ */
