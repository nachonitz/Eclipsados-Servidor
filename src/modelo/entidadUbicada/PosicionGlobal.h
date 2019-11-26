#ifndef SRC_MODELO_ENTIDADUBICADA_POSICIONGLOBAL_H_
#define SRC_MODELO_ENTIDADUBICADA_POSICIONGLOBAL_H_


#include "../../defs.h"

class PosicionGlobal {
public:
	PosicionGlobal();
	virtual ~PosicionGlobal();


	void moverArriba();
	void moverAbajo();
	void moverIzquierda();
	void moverDerecha();
	void moverArribaEnemigo();
	void moverAbajoEnemigo();
	void moverIzquierdaEnemigo();
	void moverDerechaEnemigo();
	void moverSalto();
	void terminoSalto(){velocidadSalto = VELOCIDAD_SALTO_INICIAL; z = 0;}

	float getHorizontal();
	float getVertical();
	float getDistanciaDelPiso();


	bool estaBordeDerecho(){return x >= (ANCHO_CAPA_PIXELES_ESCALADA)- (MARGEN_DERECHO + 150);}
	bool estaBordeIzquierdo(){return x <= MARGEN_IZQUIERDO;}

	void trasladarA(float horizontal, float vertical);

	PosicionGlobal (const PosicionGlobal &obj);

private:
	float x=0;
	float y=0;
	float z=0;
	float velocidadSalto;
};

#endif /* SRC_MODELO_ENTIDADUBICADA_POSICIONGLOBAL_H_ */
