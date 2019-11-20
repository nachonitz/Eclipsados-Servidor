/*
 * HitboxUbicada.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: franco
 */

#include "HitboxUbicada.h"

#include "../../Logger.h"

HitboxUbicada::HitboxUbicada(Hitbox hitbox, PosicionGlobal posicion) {
	this->hitbox = hitbox;
	this->posicion = posicion;
}

void HitboxUbicada::desplazarDerecha() {
	posicion.moverDerecha();
}

void HitboxUbicada::desplazarIzquierda() {
	posicion.moverIzquierda();
}

void HitboxUbicada::desplazarArriba() {
	posicion.moverArriba();
}

void HitboxUbicada::desplazarAbajo() {
	posicion.moverAbajo();
}

bool HitboxUbicada::colisionaCon(HitboxUbicada& otraHitbox) {

	// 		 posX + deltaX <= miRangoX <= posX + deltaX + width
	//		 posZ + deltaZ <= miRangoZ <= posZ + deltaZ + height
	// 		 posY - depth / 2 <= miRangoY <= posY + depth / 2


	float miRangoXmin = this->posicion.getHorizontal() + this->hitbox.deltax;

	float miRangoXmax = miRangoXmin + this->hitbox.width;

	float suRangoXmin = otraHitbox.posicion.getHorizontal() + otraHitbox.hitbox.deltax;

	float suRangoXmax = suRangoXmin + otraHitbox.hitbox.width;



	if (miRangoXmax < suRangoXmin || suRangoXmax < miRangoXmin)
		return false;

	//Logger::getInstance()->log(DEBUG, "HITBOXUBICADA.CPP: COLISIONA EN X");
	//Logger::getInstance()->log(DEBUG, "RANGOSX: (" + std::to_string(miRangoXmin) + ", " + std::to_string(miRangoXmax) + ") vs ("+ std::to_string(suRangoXmin) + ", "+ std::to_string(suRangoXmax) + ")");


	float miRangoZmin = this->posicion.getDistanciaDelPiso() + this->hitbox.deltaz;

	float miRangoZmax = miRangoZmin + this->hitbox.height;

	float suRangoZmin = otraHitbox.posicion.getDistanciaDelPiso() + otraHitbox.hitbox.deltaz;

	float suRangoZmax = suRangoZmin + otraHitbox.hitbox.height;


	///Logger::getInstance()->log(DEBUG, "RANGOSZ: (" + std::to_string(miRangoZmin) + ", " + std::to_string(miRangoZmax) + ") vs ("+ std::to_string(suRangoZmin) + ", "+ std::to_string(suRangoZmax) + ")");

	if (miRangoZmax < suRangoZmin || suRangoZmax < miRangoZmin)
		return false;


	//Logger::getInstance()->log(DEBUG, "HITBOXUBICADA.CPP: COLISIONA EN X + Z. DEPTH Y: " + std::to_string(this->hitbox.depth/2));

	float miRangoYmin = this->posicion.getVertical() - this->hitbox.depth/2;

	float miRangoYmax = this->posicion.getVertical() + this->hitbox.depth/2;

	float suRangoYmin = otraHitbox.posicion.getVertical() - otraHitbox.hitbox.depth/2;

	float suRangoYmax = otraHitbox.posicion.getVertical() + otraHitbox.hitbox.depth/2;


	Logger::getInstance()->log(DEBUG, "RANGOSY: (" + std::to_string(miRangoYmin) + ", " + std::to_string(miRangoYmax) + ") vs ("+ std::to_string(suRangoYmin) + ", "+ std::to_string(suRangoYmax) + ")");

	if (miRangoYmax < suRangoYmin || suRangoYmax < miRangoYmin)
		return false;

	//Logger::getInstance()->log(DEBUG, "HITBOXUBICADA.CPP: COLISIONA EN X + Y + Z");




	Logger::getInstance()->log(DEBUG, "COLISION XYZ EN HITBOXUBICADA.CPP!");

	// coincide en todos los rangos!
	return true;
}



HitboxUbicada::~HitboxUbicada() {
	// TODO Auto-generated destructor stub
}

