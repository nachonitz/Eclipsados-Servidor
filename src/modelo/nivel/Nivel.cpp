

#include "Nivel.h"

Nivel::Nivel(int numeroNivel, EntidadUbicada* jugador, int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos) {

	musicaFondo = new Sonido(numeroNivel);
	(*musicaFondo).play();

	cody = jugador;
	personaje = (Personaje*)cody->getDibujable();

	int parado = personaje->crearCiclo(1, 120, 120, 1, 10);
	int caminar = personaje->crearCiclo(2, 120, 120, 12, 4);
	int salto = personaje->crearCiclo(3, 120, 120, 8, 6);
	int golpear = personaje->crearCiclo(4, 120, 120, 9, 5);
	int saltoPatada = personaje->crearCiclo(5, 120, 120, 6, 9);
	int agachado = personaje->crearCiclo(1, 120, 120, 4, 5);
	int saltoVertical = personaje->crearCiclo(6, 120, 120, 6, 8);

	int accionActual = parado;
	personaje->setAnimacionActual(accionActual, SDL_FLIP_NONE);
	cody->getDibujable()->setDest(JUGADOR_POSICION_HORIZONTAL_INICIAL, JUGADOR_POSICION_VERTICAL_INICIAL, JUGADOR_SIZE_HORIZONTAL, JUGADOR_SIZE_VERTICAL);
	personaje->updateAnim();

	capa1.setSource(0,0,ANCHO_CAPA_PIXELES ,WINDOW_SIZE_VERTICAL+10);
	capa1.setDest(0,0,ANCHO_CAPA_PIXELES_ESCALADA,WINDOW_SIZE_VERTICAL+10);
	capa2.setSource(0,0,ANCHO_CAPA_PIXELES ,WINDOW_SIZE_VERTICAL+10);
	capa2.setDest(0,0,ANCHO_CAPA_PIXELES_ESCALADA,WINDOW_SIZE_VERTICAL+10);
	capa3.setSource(0,0,ANCHO_CAPA_PIXELES ,WINDOW_SIZE_VERTICAL+10);
	capa3.setDest(0,0,ANCHO_CAPA_PIXELES_ESCALADA,WINDOW_SIZE_VERTICAL+10);

	capa1.setVelocidad(VELOCIDAD_CODY);
	capa2.setVelocidad(2);
	capa3.setVelocidad(1);

	this->movimientoEnemigos = 0;

	this->ubicarEnemigosYElementos(cantCuchillos, cantCajas, cantCanios, cantBarriles, cantEnemigos);

	for(uint i = 0; i<enemigos.size(); i++){
		Enemigo* enemigoActual = (Enemigo*) enemigos[i]->getDibujable();
		enemigoActual->setSource(0,0,100,125);
		//enemigoActual->setDest(enemigoActual->getPosHorizontal(), enemigoActual->getPosVertical(), enemigoActual->getWidth()*2.2,enemigoActual->getHeight()*2.2);
		int parado = enemigoActual->crearCiclo(1, 100, 125, 1, 1);
		int caminar = enemigoActual->crearCiclo(2, 100, 125, 6, 4);
		enemigoActual->setAnimacionActual(caminar, SDL_FLIP_NONE);
	}

}

Nivel::~Nivel() {
	//delete cody;
	delete musicaFondo;

	for (uint i = 0; i < elementos.size(); i++) {
		delete elementos[i];
	}
}

void Nivel::actualizarAnimaciones(){
	personaje->updateAnim();
	for (uint i = 0; i<enemigos.size();i++){
		Enemigo* enemigoActual = (Enemigo*) enemigos[i]->getDibujable();
		enemigoActual->updateAnim();
	}
}

struct informacion Nivel::getInformacion(){
	struct informacion info;

	struct animado animadoActual;
	animadoActual.dest = personaje->getDest();
	animadoActual.src = personaje->getSource();
	//animadoActual.txt = personaje->getTexture();
	animadoActual.src = personaje->getSource();
	animadoActual.flip = personaje->getFlip();
	//animados.push_back(animadoActual);
	info.animados[0] = animadoActual;

	for (uint i = 0; i<enemigos.size(); i++){
		struct animado animadoActual;
		Enemigo* enemigoActual = (Enemigo*) enemigos[i]->getDibujable();
		animadoActual.dest = enemigoActual->getDest();
		animadoActual.src = enemigoActual->getSource();
		//animadoActual.txt = enemigoActual->getTexture();
		animadoActual.flip = enemigoActual->getFlip();
		//animados.push_back(animadoActual);
		info.animados[i+1] = animadoActual;
	}

