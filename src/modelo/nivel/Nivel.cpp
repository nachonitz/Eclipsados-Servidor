

#include "Nivel.h"

Nivel::Nivel(int numeroNivel, EntidadUbicada* jugador, int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos) {

	musicaFondo = new Sonido(numeroNivel);
	(*musicaFondo).play();

	cody = jugador;

	capa1.setVelocidad(VELOCIDAD_CODY);
	capa2.setVelocidad(2);
	capa3.setVelocidad(1);

	this->movimientoEnemigos = 0;


	this->ubicarEnemigosYElementos(cantCuchillos, cantCajas, cantCanios, cantBarriles, cantEnemigos);
}

Nivel::~Nivel() {
	//delete cody;
	delete musicaFondo;

	for (uint i = 0; i < elementos.size(); i++) {
		delete elementos[i];
	}
}

void Nivel::actualizarAnimaciones(){
	Personaje* personaje = (Personaje*) this->cody->getDibujable();
	personaje->updateAnim();
	for (uint i = 0; i<enemigos.size();i++){
		Enemigo* enemigoActual = (Enemigo*) enemigos[i]->getDibujable();
		enemigoActual->updateAnim();
	}
}

struct informacion Nivel::getInformacion(){
	struct informacion info;
	vector<struct animado> animados;
	vector<struct elemento> objetos;
	vector<struct capa> capas;

	for (uint i = 0;i<enemigos.size();i++){
		struct animado animadoActual;
		Enemigo* enemigoActual = (Enemigo*) enemigos[i]->getDibujable();
		animadoActual.dest = enemigoActual->getDest();
		animadoActual.src = enemigoActual->getSource();
		animadoActual.txt = enemigoActual->getTexture();
		animadoActual.flip = enemigoActual->getFlip();
		animados.push_back(animadoActual);
	}
	Personaje* personaje = (Personaje*)cody->getDibujable();
	struct animado animadoActual;
	animadoActual.dest = personaje->getDest();
	animadoActual.txt = personaje->getTexture();
	animadoActual.src = personaje->getSource();
	animadoActual.flip = personaje->getFlip();
	animados.push_back(animadoActual);

	for (uint i = 0;i<elementos.size();i++){
		struct elemento elementoActual;
		Dibujable* dibujable = elementos[i]->getDibujable();
		elementoActual.dest = dibujable->getDest();
		elementoActual.src = dibujable->getSource();
		elementoActual.txt = dibujable->getTexture();
		objetos.push_back(elementoActual);
	}

	struct capa capa1;
	capa1.dest = this->capa1.getDest();
	capa1.src = this->capa1.getSource();
	capa1.txt= this->capa1.getTexture();
	capas.push_back(capa1);
	struct capa capa2;
	capa2.dest = this->capa2.getDest();
	capa2.src = this->capa2.getSource();
	capa2.txt = this->capa2.getTexture();
	capas.push_back(capa1);
	struct capa capa3;
	capa3.dest = this->capa3.getDest();
	capa3.src = this->capa3.getSource();
	capa3.txt = this->capa3.getTexture();
	capas.push_back(capa3);

	info.animados = animados;
	info.capas = capas;
	info.elementos = objetos;
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

