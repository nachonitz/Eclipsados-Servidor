#ifndef SRC_MODELO_ENTIDADUBICADA_ENTIDADUBICADA_H_
#define SRC_MODELO_ENTIDADUBICADA_ENTIDADUBICADA_H_

#include "dibujable/Dibujable.h"
#include "HitboxUbicada.h"
#include "../../defs.h"


class EntidadUbicada {
public:
	EntidadUbicada(Dibujable* entidad);
	EntidadUbicada(Dibujable* entidad, float horizontal, float vertical);

	virtual ~EntidadUbicada();


	void moverGlobalIzquierda(){posicion->moverIzquierda();}
	void moverGlobalDerecha(){posicion->moverDerecha();}
	void moverGlobalArriba(){posicion->moverArriba();}
	void moverGlobalAbajo(){posicion->moverAbajo();}
	void moverGlobalSalto(){posicion->moverSalto();}
	void terminoGlobalSalto(){posicion->terminoSalto();}

	void moverLocalIzquierda(){dibujable->moverIzquierda();}
	void moverLocalDerecha(){dibujable->moverDerecha();}
	void moverLocalArriba(){dibujable->moverArriba();}
	void moverLocalAbajo(){dibujable->moverAbajo();}
	void moverLocalSalto(){dibujable->moverSalto();}
	void terminoLocalSalto(int alturaLocalInicial){dibujable->terminoSalto(alturaLocalInicial);}

	PosicionGlobal* getPosicionGlobal();

	bool llegoBordeLocalDerecho(){return dibujable->estaBordeDerecho();}
	bool llegoBordeLocalIzquierdo(){return dibujable->estaBordeIzquierdo();}

	bool llegoBordeGlobalIzquierdo(){return posicion->estaBordeIzquierdo();}
	bool llegoBordeGlobalDerecho(){return posicion->estaBordeDerecho();}

	Dibujable* getDibujable(){return dibujable;}


	int getHorizontalGlobal(){return posicion->getHorizontal();}

	void seCambioElNivel(Dibujable* entidad);

	bool colisionaCon(HitboxUbicada& hitboxAjena);

private:

	Dibujable* dibujable;
	PosicionGlobal* posicion;
};

#endif /* SRC_MODELO_ENTIDADUBICADA_ENTIDADUBICADA_H_ */
