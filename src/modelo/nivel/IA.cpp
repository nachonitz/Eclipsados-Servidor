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

void procesarAccionIA(Enemigo* enemigo){
	struct informacionRec info;
	enemigo->procesarAccion(info);
}

int IA::encontrarEnemigoMasCercano(EntidadUbicada* enemigo,std::vector<bool> jugadoresActivos){
	float distancia_x;
	float distancia_y;
	HitboxUbicada hitboxUbicadaEnemigo(enemigo->getDibujable()->getHitbox(), *enemigo->getPosicionGlobal());
	float distancia;
	int idx_jugador = -1;

	for (int i = 0; i < jugadores.size(); i++){
		Personaje* pj = (Personaje*) jugadores[i]->getDibujable();
		if (!jugadoresActivos[i] || pj->getEstadoMuerto()){
			continue;
		}
		EstadoPersonaje* estado = pj->getEstadoActual();
		if (typeid(*estado) == typeid(EstadoMorirPersonaje)){
			continue;
		}
		HitboxUbicada hitboxUbicadaPersonaje(jugadores[i]->getDibujable()->getHitbox(), *jugadores[i]->getPosicionGlobal());
		float distancia_x = abs(hitboxUbicadaPersonaje.distanciaEnX(hitboxUbicadaEnemigo));
		float distancia_y = abs(hitboxUbicadaPersonaje.distanciaEnY(hitboxUbicadaEnemigo));
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
	HitboxUbicada hitboxUbicadaPersonaje(jugador->getDibujable()->getHitbox(), *jugador->getPosicionGlobal());

	float distancia_x = hitboxUbicadaPersonaje.distanciaEnX(hitboxUbicadaEnemigo);
	float distancia_y = hitboxUbicadaPersonaje.distanciaEnY(hitboxUbicadaEnemigo);

	Enemigo* enemigoDibujable = (Enemigo*) enemigo->getDibujable();
	Personaje* personajeDibujable = (Personaje*) jugador->getDibujable();

	EstadoPersonaje* estadoPersonaje = personajeDibujable->getEstadoActual();
	EstadoPersonaje* estado = enemigoDibujable->getEstadoActual();

	if(estado == NULL)
		return;
	if(typeid(*estado) == typeid(EstadoGolpeandoEnemigo) || typeid(*estado) == typeid(EstadoRecibiendoDanioEnemigo) || typeid(*estado) == typeid(EstadoMorirEnemigo)){
		return;
	}

	if (distancia_y != 0){ //Siempre primero hacemos que el enemigo se ajuste al eje y
		if (distancia_y > 0){
			hitboxUbicadaEnemigo.desplazarArriba();
			if(jugador->colisionaCon(hitboxUbicadaEnemigo)){
				enemigo->moverGlobalDerechaEnemigo();
				enemigoDibujable->moverDerechaEnemigo();
				enemigoDibujable->setFlip(SDL_FLIP_NONE);
				return;
			}
			enemigo->moverGlobalArribaEnemigo();
			enemigoDibujable->moverArribaEnemigo();
		}else{
			hitboxUbicadaEnemigo.desplazarAbajo();

			if(jugador->colisionaCon(hitboxUbicadaEnemigo)){
				enemigo->moverGlobalDerechaEnemigo();
				enemigoDibujable->moverDerechaEnemigo();
				enemigoDibujable->setFlip(SDL_FLIP_NONE);
				return;
			}
			enemigo->moverGlobalAbajoEnemigo();
			enemigoDibujable->moverAbajoEnemigo();
		}
	}else{
		if (distancia_x < 0){
			hitboxUbicadaEnemigo.desplazarDerecha();
			enemigoDibujable->setFlip(SDL_FLIP_NONE);
			if(jugador->colisionaCon(hitboxUbicadaEnemigo)){
				if((rand()%70 == 0) && (typeid(*estadoPersonaje) != typeid(EstadoSaltando)) && (typeid(*estadoPersonaje) != typeid(EstadoSaltandoConPatada)) && (typeid(*estadoPersonaje) != typeid(EstadoSaltandoVertical))){
					struct informacionRec info;
					enemigoDibujable->golpear(jugador);
					enemigoDibujable->procesarAccion(info);
					//procesarAccionIA(enemigoDibujable);
					return;
				}
				return;
			}
			enemigo->moverGlobalDerechaEnemigo();
			enemigoDibujable->moverDerechaEnemigo();
		}else{
			hitboxUbicadaEnemigo.desplazarIzquierda();
			enemigoDibujable->setFlip(SDL_FLIP_HORIZONTAL);
			if(jugador->colisionaCon(hitboxUbicadaEnemigo)){
				if((rand()%70 == 0) && (typeid(*estadoPersonaje) != typeid(EstadoSaltando)) && (typeid(*estadoPersonaje) != typeid(EstadoSaltandoConPatada)) && (typeid(*estadoPersonaje) != typeid(EstadoSaltandoVertical))){
					struct informacionRec info;
					enemigoDibujable->golpear(jugador);
					enemigoDibujable->procesarAccion(info);
					//procesarAccionIA(enemigoDibujable);
					return;
				}
				return;
			}
			enemigo->moverGlobalIzquierdaEnemigo();
			enemigoDibujable->moverIzquierdaEnemigo();
		}
	}

}

void IA::moverEnemigos(int pos_borde_derecho, int pos_borde_izquierdo, std::vector<bool> jugadoresActivos){

	for (int i = 0; i < enemigos.size(); i++){
		int pos_horizontal_enemigo = enemigos[i]->getPosicionGlobal()->getHorizontal();
		struct informacionRec info;
		Enemigo * enemigo = (Enemigo*)enemigos[i]->getDibujable();
		if (pos_horizontal_enemigo < pos_borde_derecho+50 /*&& pos_horizontal_enemigo > pos_borde_izquierdo - 100*/){
			int idx_jugador = encontrarEnemigoMasCercano(enemigos[i],jugadoresActivos);
			if (idx_jugador == -1){
				//enemigo->moverArriba();
				//enemigos[i]->moverGlobalArriba();
				enemigo->procesarAccion(info);
				continue;
			}
			targets[i] = idx_jugador;
			moverEnemigoAJugador(enemigos[i],jugadores[targets[i]]);
			enemigo->procesarAccion(info);
			//procesarAccionIA((Enemigo*)enemigos[i]->getDibujable());
		}else{
			enemigo->procesarAccion(info);
		}
	}
}
