/*
 * HitboxUbicada.h
 *
 *  Created on: Nov 20, 2019
 *      Author: franco
 */

#include "PosicionGlobal.h"
#include "dibujable/Hitbox.h"


#ifndef SRC_MODELO_ENTIDADUBICADA_HITBOXUBICADA_H_
#define SRC_MODELO_ENTIDADUBICADA_HITBOXUBICADA_H_

class HitboxUbicada {
public:
	HitboxUbicada(Hitbox hitbox, PosicionGlobal posicion);
	virtual ~HitboxUbicada();

	void desplazarDerecha();
	void desplazarIzquierda();
	void desplazarArriba();
	void desplazarAbajo();
	void desplazarSalto();

	bool colisionaCon(HitboxUbicada& otraHitbox);

	void extenderDepthPorUnFactor(int factor);
	void sumarExtras(int extraWidth, int extraHeight, int extraDepth);


private:
	Hitbox hitbox;
	PosicionGlobal posicion;
};

#endif /* SRC_MODELO_ENTIDADUBICADA_HITBOXUBICADA_H_ */
