/*
 * AsignadorDeTexturas.h
 *
 *  Created on: Sep 19, 2019
 *      Author: franco
 */

#ifndef SRC_ASIGNADORDETEXTURAS_H_
#define SRC_ASIGNADORDETEXTURAS_H_

#include <vector>
#include <string>

#include "SDL2/SDL.h"
#include <stdlib.h>

class Elemento;
class Personaje;
class Enemigo;
class FinalBoss;

/*

*/

class AsignadorDeTexturas {
public:
	AsignadorDeTexturas();
	virtual ~AsignadorDeTexturas();

	std::vector<std::string> * getNivel1() {
		return &nivel1;
	}
	std::vector<std::string> * getNivel2() {
		return &nivel2;
	}
	std::vector<std::string> * getSprites() {
		return &sprites;
	}

	void setTexture(Elemento& elemento, SDL_Renderer* ren);
	void setTexture(Personaje& personaje, SDL_Renderer* ren);
	void setTexture(Enemigo& enemigo, SDL_Renderer* ren);
	//void setTexture(FinalBoss& boss, SDL_Renderer* ren);


private:
	std::vector<std::string> nivel1, nivel2, sprites;
};

#endif /* SRC_ASIGNADORDETEXTURAS_H_ */
