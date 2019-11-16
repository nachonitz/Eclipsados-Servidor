#ifndef JUEGO_H_
#define JUEGO_H_

#include "entidadUbicada/EntidadUbicada.h"
#include "entidadUbicada/dibujable/Personaje.h"
#include "nivel/Nivel.h"



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

	void moverEnemigos();
	void actualizarAnimaciones(){this->nivel->actualizarAnimaciones();}
	void procesarInfo(struct informacionRec infoRec);

	void chequearCambioDeNivel();

	struct informacionEnv getInformacion(){return this->nivel->getInformacion();}
	Personaje* getJugador(int numeroJugador);

	PosicionGlobal* getPosicionJugador(int numeroJugador);

	void desconexionDeJugador(int i);
	void conexionDeJugador(int i);

	bool jugadorConectado(int i);

	Capa* getCapa1(){return nivel->getCapa1();}
	Capa* getCapa2(){return nivel->getCapa2();}
	Capa* getCapa3(){return nivel->getCapa3();}

	vector<EntidadUbicada*> getElementos(){return nivel->getElementos();}
	vector<EntidadUbicada*> getEnemigos(){return nivel->getEnemigos();}

private:

	Nivel* nivel;
	vector<EntidadUbicada*> jugadores;

	int cajas,barriles,canios,cuchillos,enemigos;

/*	int animacionActual[MAX_CLIENTES], direccionSalto[MAX_CLIENTES];
	bool agachado[MAX_CLIENTES],golpear[MAX_CLIENTES],saltando[MAX_CLIENTES];
	double alturaActualSalto[MAX_CLIENTES], alturaMaximaSalto[MAX_CLIENTES];*/

	bool terminoElNivel();
	void cambiarDeNivel();
	bool cambiandoNivel[MAX_CLIENTES];


};

#endif /* JUEGO_H_ */
