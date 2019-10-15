/*
 * ContenedorDeTexturas.cpp
 *
 *  Created on: Sep 30, 2019
 *      Author: franco
 */

#include "ContenedorDeTexturas.h"
#include <map>

std::map<std::string, SDL_Texture*> textureMap;

ContenedorDeTexturas* ContenedorDeTexturas::instance = nullptr;

ContenedorDeTexturas* ContenedorDeTexturas::getInstance() {

    if (instance == nullptr)
        instance = new ContenedorDeTexturas;

    return instance;
}


ContenedorDeTexturas::~ContenedorDeTexturas() {
	// TODO Auto-generated destructor stub
}

SDL_Texture* ContenedorDeTexturas::getTexture(SDL_Renderer* ren, std::string path) {

	auto pair = textureMap.find(path);

	SDL_Texture* tex;

	if (pair == textureMap.end()) {

		SDL_Surface* surf = IMG_Load(path.c_str());

		if (surf == nullptr) {

		    tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 640);

		    Uint32 * pixels = new Uint32[640 * 640];

		    memset(pixels, 255, 640 * 640 * sizeof(Uint32));

		    SDL_UpdateTexture(tex, NULL, pixels, 640 * sizeof(Uint32));

		    Logger::getInstance()->log(ERROR, "No se encuentra el sprite '" + path + "', se mostrara una textura erronea.");
		}
		else
			tex = SDL_CreateTextureFromSurface(ren, surf);

		textureMap.insert({ path, tex });

		return tex;

	}
	else {
		return pair->second;
	}


}

