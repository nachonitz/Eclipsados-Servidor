#include "EntidadUbicada.h"


EntidadUbicada::EntidadUbicada(Dibujable* entidad) {
	this->entidad = entidad;
	this->posicion = new PosicionGlobal();

}


EntidadUbicada::EntidadUbicada(Dibujable* entidad, float horizontal, float vertical) {

	this->entidad = entidad;
	this->posicion = new PosicionGlobal();

	posicion->trasladarA(horizontal, vertical);
}

EntidadUbicada::~EntidadUbicada() {
	delete posicion;
}



PosicionGlobal* EntidadUbicada::getPosicionGlobal() {
	return posicion;
}

void EntidadUbicada::seCambioElNivel(Dibujable* entidad){
	this->posicion->trasladarA(JUGADOR_POSICION_HORIZONTAL_INICIAL,JUGADOR_POSICION_VERTICAL_INICIAL);
	this->entidad = entidad;
}