	for (uint i = 0;i<elementos.size();i++){
		struct elemento elementoActual;
		Dibujable* dibujable = elementos[i]->getDibujable();
		elementoActual.dest = dibujable->getDest();
		elementoActual.src = dibujable->getSource();
		//elementoActual.txt = dibujable->getTexture();
		//objetos.push_back(elementoActual);
		info.elementos[i] = elementoActual;
	}

	struct capa capa1;
	capa1.dest = this->capa1.getDest();
	capa1.src = this->capa1.getSource();
	//capa1.txt= this->capa1.getTexture();

	info.capas[0] = capa1;

	struct capa capa2;
	capa2.dest = this->capa2.getDest();
	capa2.src = this->capa2.getSource();
	//capa2.txt = this->capa2.getTexture();

	info.capas[1] = capa2;

	struct capa capa3;
	capa3.dest = this->capa3.getDest();
	capa3.src = this->capa3.getSource();
	//capa3.txt = this->capa3.getTexture();

	info.capas[2] = capa3;


	info.cantAnimados = enemigos.size() + 1;
	info.cantElementos = elementos.size();


	return info;
}

void Nivel::moverElementosDerecha(){

	for (uint i = 0; i < elementos.size(); i++){
		elementos[i]->moverLocalDerecha();
	}
}
void Nivel::moverElementosIzquierda(){

	for (uint i = 0; i < elementos.size(); i++){
		elementos[i]->moverLocalIzquierda();
	}
}

void Nivel::moverEnemigosIzquierda(){
	for (uint i = 0; i < enemigos.size(); i++){
		enemigos[i]->moverLocalIzquierda();
	}
}
void Nivel::moverEnemigosDerecha(){

	for (uint i = 0; i < enemigos.size(); i++){
		enemigos[i]->moverLocalDerecha();
	}
}

void Nivel::movimientoArriba(){
	cody->moverLocalArriba();
	cody->moverGlobalArriba();
}

void Nivel::movimientoSalto(){
	cody->moverLocalSalto();
	cody->moverGlobalSalto();
}

void Nivel::terminoSalto(){
	cody->terminoLocalSalto();
	cody->terminoGlobalSalto();
}

void Nivel::movimientoAbajo(){
	cody->moverLocalAbajo();
	cody->moverGlobalAbajo();
}

void Nivel::movimientoIzquierda(){
	if (!cody->llegoBordeGlobalIzquierdo()){
		if (cody->llegoBordeLocalIzquierdo()){
			pos_borde_izquierda -= VELOCIDAD_CODY;
			pos_borde_derecha -= VELOCIDAD_CODY;
			moverCapasDerecha();
			moverElementosDerecha();
			moverEnemigosDerecha();
		}else{
			cody->moverLocalIzquierda();
		}
		cody->moverGlobalIzquierda();
	}

}

void Nivel::movimientoDerecha(){
	if (!cody->llegoBordeGlobalDerecho()){
		if (cody->llegoBordeLocalDerecho()){
			pos_borde_derecha += VELOCIDAD_CODY;
			pos_borde_izquierda += VELOCIDAD_CODY;
			moverCapasIzquierda();
			moverElementosIzquierda();
			moverEnemigosIzquierda();
		}else{
			cody->moverLocalDerecha();
		}

		cody->moverGlobalDerecha();
	}

}

void Nivel::setImagesCapas(SDL_Renderer *ren, char const* imagen1, char const* imagen2, char const* imagen3){
	capa1.setImage(ren,imagen1);
	capa2.setImage(ren,imagen2);
	capa3.setImage(ren,imagen3);
}


void Nivel::moverCapasDerecha(){
	capa1.moverDerecha();
	capa2.moverDerecha();
	capa3.moverDerecha();

}
void Nivel::moverCapasIzquierda(){
	capa1.moverIzquierda();
	capa2.moverIzquierda();
	capa3.moverIzquierda();

}

int Nivel::generarXaleatorio(){
	int x = rand()%(static_cast<int>(ANCHO_CAPA_PIXELES_ESCALADA) - MARGEN_DERECHO);
	return x;
}
int Nivel::generarYaleatorio(){
	int y = rand()% (120+1);
	y = 600-245-y;
	return y;
}

