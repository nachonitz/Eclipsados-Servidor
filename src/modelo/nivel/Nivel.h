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
#include "IA.h"

#include <algorithm>    // std::find


#include "../entidadUbicada/HitboxUbicada.h"


//#include "cody.h"
struct animado{
	bool estaActivo;
	SDL_Rect dest;
	SDL_Rect src;
	SDL_RendererFlip flip;
	int tipoEnemigo;
	int ID;
	int elementoEnMano;
	bool dibujar = true;
};

struct elemento{
	SDL_Rect dest;
	SDL_Rect src;
};

struct capa{
	int nivel;
	SDL_Rect dest;
	SDL_Rect src;
};
struct credencial {
	char usuario[MAX_USER_LEN];
	char contrasenia[MAX_PASS_LEN];
	bool credencialValida;
	int myID;
};
struct informacionEnv{
	struct elemento elementos[MAX_CANT_ELEMENTOS];
	struct capa capas[3];
	struct animado animados[MAX_CANT_ANIMADOS];
	int scores[MAX_CLIENTES];
	int vidas[MAX_CLIENTES];
	int energia[MAX_CLIENTES];
	int cantAnimados;
	int cantElementos;
	int cantJugadores;
	int nivelActual;
	struct credencial credenciales[MAX_CLIENTES];
	bool perdieronTodos;
};
class Nivel {
public:
	Nivel(int NumeroNivel,vector<EntidadUbicada*>& jugadores, int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos, string nombres[MAX_CLIENTES]);
	virtual ~Nivel();

	void setImagesCapas(SDL_Renderer *ren, char const* imagen1, char const* imagen2, char const* imagen3);

	void movimientoArriba(int numeroJugador, Hitbox& hitbox);
	void movimientoAbajo(int numeroJugador, Hitbox& hitbox);
	void movimientoIzquierda(int numeroJugador, Hitbox& hitbox);
	void movimientoDerecha(int numeroJugador, Hitbox& hitbox);
	void movimientoSalto(int numeroJugador, Hitbox& hitbox, int danio);
	void terminoSalto(int numeroJugador, int alturaLocalInicial);
	bool terminoElNivel();

	void finalizarPartida(){this->numeroNivel = 3;}

	void moverCapaDerecha(){moverCapasIzquierda();}

	int get_pos_borde_derecho(){return this->pos_borde_derecha;}
	int get_pos_borde_izquierdo(){return this->pos_borde_izquierda;}

	void actualizarAnimaciones();
	struct informacionEnv getInformacion();

	void moverEnemigos();

	void desconexionDeJugador(int i);
	void conexionDeJugador(int i);

	bool jugadorConectado(int i);

	Capa* getCapa1(){return &capa1;}
	Capa* getCapa2(){return &capa2;}
	Capa* getCapa3(){return &capa3;}

	vector<EntidadUbicada*> getElementos(){return elementos;}
	vector<EntidadUbicada*> getEnemigos(){return enemigos;}

	Personaje* getPersonaje(int numeroJugador);

	bool esPrimerNivel() {return this->numeroNivel==1;};

	bool esSegundoNivel() {return this->numeroNivel==2;};

	vector<bool> getJugadoresActivos();
	void setJugadoresActivos(vector<bool> jugadores);

	float getAlturaGlobalJugador(int numeroJugador) {return jugadores[numeroJugador]->getPosicionGlobal()->getDistanciaDelPiso();};

	float getAlturaLocalJugador(int numeroJugador) {return jugadores[numeroJugador]->getDibujable()->getDest().y;};

	Elemento* agarrarObjeto(int numeroCliente, Hitbox& hitboxJugador);

	bool hacerDanio(int numJugador, Hitbox hitbox, int danio, int score);

	void hacerDanioEnemigo(EntidadUbicada* jugador, Hitbox hitbox, int danio);

	void cargarFinalBoss();

	bool todosMuertos();

	void setNombresUsuario(string nombresApasar[MAX_CLIENTES], int cantClientes);

	string getNombres(int i);

	void jugadorReConectado(int i);

private:
	void moverCapasDerecha();
	void moverCapasIzquierda();
	void moverElementosIzquierda();
	void moverElementosDerecha();
	void moverEnemigosIzquierda();
	void moverEnemigosDerecha();

	void moverJugadoresDerechaExcepto(int numeroJugador);
	void moverJugadoresIzquierdaExcepto(int numeroJugador);

	EntidadUbicada* colisionaConOtroDibujable(HitboxUbicada& hitboxUbicada, Dibujable* dibujablePropietario);

	EntidadUbicada* colisionaConOtroElemento(HitboxUbicada& hitboxUbicada, Dibujable* dibujablePropietario, int extraHeight);


	int generarXaleatorioEnemigo();
	int generarXaleatorio();
	int generarYaleatorioEnemigos();
	int generarYaleatorioCajas();
	int generarYaleatorioBarriles();
	int generarYaleatorioCuchillosYCanios();

	int movimientoEnemigos;
	int puntosExtras;

	bool alguienLlegoBordeGlobalDerecho();
	bool alguienLlegoBordeGlobalIzquierdo();
	bool alguienLlegoBordeLocalIzquierdo();
	bool alguienLlegoBordeLocalDerecho();


	void ubicarEnemigosYElementos(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles);


	void inicializarCapa(Capa capa);

	FactoryEntidadUbicada factory;

	std::vector<EntidadUbicada*> enemigos;
	std::vector<EntidadUbicada*> elementos;
	vector<EntidadUbicada*> jugadores;
	vector<bool>jugadoresActivos;

	IA* ia;
	int numeroNivel;
	int cantEnemigos,cantElementos;

	Capa capa1;
	Capa capa2;
	Capa capa3;
	//Personaje* personaje;
	//Cody cody;

	int pos_borde_izquierda = 0;
	int pos_borde_derecha = WINDOW_SIZE_HORIZONTAL;

	Sonido *musicaFondo;

	bool enemigoGolpeando;
	string nombres[MAX_CLIENTES];


};
#endif /* NIVEL_H_ */
