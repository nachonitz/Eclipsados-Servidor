#ifndef JUEGO_H_
#define JUEGO_H_

#include "entidadUbicada/EntidadUbicada.h"
#include "entidadUbicada/dibujable/Personaje.h"
#include "nivel/Nivel.h"

struct informacionRec{
	int animacionActual;
	int movimiento;
	SDL_RendererFlip flip;
	int numeroDeCliente;
	int tickActual;
};


class Juego {
public:
	Juego(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos, int cantJugadores);
	virtual ~Juego();

	void movimientoDerecha(int numeroJugador);
	void movimientoIzquierda(int numeroJugador);
	void movimientoArriba(int numeroJugador);
	void movimientoAbajo(int numeroJugador);
	void movimientoSalto(int numeroJugador);
	void terminadoSalto(int numeroJugador);
	bool terminoElNivel();
	void cambiarDeNivel();
	void moverEnemigos();
	void actualizarAnimaciones(){this->nivel->actualizarAnimaciones();}
	void procesarInfo(struct informacionRec infoRec);

	struct informacionEnv getInformacion(){return this->nivel->getInformacion();}
	Personaje* getJugador(int numeroJugador);

	PosicionGlobal* getPosicionJugador(int numeroJugador);


	Capa* getCapa1(){return nivel->getCapa1();}
	Capa* getCapa2(){return nivel->getCapa2();}
	Capa* getCapa3(){return nivel->getCapa3();}

	vector<EntidadUbicada*> getElementos(){return nivel->getElementos();}
	vector<EntidadUbicada*> getEnemigos(){return nivel->getEnemigos();}

private:
	//EntidadUbicada* entidad;
	Nivel* nivel;
	vector<EntidadUbicada*> jugadores;
	//Dibujable* personaje;
	//Personaje* cody;
	int cajas,barriles,canios,cuchillos,enemigos;

	int animacionActual[cantClientes];
	bool agachado[cantClientes],golpear[cantClientes],saltando[cantClientes];
	double alturaActualSalto, alturaMaximaSalto;

};

#endif /* JUEGO_H_ */
