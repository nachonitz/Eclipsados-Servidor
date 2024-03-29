/*
 * EstadoSaltandoConPatada.h
 *
 *  Created on: Nov 16, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOCONPATADA_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOCONPATADA_H_

#include "EstadoPersonaje.h"

class EstadoSaltandoConPatada : public EstadoPersonaje {
private:
	float alturaActualSalto;
	int alturaDestInicial;

	void resolverMovimientoHorizontal(int numeroCliente);

	Hitbox hitbox[6];

	int hbxActual = 0;

	int tickAnterior;


public:
	EstadoSaltandoConPatada(SDL_RendererFlip flip, float alturaActual) : EstadoSaltandoConPatada(flip, alturaActual, nullptr) {};
	EstadoSaltandoConPatada(SDL_RendererFlip flip, float alturaActual, Elemento* elementoEnMano);


	virtual ~EstadoSaltandoConPatada();

	EstadoPersonaje* procesarAccion(informacionRec info);

	virtual Hitbox getHitboxActual() {return hitbox[hbxActual];}

	bool puedeRecibirDanio() override {return false;};	// invencible cuando salta!

};

#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_ESTADOPERSONAJE_ESTADOSALTANDOCONPATADA_H_ */
