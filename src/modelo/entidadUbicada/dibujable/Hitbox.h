/*
 * Hitbox.h
 *
 *  Created on: Nov 20, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_HITBOX_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_HITBOX_H_

class Hitbox {
public:
	Hitbox();
	Hitbox(float deltax, float deltaz, float width, float height, float depth);
	virtual ~Hitbox();

	void set(float deltax, float deltaz, float width, float height, float depth);

	Hitbox (const Hitbox &obj);

private:
	float deltax=0, deltaz=0, width=0, height=0, depth=0;

	friend class HitboxUbicada;
};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_HITBOX_H_ */
