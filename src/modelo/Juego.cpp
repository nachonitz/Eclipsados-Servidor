#include "Juego.h"
#include "../Logger.h"

Juego::Juego(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos, int cantJugadores) {

	this->cuchillos = cantCuchillos;
	this->cajas = cantCajas;
	this->canios = cantCanios;
	this->barriles = cantBarriles;
	this->enemigos = cantEnemigos;

	for (int i = 0; i < MAX_CLIENTES; i++){
		this->cambiandoNivel[i] = false;
	}

	FactoryEntidadUbicada factory;

	for (int i = 0; i < cantJugadores; i++) {

		this->jugadores.push_back(factory.crearEntidadConPersonaje());

	}

  Logger::getInstance()->log(INFO, "******** NIVEL 1 ********");
	this-> nivel = new Nivel(1,jugadores, cantCuchillos, cantCajas, cantCanios, cantBarriles, cantEnemigos);

	EstadoPersonaje::setNivel(nivel);

}

Juego::~Juego() {
	// TODO Auto-generated destructor stub
	for (EntidadUbicada* entidad : jugadores) {
		delete entidad->getDibujable();
		delete entidad;
	}
}

PosicionGlobal* Juego::getPosicionJugador(int numeroJugador) {
	return jugadores.at(numeroJugador)->getPosicionGlobal();
}

void Juego::desconexionDeJugador(int i) {
	this->nivel->desconexionDeJugador(i);
}

void Juego::conexionDeJugador(int i) {
	this->nivel->conexionDeJugador(i);
}

bool Juego::jugadorConectado(int i) {
	return this->nivel->jugadorConectado(i);
}


void Juego::moverEnemigos(){
	nivel->moverEnemigos();
}

Personaje* Juego::getJugador(int numeroJugador) {
	return nivel->getPersonaje(numeroJugador);
}

bool Juego::terminoElNivel(){
	return this->nivel->terminoElNivel();
}

void Juego::cambiarDeNivel(){

	//Logger::getInstance()->log(INFO, "******** NIVEL 2 ********");

	for (EntidadUbicada* jugador : jugadores) {
		jugador->seCambioElNivel(jugador->getDibujable());
	}

	vector<bool> activos = nivel->getJugadoresActivos();

	delete(nivel);

	nivel = new Nivel(2,jugadores, cuchillos, cajas, canios, barriles, enemigos);

	nivel->setJugadoresActivos(activos);

	EstadoPersonaje::setNivel(nivel);
}

void Juego::chequearCambioDeNivel() {
	if(terminoElNivel() && nivel->esPrimerNivel()){
		cambiarDeNivel();
		for(int i = 0; i < MAX_CLIENTES; i++){
			cambiandoNivel[i] = true;
		}
	}
}


void Juego::procesarInfo(struct informacionRec infoRec){

	int numeroDeCliente = infoRec.numeroDeCliente;
	Personaje* cody = (Personaje *)jugadores.at(numeroDeCliente)->getDibujable();

	if(!(cody->getEstadoMuerto())){
		cody->procesarAccion(infoRec);
	}


}


