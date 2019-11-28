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

class IA {
public:
	IA(std::vector<EntidadUbicada*> enemigos, std::vector<EntidadUbicada*> jugadores);
	virtual ~IA();
	void moverEnemigos(int pos_borde_derecho, int pos_borde_izquierdo, std::vector<bool>jugadoresActivos);

private:
	int encontrarEnemigoMasCercano(EntidadUbicada* enemigo, std::vector<bool> jugadoresActivos);
	void moverEnemigoAJugador(EntidadUbicada* enemigo, EntidadUbicada* jugador);
	std::vector<EntidadUbicada*> enemigos;
	std::vector<EntidadUbicada*> jugadores;

	std::vector<int> targets;

};

#endif /* IA_H_ */
