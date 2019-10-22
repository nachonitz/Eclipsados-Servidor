#ifndef JUEGO_H_
#define JUEGO_H_

#include "entidadUbicada/EntidadUbicada.h"
#include "entidadUbicada/dibujable/Personaje.h"
#include "nivel/Nivel.h"

struct informacionRec{
	int animacionActual;
	int movimiento;
	SDL_RendererFlip flip;
};


class Juego {
public:
	Juego(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos);
	virtual ~Juego();

	void movimientoDerecha();
	void movimientoIzquierda();
	void movimientoArriba();
	void movimientoAbajo();
	void movimientoSalto();
	void terminadoSalto();
	bool terminoElNivel();
	void cambiarDeNivel();
	void moverEnemigos();
	void actualizarAnimaciones(){this->nivel->actualizarAnimaciones();}

	struct informacion getInformacion(){return this->nivel->getInformacion();}
	Personaje* getJugador();

	PosicionGlobal* getPosicionJugador();


	Capa* getCapa1(){return nivel->getCapa1();}
	Capa* getCapa2(){return nivel->getCapa2();}
	Capa* getCapa3(){return nivel->getCapa3();}

	vector<EntidadUbicada*> getElementos(){return nivel->getElementos();}
	vector<EntidadUbicada*> getEnemigos(){return nivel->getEnemigos();}

private:
	EntidadUbicada* entidad;
	Nivel* nivel;
	Dibujable* personaje;
	int cajas,barriles,canios,cuchillos,enemigos;



};

#endif /* JUEGO_H_ */
