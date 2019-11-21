/*
 * IA.cpp
 *
 *  Created on: 11 nov. 2019
 *      Author: nacho
 */

#include "IA.h"

IA::IA(std::vector<EntidadUbicada*> enemigos, std::vector<EntidadUbicada*> jugadores) {
	this->enemigos = enemigos;
	this->jugadores = jugadores;

	for (int i = 0; i < enemigos.size(); i++){
		targets.push_back(0);
	}
}

IA::~IA() {
	// TODO Auto-generated destructor stub
}

int IA::encontrarEnemigoMasCercano(EntidadUbicada* enemigo){
	int idx_jugador;
	float distancia;
	int x_enemigo = enemigo->getPosicionGlobal()->getHorizontal();
	int y_enemigo = enemigo->getPosicionGlobal()->getVertical()-50;

	for (int i = 0; i < jugadores.size(); i++){
		int x_jugador = jugadores[i]->getPosicionGlobal()->getHorizontal();
		int y_jugador = jugadores[i]->getPosicionGlobal()->getVertical();
		int distancia_x = abs(x_enemigo-x_jugador);
		int distancia_y = abs(y_enemigo-y_jugador);
		float distancia_actual = sqrt((distancia_x * distancia_x) + (distancia_y * distancia_y));

		if (i == 0){
			distancia = distancia_actual;
			idx_jugador = i;
		}
		else{
			if (distancia_actual < distancia){
				distancia = distancia_actual;
				idx_jugador = i;
			}
		}
	}

	return idx_jugador;
}

void IA::moverEnemigoAJugador(EntidadUbicada* enemigo, EntidadUbicada* jugador){

	//TODO: COLISIONES ENEMIGOS
	HitboxUbicada hitboxUbicadaEnemigo(enemigo->getDibujable()->getHitbox(), *enemigo->getPosicionGlobal());


	int x_enemigo = enemigo->getPosicionGlobal()->getHorizontal();
	int y_enemigo = enemigo->getPosicionGlobal()->getVertical()-50;
	int x_jugador = jugador->getPosicionGlobal()->getHorizontal();
	int y_jugador = jugador->getPosicionGlobal()->getVertical();
	int distancia_x = abs(x_enemigo-x_jugador);
	int distancia_y = abs(y_enemigo-y_jugador);

	Enemigo* enemigoDibujable = (Enemigo*) enemigo->getDibujable();


	if (distancia_x > distancia_y){
		if (x_jugador > x_enemigo){
			hitboxUbicadaEnemigo.desplazarDerecha();
			if(jugador->colisionaCon(hitboxUbicadaEnemigo)){
				return;
			}
			enemigo->moverGlobalDerecha();
			enemigo->moverLocalDerecha();
			enemigoDibujable->setFlip(SDL_FLIP_NONE);
		}else{
			hitboxUbicadaEnemigo.desplazarIzquierda();
			if(jugador->colisionaCon(hitboxUbicadaEnemigo)){
				return;
			}
			enemigo->moverGlobalIzquierda();
			enemigo->moverLocalIzquierda();
			enemigoDibujable->setFlip(SDL_FLIP_HORIZONTAL);
		}
	}
	else{
		if (y_jugador < y_enemigo){
			hitboxUbicadaEnemigo.desplazarArriba();
			if(jugador->colisionaCon(hitboxUbicadaEnemigo)){
				return;
			}
			enemigo->moverGlobalArriba();
			enemigo->moverLocalArriba();
		}else{
			hitboxUbicadaEnemigo.desplazarAbajo();

			if(jugador->colisionaCon(hitboxUbicadaEnemigo)){
				return;
			}
			enemigo->moverGlobalAbajo();
			enemigo->moverLocalAbajo();
		}
	}
}

void IA::moverEnemigos(int pos_borde_derecho, int pos_borde_izquierdo){

	for (int i = 0; i < enemigos.size(); i++){
		int pos_horizontal_enemigo = enemigos[i]->getPosicionGlobal()->getHorizontal();
		if (pos_horizontal_enemigo < pos_borde_derecho+50 && pos_horizontal_enemigo > pos_borde_izquierdo){
			targets[i] = encontrarEnemigoMasCercano(enemigos[i]);
			moverEnemigoAJugador(enemigos[i],jugadores[targets[i]]);
			struct informacionRec info;
			Enemigo* enemigoDibujable = (Enemigo*) enemigos[i]->getDibujable();
			enemigoDibujable->procesarAccion(info);
		}
	}
}
