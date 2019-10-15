/*
 * ContenedorDeTexturas.h
 *
 *  Created on: Sep 30, 2019
 *      Author: franco
 */

#ifndef SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_CONTENEDORDETEXTURAS_H_
#define SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_CONTENEDORDETEXTURAS_H_

#include "SDL2/SDL_image.h"
#include <string>
#include "../../../Logger.h"

class ContenedorDeTexturas {
public:

	static ContenedorDeTexturas* getInstance();

	SDL_Texture* getTexture(SDL_Renderer* ren,std::string path);

	virtual ~ContenedorDeTexturas();

private:
	ContenedorDeTexturas() {};
	static ContenedorDeTexturas* instance;
	ContenedorDeTexturas(ContenedorDeTexturas const&);
	ContenedorDeTexturas& operator=(ContenedorDeTexturas const&);

};


#endif /* SRC_MODELO_ENTIDADUBICADA_DIBUJABLE_CONTENEDORDETEXTURAS_H_ */
