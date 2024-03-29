/*
 * Objeto.h
 *
 *  Created on: Sep 5, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_OBJETO_H_
#define SRC_MODELO_OBJETO_H_

#include "../Dibujable.h"
#include "../estadoPersonaje/EstadoElemento.h"
#include "../estadoPersonaje/EstadoRecibiendoDanioElemento.h"

class Elemento : public Dibujable{
protected:
	Hitbox hitboxElemento;
	EstadoPersonaje* estadoActual;
	int vidas, score;

public:
	Elemento();
	virtual ~Elemento();

	Hitbox getHitbox() {return hitboxElemento;}

	virtual int getScore() = 0;

	virtual int getDanioElemento() = 0;

	void registrarUnUso(){this->vidas --;}

	void setImageWith(AsignadorDeTexturas& asignador, SDL_Renderer* ren);

	virtual int recibirDanio(int danio) = 0;

	int getVidas(){return vidas;}

	virtual EstadoPersonaje* getEstadoActual()=0;

	void updateAnim();

};

#endif /* SRC_MODELO_OBJETO_H_ */
