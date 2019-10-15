
#ifndef ADMINISTRADORDENIVELES_H_
#define ADMINISTRADORDENIVELES_H_

#include <stdio.h>

#include "Nivel.h"

class AdministradorDeNiveles {
public:
	AdministradorDeNiveles();
	virtual ~AdministradorDeNiveles();
	void cambiarNivel();

private:
	//Nivel nivelActual;
};

#endif /* ADMINISTRADORDENIVELES_H_ */
