#ifndef NIVEL_H_
#define NIVEL_H_


#include "../../defs.h"
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
struct animado{
	//SDL_Texture* txt;
	bool estaActivo;
	SDL_Rect dest;
	SDL_Rect src;
	SDL_RendererFlip flip;
};

struct elemento{
	//SDL_Texture* txt;
	SDL_Rect dest;
	SDL_Rect src;
};

struct capa{
	//SDL_Texture* txt;
	int nivel;
	SDL_Rect dest;
	SDL_Rect src;
};

struct informacionEnv{
	struct elemento elementos[MAX_CANT_ELEMENTOS];
	struct capa capas[3];
	struct animado animados[MAX_CANT_ANIMADOS];
	int cantAnimados;
	int cantElementos;
	int cantJugadores;
};
class Nivel {
public:
	Nivel(int NumeroNivel,vector<EntidadUbicada*>& jugadores, int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos);
	virtual ~Nivel();

	void setImagesCapas(SDL_Renderer *ren, char const* imagen1, char const* imagen2, char const* imagen3);

	void movimientoArriba(int numeroJugador);
	void movimientoAbajo(int numeroJugador);
	void movimientoIzquierda(int numeroJugador);
	void movimientoDerecha(int numeroJugador);
	void movimientoSalto(int numeroJugador);
	void terminoSalto(int numeroJugador);
	bool terminoElNivel();

	void moverCapaDerecha(){moverCapasIzquierda();}

	void actualizarAnimaciones();
	struct informacionEnv getInformacion();

	void moverEnemigos();

	Capa* getCapa1(){return &capa1;}
	Capa* getCapa2(){return &capa2;}
	Capa* getCapa3(){return &capa3;}

	vector<EntidadUbicada*> getElementos(){return elementos;}
	vector<EntidadUbicada*> getEnemigos(){return enemigos;}

	Personaje* getPersonaje(int numeroJugador);

	bool esPrimerNivel() {return this->numeroNivel==1;};

private:
	void moverCapasDerecha();
	void moverCapasIzquierda();
	void moverElementosIzquierda();
	void moverElementosDerecha();
	void moverEnemigosIzquierda();
	void moverEnemigosDerecha();

	void moverJugadoresDerechaExcepto(int numeroJugador);
	void moverJugadoresIzquierdaExcepto(int numeroJugador);

	void inicializarCiclos(EntidadUbicada* jugador);

	int generarXaleatorio();
	int generarYaleatorio();
	int generarYaleatorioObjetos();

	int movimientoEnemigos;

	bool alguienLlegoBordeGlobalDerecho();
	bool alguienLlegoBordeGlobalIzquierdo();
	bool alguienLlegoBordeLocalIzquierdo();
	bool alguienLlegoBordeLocalDerecho();


	void ubicarEnemigosYElementos(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos);


	void inicializarCapa(Capa capa);

	FactoryEntidadUbicada factory;

	std::vector<EntidadUbicada*> enemigos;
	std::vector<EntidadUbicada*> elementos;

	vector<EntidadUbicada*> jugadores;
	vector<bool>jugadoresActivos;

	int numeroNivel;

	Capa capa1;
	Capa capa2;
	Capa capa3;
	//Personaje* personaje;
	//Cody cody;

	int pos_borde_izquierda = 0;
	int pos_borde_derecha = WINDOW_SIZE_HORIZONTAL;

	Sonido *musicaFondo;


};
#endif /* NIVEL_H_ */
