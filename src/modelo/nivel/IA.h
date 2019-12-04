/*
 * IA.h
 *
 *  Created on: 11 nov. 2019
 *      Author: nacho
 */

#ifndef IA_H_
#define IA_H_

#include <vector>
#include "../entidadUbicada/EntidadUbicada.h"
#include "../entidadUbicada/FactoryEntidadUbicada.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../entidadUbicada/dibujable/estadoPersonaje/EstadoSaltando.h"
#include "../entidadUbicada/dibujable/estadoPersonaje/EstadoSaltandoConPatada.h"
#include "../entidadUbicada/dibujable/estadoPersonaje/EstadoSaltandoVertical.h"

class IA {
public:
	IA(std::vector<EntidadUbicada*> enemigos, std::vector<EntidadUbicada*> jugadores);
	virtual ~IA();
	void moverEnemigos(int pos_borde_derecho, int pos_borde_izquierdo, std::vector<bool>jugadoresActivos, std::vector<EntidadUbicada*> elementos);
	void setEnemigos(std::vector<EntidadUbicada*> enemigos){this->enemigos = enemigos;}

private:
	int encontrarEnemigoMasCercano(EntidadUbicada* enemigo, std::vector<bool> jugadoresActivos);
	void moverEnemigoAJugador(EntidadUbicada* enemigo, EntidadUbicada* jugador, bool* enemigoColisionaObjeto, int * direccion, std::vector<EntidadUbicada*> elementos);
	std::vector<EntidadUbicada*> enemigos;
	std::vector<EntidadUbicada*> jugadores;
	std::vector<int> targets;

	bool enemigoColisionaObjeto[MAX_CANT_ANIMADOS];
	int direccion[MAX_CANT_ANIMADOS];

};

#endif /* IA_H_ */
