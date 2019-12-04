#include "Juego.h"
#include "../Logger.h"
#include <string>

Juego::Juego(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos, int cantJugadores) {

	this->cuchillos = cantCuchillos;
	this->cajas = cantCajas;
	this->canios = cantCanios;
	this->barriles = cantBarriles;
	this->enemigos = cantEnemigos;
	this->aparecioElFinalBoss = false;

	for (int i = 0; i < MAX_CLIENTES; i++){
		this->cambiandoNivel[i] = false;
	}

	FactoryEntidadUbicada factory;

	for (int i = 0; i < cantJugadores; i++) {

		this->jugadores.push_back(factory.crearEntidadConPersonaje());

	}

  Logger::getInstance()->log(INFO, "******** NIVEL 1 ********");
  string nombres[MAX_CLIENTES];
	this-> nivel = new Nivel(1,jugadores, cantCuchillos, cantCajas, cantCanios, cantBarriles, cantEnemigos, nombres);

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
	std::string nombres[MAX_CLIENTES];
	for(int i= 0; i < MAX_CLIENTES; i++){
		nombres[i] = nivel->getNombres(i);
	}

	delete(nivel);

	nivel = new Nivel(2,jugadores, cuchillos, cajas, canios, barriles, enemigos, nombres);

	nivel->setJugadoresActivos(activos);

	EstadoPersonaje::setNivel(nivel);
}

bool Juego::chequearCambioDeNivel() {
	bool resultado = false;
	if(nivel->todosMuertos()){
		nivel->finalizarPartida();
	}
	if(terminoElNivel() && nivel->esPrimerNivel()){
		cambiarDeNivel();
		resultado = true;
		for(int i = 0; i < MAX_CLIENTES; i++){
			cambiandoNivel[i] = true;
		}
	}else if(terminoElNivel() && nivel->esSegundoNivel() && !aparecioElFinalBoss){
		aparecioElFinalBoss = true;
		nivel->cargarFinalBoss();
	}else if(terminoElNivel() && aparecioElFinalBoss){
		nivel->finalizarPartida();
	}
	return resultado;
}


void Juego::procesarInfo(struct informacionRec infoRec){

	int numeroDeCliente = infoRec.numeroDeCliente;
	Personaje* cody = (Personaje *)jugadores.at(numeroDeCliente)->getDibujable();

	if (infoRec.animacionActual == ACCION_TESTMODE) {
		bool modoActual = cody->toggleTestMode();
		Logger::getInstance()->log(INFO, "Test Mode seteado en " + std::to_string(modoActual) + " para jugador numero " + std::to_string(numeroDeCliente));

		return;
	}

	if(!(cody->getEstadoMuerto())){
		cody->procesarAccion(infoRec);
	}

}

void Juego::setNombresUsuario(string nombresApasar[4], int cantClientes){

	nivel->setNombresUsuario(nombresApasar, cantClientes);
}
