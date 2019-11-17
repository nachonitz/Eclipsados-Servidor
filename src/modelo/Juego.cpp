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

void Juego::movimientoArriba(int numeroJugador) {
	nivel->movimientoArriba(numeroJugador);
}

void Juego::movimientoSalto(int numeroJugador) {
	nivel->movimientoSalto(numeroJugador);
}

void Juego::terminadoSalto(int numeroJugador) {
	nivel->terminoSalto(numeroJugador);
}

void Juego::movimientoAbajo(int numeroJugador) {
	nivel->movimientoAbajo(numeroJugador);
}

void Juego::movimientoDerecha(int numeroJugador) {
	//nivel->moverCapaDerecha();
	nivel->movimientoDerecha(numeroJugador);
}


void Juego::movimientoIzquierda(int numeroJugador) {
	nivel->movimientoIzquierda(numeroJugador);
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

	cody->procesarAccion(infoRec);


/*

	if(cambiandoNivel[numeroDeCliente]){
		cambiandoNivel[numeroDeCliente] = false;
		saltando[numeroDeCliente] = false;
	}

	if(!saltando[numeroDeCliente] && !agachado[numeroDeCliente] && !golpear[numeroDeCliente]){
		switch(infoRec.movimiento){
				case RIGHT: this->movimientoDerecha(numeroDeCliente);
				break;
				case LEFT: this->movimientoIzquierda(numeroDeCliente);
				break;
				case UP: this->movimientoArriba(numeroDeCliente);
				break;
				case DOWN: this->movimientoAbajo(numeroDeCliente);
				break;
				case STAND: break;
		}
	}

	if(!saltando[numeroDeCliente] && !agachado[numeroDeCliente] && !golpear[numeroDeCliente]){
		switch(infoRec.animacionActual){
			case ACCION_SALTO: 		saltando[numeroDeCliente] = true;
									switch(infoRec.movimiento){
									case RIGHT:
										this->direccionSalto[numeroDeCliente] = 1;
										break;
									case LEFT:
										this->direccionSalto[numeroDeCliente] = -1;
										break;
									}

									alturaActualSalto[numeroDeCliente] = this->getPosicionJugador(numeroDeCliente)->getVertical();
									alturaMaximaSalto[numeroDeCliente] = this->getPosicionJugador(numeroDeCliente)->getVertical() + 25;
									if(animacionActual[numeroDeCliente] != infoRec.animacionActual){
										cody->setAnimacionActual(infoRec.animacionActual, infoRec.flip);
										animacionActual[numeroDeCliente] = infoRec.animacionActual;
									}
			break;
			case ACCION_GOLPEAR: 	golpear[numeroDeCliente] = true;
									if(animacionActual[numeroDeCliente] != infoRec.animacionActual){
										cody->setAnimacionActual(infoRec.animacionActual, infoRec.flip);
										animacionActual[numeroDeCliente] = infoRec.animacionActual;
									}
			break;
			case ACCION_SALTO_PATADA: saltando[numeroDeCliente] = true;
									switch(infoRec.movimiento){
										case RIGHT:	this->direccionSalto[numeroDeCliente] = 1;
										break;
										case LEFT:	this->direccionSalto[numeroDeCliente] = -1;
										break;
										}
										alturaActualSalto[numeroDeCliente] = this->getPosicionJugador(numeroDeCliente)->getVertical();
										alturaMaximaSalto[numeroDeCliente] = this->getPosicionJugador(numeroDeCliente)->getVertical() + 25;
										if(animacionActual[numeroDeCliente] != infoRec.animacionActual){
											cody->setAnimacionActual(infoRec.animacionActual, infoRec.flip);
											animacionActual[numeroDeCliente] = infoRec.animacionActual;
									}
			break;
			case ACCION_AGACHADO: 	agachado[numeroDeCliente] = true;
									if(animacionActual[numeroDeCliente] != infoRec.animacionActual){
										cody->setAnimacionActual(infoRec.animacionActual, infoRec.flip);
										animacionActual[numeroDeCliente] = infoRec.animacionActual;
									}
			break;
			case ACCION_SALTO_VERTICAL: saltando[numeroDeCliente] = true;
										alturaActualSalto[numeroDeCliente] = this->getPosicionJugador(numeroDeCliente)->getVertical();
										alturaMaximaSalto[numeroDeCliente] = this->getPosicionJugador(numeroDeCliente)->getVertical() + 25;
										if(animacionActual[numeroDeCliente] != infoRec.animacionActual){
											cody->setAnimacionActual(infoRec.animacionActual, infoRec.flip);
											animacionActual[numeroDeCliente] = infoRec.animacionActual;
										}
			break;
		}
	}

	if(agachado[numeroDeCliente]){
		if((3 - cody->getTicks()) == 0 ){
			agachado[numeroDeCliente] = false;
			infoRec.animacionActual = ACCION_PARADO;
		}
	}

	if (golpear[numeroDeCliente]){
		if((8 - cody->getTicks()) == 0){
			golpear[numeroDeCliente] = false;
			infoRec.animacionActual = ACCION_PARADO;
		}
	}

	if (saltando[numeroDeCliente] && alturaActualSalto[numeroDeCliente] < alturaMaximaSalto[numeroDeCliente]){
		this->movimientoSalto(numeroDeCliente);
		alturaActualSalto[numeroDeCliente] = this->getPosicionJugador(numeroDeCliente)->getVertical();
		switch(direccionSalto[numeroDeCliente]){
		case 1: this->movimientoDerecha(numeroDeCliente);
		break;

		case 0: break;

		case -1: this->movimientoIzquierda(numeroDeCliente);
		break;
		}
	}

	if(saltando[numeroDeCliente] && alturaActualSalto[numeroDeCliente] > alturaMaximaSalto[numeroDeCliente]){
		this->terminadoSalto(numeroDeCliente);
		saltando[numeroDeCliente] = false;
		direccionSalto[numeroDeCliente] = 0;
		infoRec.animacionActual = ACCION_PARADO;
	}

	if(animacionActual[numeroDeCliente] != infoRec.animacionActual && !saltando[numeroDeCliente] && !agachado[numeroDeCliente] && !golpear[numeroDeCliente]){
		cody->setAnimacionActual(infoRec.animacionActual, infoRec.flip);
		animacionActual[numeroDeCliente] = infoRec.animacionActual;
	}
*/


}


