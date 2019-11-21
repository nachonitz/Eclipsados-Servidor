/*
 * FactoryEntidadUbicada.h
 *
 *  Created on: Sep 9, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_FACTORYENTIDADUBICADA_H_
#define SRC_MODELO_ENTIDADUBICADA_FACTORYENTIDADUBICADA_H_

#include "EntidadUbicada.h"
#include "dibujable/Personaje.h"
#include "dibujable/Enemigo.h"
#include "dibujable/elemento/Barril.h"
#include "dibujable/elemento/Caja.h"
#include "dibujable/elemento/CanioMetalico.h"
#include "dibujable/elemento/Cuchillo.h"

class FactoryEntidadUbicada {
public:
	FactoryEntidadUbicada();
	virtual ~FactoryEntidadUbicada();

	EntidadUbicada* crearEntidadConPersonaje();

	EntidadUbicada* crearEntidadConEnemigo(float horizontal, float vertical, int tipoEnemigo);

	EntidadUbicada* crearEntidadConBarril();

	EntidadUbicada* crearEntidadConBarril(float horizontal, float vertical);

	EntidadUbicada* crearEntidadConCuchillo(float horizontal, float vertical);

	EntidadUbicada* crearEntidadConCanio(float horizontal, float vertical);

	EntidadUbicada* crearEntidadConCaja(float horizontal, float vertical);

};

#endif /* SRC_MODELO_ENTIDADUBICADA_FACTORYENTIDADUBICADA_H_ */
