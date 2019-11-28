/*
 * AsignadorDeTexturas.cpp
 *
 *  Created on: Sep 19, 2019
 *      Author: franco
 */

#include "AsignadorDeTexturas.h"

#include "modelo/entidadUbicada/dibujable/elemento/Elemento.h"

#include "modelo/entidadUbicada/dibujable/Personaje.h"

#include "modelo/entidadUbicada/dibujable/Enemigo.h"

AsignadorDeTexturas::AsignadorDeTexturas() {
	// TODO Auto-generated constructor stub

}

AsignadorDeTexturas::~AsignadorDeTexturas() {
	// TODO Auto-generated destructor stub
}


void AsignadorDeTexturas::setTexture(Elemento& elemento, SDL_Renderer* ren) {
	const char* img = sprites.at(1).c_str();

	elemento.setImage(ren, img);
}

void AsignadorDeTexturas::setTexture(Personaje& personaje, SDL_Renderer* ren) {

	const char* img = sprites.at(0).c_str();

	personaje.setImage(ren, img);
}

void AsignadorDeTexturas::setTexture(Enemigo& enemigo, SDL_Renderer* ren) {

	int num = 2+(rand()% 3);
	const char* img = sprites.at(num).c_str();
	//const char* img = sprites.at(2).c_str();

	enemigo.setImage(ren, img);
}

/*void AsignadorDeTexturas::setTexture(FinalBoss& boss, SDL_Renderer* ren) {

	int num = 2+(rand()% 3);
	const char* img = sprites.at(num).c_str();
	//const char* img = sprites.at(2).c_str();

	boss.setImage(ren, img);
}*/