int Nivel::generarYaleatorioObjetos(){
	int y = rand()% (70+1); //el 70 es por el alto del cuchilo (objeto mas chico)
	y = 600-100-y; //el 100 es por el alto de la caja (objeto mas grande)
	return y;
}

void Nivel::ubicarEnemigosYElementos(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos){

	FactoryEntidadUbicada factory;
/*
	EntidadUbicada* barril = factory.crearEntidadConBarril(300, JUGADOR_POSICION_VERTICAL_INICIAL+140);
	EntidadUbicada* caja = factory.crearEntidadConCaja(500, JUGADOR_POSICION_VERTICAL_INICIAL+140);
	EntidadUbicada* canio = factory.crearEntidadConCanio(700, JUGADOR_POSICION_VERTICAL_INICIAL+190);
	EntidadUbicada* cuchillo = factory.crearEntidadConCuchillo(900, JUGADOR_POSICION_VERTICAL_INICIAL+190);

	elementos.push_back(barril);
	elementos.push_back(caja);
	elementos.push_back(canio);
	elementos.push_back(cuchillo);
*/
	srand(time(NULL));

	Logger::getInstance()->log(INFO, "Posicionando objetos...");

	for(int i=0; i<cantCuchillos; i++){
		int x = generarXaleatorio();
		int y = generarYaleatorioObjetos();
    Logger::getInstance()->log(DEBUG, std::string("Posición de cuchillo " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");
		EntidadUbicada* cuchillo = factory.crearEntidadConCuchillo(x,y);
		elementos.push_back(cuchillo);
	}
	for(int i=0; i<cantCanios; i++){
		int x = generarXaleatorio();
		int y = generarYaleatorioObjetos();
    Logger::getInstance()->log(DEBUG, std::string("Posición de caño " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");

		EntidadUbicada* canio = factory.crearEntidadConCanio(x,y);
		elementos.push_back(canio);
	}
	for(int i=0; i<cantCajas; i++){
		int x = generarXaleatorio();
		int y = generarYaleatorioObjetos();
    Logger::getInstance()->log(DEBUG, std::string("Posición de caja " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");
		EntidadUbicada* caja = factory.crearEntidadConCaja(x,y);
		elementos.push_back(caja);
	}

	for(int i=0; i<cantBarriles; i++){
		int x = generarXaleatorio();
		int y = generarYaleatorioObjetos();
    Logger::getInstance()->log(DEBUG, std::string("Posición de barril " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");
		EntidadUbicada* barril = factory.crearEntidadConBarril(x,y);
		elementos.push_back(barril);
	}

	Logger::getInstance()->log(INFO, "Posicionando enemigos...");
	for(int i=0; i<cantEnemigos; i++){
		int x = generarXaleatorio();
		int y = generarYaleatorio();
    Logger::getInstance()->log(DEBUG, std::string("Posición inicial de enemigo " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");
		EntidadUbicada* enemigo = factory.crearEntidadConEnemigo(x, y);
		enemigos.push_back(enemigo);
	}

}

void Nivel::moverEnemigos(){

	for (int i = 0; i < enemigos.size(); i++){
		Enemigo* enemigoDibujable = (Enemigo*) enemigos[i]->getDibujable();
		SDL_RendererFlip flip = enemigoDibujable->getFlip();
		if (flip == SDL_FLIP_HORIZONTAL){
			if (!enemigos[i]->llegoBordeGlobalIzquierdo()){
				enemigos[i]->moverGlobalIzquierda();
				enemigos[i]->moverLocalIzquierda();
			}
			else{
				enemigoDibujable->setFlip(SDL_FLIP_NONE);
				enemigos[i]->moverGlobalDerecha();
				enemigos[i]->moverLocalDerecha();
			}
		}
		else{
			if (!enemigos[i]->llegoBordeGlobalDerecho()){
				enemigos[i]->moverGlobalDerecha();
				enemigos[i]->moverLocalDerecha();
			}
			else{
				enemigoDibujable->setFlip(SDL_FLIP_HORIZONTAL);
				enemigos[i]->moverGlobalIzquierda();
				enemigos[i]->moverLocalIzquierda();
			}
		}
	}



}
Personaje* Nivel::getPersonaje() {
	return (Personaje*)this->cody->getDibujable();
}

bool Nivel::terminoElNivel(){
	return cody->llegoBordeGlobalDerecho();
}

