#include "PosicionGlobal.h"


PosicionGlobal::PosicionGlobal() {
	// Inicializacion harcodeada para tamaño de cody
	x = JUGADOR_POSICION_HORIZONTAL_INICIAL;
	y = JUGADOR_POSICION_VERTICAL_INICIAL;
	velocidadSalto = VELOCIDAD_SALTO_INICIAL;
	z = 0;
}

/*
PosicionGlobal::PosicionGlobal(const PosicionGlobal &pos) {

	x = pos.x;
	y = pos.y;
	velocidad = pos.velocidad;

}
*/

PosicionGlobal::~PosicionGlobal() {
	// TODO Auto-generated destructor stub
}

// Todos los valores fueron calculados para el tamaño que ocupa Cody

void PosicionGlobal::moverArriba(){
	if(y > WINDOW_SIZE_VERTICAL - MARGEN_PISO_ARRIBA){
		y -= VELOCIDAD_CODY/2;
	}
}

void PosicionGlobal::moverSalto(){
	z = z - velocidadSalto * DELTA_T;
	velocidadSalto = velocidadSalto + DELTA_T * GRAVEDAD;

}

void PosicionGlobal::moverAbajo(){
	if(y < WINDOW_SIZE_VERTICAL - MARGEN_PISO_ABAJO){
		y += VELOCIDAD_CODY/2;
	}
}

void PosicionGlobal::moverIzquierda(){
	//x -= VELOCIDAD_CODY/2;
	x -= VELOCIDAD_CODY;
}

void PosicionGlobal::moverDerecha(){
	//x += VELOCIDAD_CODY/2;
	x += VELOCIDAD_CODY;
}

float PosicionGlobal::getVertical() {
	return y;
}

float PosicionGlobal::getHorizontal() {
	return x;
}

float PosicionGlobal::getDistanciaDelPiso() {
	return z;
}


void PosicionGlobal::trasladarA(float horizontal, float vertical) {
	x = horizontal;
	y = vertical;
	z=0;
}
