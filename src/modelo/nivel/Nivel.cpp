

#include "Nivel.h"
#include<string>


Nivel::Nivel(int numeroNivel, vector<EntidadUbicada*>& jugadores, int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles, int cantEnemigos, string nombresViejos[MAX_CLIENTES]) {

	this->numeroNivel = numeroNivel;

	this->jugadores = jugadores;

	this->cantEnemigos = cantEnemigos;

	this->cantElementos = cantCuchillos + cantCajas + cantCanios;

	for (int i = 0; i<jugadores.size(); i++){
		jugadoresActivos.push_back(true);
	}
	int i = 0;
	for (EntidadUbicada* entidad : jugadores) {
		entidad->getPosicionGlobal()->trasladarA(JUGADOR_POSICION_HORIZONTAL_INICIAL + i, JUGADOR_POSICION_VERTICAL_INICIAL);
		Personaje* personaje = (Personaje*)entidad->getDibujable();
		personaje->setDest(JUGADOR_POSICION_HORIZONTAL_INICIAL + i, JUGADOR_POSICION_VERTICAL_INICIAL, JUGADOR_SIZE_HORIZONTAL, JUGADOR_SIZE_VERTICAL);
		if(!(personaje->getEstadoMuerto())){
			personaje->resetearEstado();
		}
		i+= 200;
	}

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

	this->ubicarEnemigosYElementos(cantCuchillos, cantCajas, cantCanios, cantBarriles);

	for(uint i = 0; i<enemigos.size(); i++){
		Enemigo* enemigoActual = (Enemigo*) enemigos[i]->getDibujable();
		enemigoActual->setSource(0,0,220,264);
	}

	this->ia = new IA(enemigos, jugadores);

	for(int i=0; i< MAX_CLIENTES; i++){
		nombres[i] = nombresViejos[i];
	}
}

Nivel::~Nivel() {

	for (uint i = 0; i < elementos.size(); i++) {
		delete elementos[i];
	}
}

void Nivel::actualizarAnimaciones(){
	int i = 0;
	for (EntidadUbicada* jugador : jugadores){
		if (jugadoresActivos[i] == true){ //Porque solo se hace animacion si estas conectado
			((Personaje*)jugador->getDibujable())->updateAnim();
		}
		i++;
	}

	for (uint i = 0; i<elementos.size();i++){
		Elemento* elementoActual = (Elemento*) elementos[i]->getDibujable();
		if(elementoActual->getEstadoActual() == NULL){
			elementos.erase(elementos.begin()+i);
			this->cantElementos --;
		}
		else{
			elementoActual->updateAnim();
		}
	}

	for (uint i = 0; i<enemigos.size();i++){
		Enemigo* enemigoActual = (Enemigo*) enemigos[i]->getDibujable();
		if(enemigoActual->getEstadoActual() == NULL){
			enemigos.erase(enemigos.begin()+i);
			this->cantEnemigos --;

		}else{
			enemigoActual->updateAnim();
		}
	}
}

struct informacionEnv Nivel::getInformacion(){
	struct informacionEnv info;

	int i = 0;
	for (EntidadUbicada* jugador : jugadores) {

		Personaje* pjActual = (Personaje*)jugador->getDibujable();
		info.scores[i] = pjActual->getScore();
		info.vidas[i] = pjActual->getVidas();
		info.energia[i] = pjActual->getEnergia();
		strcpy(info.credenciales[i].usuario, this->nombres[i].c_str());
		info.perdieronTodos = pjActual->seReconecto();
		struct animado animadoActual;
		if(!(pjActual->getEstadoMuerto())){
			animadoActual.dest = pjActual->getDest();
			animadoActual.src = pjActual->getSource();
			animadoActual.flip = pjActual->getFlip();
			animadoActual.ID = i;
			animadoActual.elementoEnMano = pjActual->getElementoEnMano();
			animadoActual.estaActivo = jugadoresActivos[i];
			animadoActual.dibujar = true;
			info.animados[i] = animadoActual;
		}else{
			animadoActual.dibujar = false;
			info.animados[i] = animadoActual;
		}

		i++;
	}


	for (uint i = 0; i<enemigos.size(); i++){
		struct animado animadoActual;
		Enemigo* enemigoActual = (Enemigo*) enemigos[i]->getDibujable();
		//if(enemigoActual->getDest() > pos_borde_izquierda  && enemigoActual->getDest() < pos_borde_derecha){
			animadoActual.dest = enemigoActual->getDest();
			animadoActual.src = enemigoActual->getSource();
			animadoActual.flip = enemigoActual->getFlip();
			animadoActual.estaActivo = true;
			animadoActual.tipoEnemigo = enemigoActual->getTipoEnemigo();
			animadoActual.ID = -1;
			info.animados[i + jugadores.size()] = animadoActual;
		//}
	}

	for (uint i = 0;i<elementos.size();i++){
		struct elemento elementoActual;
		Dibujable* dibujable = elementos[i]->getDibujable();
		elementoActual.dest = dibujable->getDest();
		elementoActual.src = dibujable->getSource();
		info.elementos[i] = elementoActual;
	}

	struct capa capa1;
	capa1.dest = this->capa1.getDest();
	capa1.src = this->capa1.getSource();
	capa1.nivel = this->numeroNivel;

	info.capas[0] = capa1;

	struct capa capa2;
	capa2.dest = this->capa2.getDest();
	capa2.src = this->capa2.getSource();
	capa2.nivel = this->numeroNivel;

	info.capas[1] = capa2;

	struct capa capa3;
	capa3.dest = this->capa3.getDest();
	capa3.src = this->capa3.getSource();
	capa3.nivel = this->numeroNivel;

	info.capas[2] = capa3;


	info.cantAnimados = enemigos.size() + jugadores.size();
	info.cantElementos = elementos.size();
	info.cantJugadores = jugadores.size();
	info.nivelActual = this->numeroNivel;

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

void Nivel::moverJugadoresIzquierdaExcepto(int numeroJugador){
	for (uint i = 0; i < jugadores.size(); i++){
		if (i != numeroJugador && !jugadores[i]->llegoBordeLocalIzquierdo())
			jugadores[i]->moverLocalIzquierda();
	}
}

void Nivel::moverJugadoresDerechaExcepto(int numeroJugador){
	for (uint i = 0; i < jugadores.size(); i++){
		if (i != numeroJugador && !jugadores[i]->llegoBordeLocalDerecho())
			jugadores[i]->moverLocalDerecha();
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

void Nivel::movimientoArriba(int numeroJugador, Hitbox& hitbox){
	EntidadUbicada* jugador = jugadores[numeroJugador];

	HitboxUbicada hitboxUbicada(hitbox, *jugador->getPosicionGlobal());
	if (!this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable())) { // ignorar colisiones si ya estoy colisionando!

		hitboxUbicada.desplazarArriba();

		if (this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable()))
			return;
	}

	jugador->moverLocalArriba();
	jugador->moverGlobalArriba();
}

void Nivel::movimientoSalto(int numeroJugador, Hitbox& hitbox, int danio) {

	EntidadUbicada* jugador = jugadores[numeroJugador];

	HitboxUbicada hitboxUbicada(hitbox, *jugador->getPosicionGlobal());

	hitboxUbicada.desplazarSalto();		//calcular hitbox del siguiente tick (mas cerca o lejos del piso)

	Personaje* pjActual = (Personaje*)jugador->getDibujable();

	EstadoPersonaje* estadoActual = pjActual->getEstadoActual();

	if (typeid(*estadoActual) == typeid(EstadoSaltandoConPatada) && danio > 0){
		for (int i = 0; i < 30; i++){
			if (pjActual->getFlip() == SDL_FLIP_NONE){
				hitboxUbicada.desplazarDerecha();
			}else{
				hitboxUbicada.desplazarIzquierda();
			}
		}

	}

	EntidadUbicada* colisionador = this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable());

	// si es un salto vertical o salto al costado, sin danio
	if (colisionador && danio == 0) {
		return;
	}

    if (colisionador && danio != 0 && typeid(*(colisionador->getDibujable())) != typeid(Personaje)){
        puntosExtras = colisionador->getDibujable()->recibirDanio(danio);
        Personaje* pjActual = (Personaje*)jugador->getDibujable();
        if(puntosExtras != PUNTOS_CAJA && puntosExtras != PUNTOS_BARRIL && puntosExtras != PRIMER_GOLPE_A_CAJA){
            pjActual->aumentarScore(PUNTOS_PATADA+puntosExtras);
        }else if(puntosExtras != PRIMER_GOLPE_A_CAJA){
            pjActual->aumentarScore(puntosExtras);
        }
    }

	jugador->moverLocalSalto();
	jugador->moverGlobalSalto();
}

void Nivel::terminoSalto(int numeroJugador, int alturaLocalInicial) {
	jugadores.at(numeroJugador)->terminoLocalSalto(alturaLocalInicial);
	jugadores.at(numeroJugador)->terminoGlobalSalto();
}

Elemento* Nivel::agarrarObjeto(int numeroCliente, Hitbox& hitboxJugador) {

	EntidadUbicada* jugador = jugadores[numeroCliente];

	HitboxUbicada hitboxUbicada(hitboxJugador, *jugador->getPosicionGlobal());

	hitboxUbicada.extenderDepthPorUnFactor(2);

	EntidadUbicada* entidadQueColisiona = this->colisionaConOtroElemento(hitboxUbicada, jugador->getDibujable(), HBX_EXTRA_HEIGHT_AL_AGARRAR);

	if (entidadQueColisiona != nullptr && entidadQueColisiona->getDibujable()->sePuedeAgarrar()) {

		std::vector<EntidadUbicada*>::iterator it = std::find(elementos.begin(), elementos.end(), entidadQueColisiona);
		this->elementos.erase(it);
		this->cantElementos = this->elementos.size();

		return (Elemento*)entidadQueColisiona->getDibujable();
	}

	return nullptr;

}

void Nivel::movimientoAbajo(int numeroJugador, Hitbox& hitbox){

	EntidadUbicada* jugador = jugadores[numeroJugador];

	HitboxUbicada hitboxUbicada(hitbox, *jugador->getPosicionGlobal());

	if (!this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable())) { // ignorar colisiones si ya estoy colisionando!

		hitboxUbicada.desplazarAbajo();

		if (this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable()))
			return;
	}

	jugador->moverLocalAbajo();
	jugador->moverGlobalAbajo();
}

EntidadUbicada* Nivel::colisionaConOtroDibujable(HitboxUbicada& hitboxUbicada, Dibujable* dibujablePropietario) {


	for (EntidadUbicada* jugador : jugadores) {
		if (jugador->getDibujable() != dibujablePropietario && jugador->colisionaCon(hitboxUbicada)) {
			return jugador;
		}
	}

	for (EntidadUbicada* elemento : elementos) {
		if (elemento->getDibujable() != dibujablePropietario && elemento->colisionaCon(hitboxUbicada)) {		//elemento->getDibujable() != dibujablePropietario
			return elemento;																					// no esta demas? el jugador no puede ser un elemento
		}
	}

	for (EntidadUbicada* enemigo : enemigos) {
		if (enemigo->getDibujable() != dibujablePropietario && enemigo->colisionaCon(hitboxUbicada)) {			//elemento->getDibujable() != dibujablePropietario
			return enemigo;																						// no esta demas? el jugador no puede ser un enemigo
		}
	}


	return nullptr;
}

EntidadUbicada* Nivel::colisionaConOtroElemento(HitboxUbicada& hitboxUbicada, Dibujable* dibujablePropietario, int extraHeight) {

	for (EntidadUbicada* elemento : elementos) {
		if (elemento->getDibujable() != dibujablePropietario && elemento->colisionaConMiFactorExtra(hitboxUbicada, 0, extraHeight, 0)) {
			return elemento;
		}
	}

	return nullptr;
}


void Nivel::movimientoIzquierda(int numeroJugador, Hitbox& hitbox){

	EntidadUbicada* jugador = jugadores.at(numeroJugador);

	HitboxUbicada hitboxUbicada(hitbox, *jugador->getPosicionGlobal());

	if (!this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable())) { // ignorar colisiones si ya estoy colisionando!

		hitboxUbicada.desplazarIzquierda();

		if (this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable()))
			return;
	}

	if (!jugador->llegoBordeGlobalIzquierdo()){
		if (jugador->llegoBordeLocalIzquierdo()){

			if (alguienLlegoBordeLocalDerecho()) {	// si alguien bloquea el movimiento...
				return;
			}

			for (int i = 0; i < jugadores.size(); i++){
				if ((jugadores[i]->llegoBordeLocalDerecho() && jugadoresActivos[i] == false) || (((Personaje*)jugadores[i]->getDibujable())->getEstadoMuerto())){
					jugadores[i]->moverGlobalIzquierda();
				}
			}

			pos_borde_izquierda -= VELOCIDAD_CODY;
			pos_borde_derecha -= VELOCIDAD_CODY;
			moverCapasDerecha();
			moverElementosDerecha();
			moverEnemigosDerecha();
			moverJugadoresDerechaExcepto(numeroJugador);
		}else{
			jugador->moverLocalIzquierda();
		}
		jugador->moverGlobalIzquierda();
	}

}

void Nivel::movimientoDerecha(int numeroJugador, Hitbox& hitbox) {

	EntidadUbicada* jugador = jugadores.at(numeroJugador);

	HitboxUbicada hitboxUbicada(hitbox, *jugador->getPosicionGlobal());

	if (!this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable())) { // ignorar colisiones si ya estoy colisionando!

		hitboxUbicada.desplazarDerecha();

		if (this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable())){
			return;
		}
	}

	if (!jugador->llegoBordeGlobalDerecho()){
		if (jugador->llegoBordeLocalDerecho()){

			if (alguienLlegoBordeLocalIzquierdo()) {	// si alguien bloquea el movimiento...
				return;
			}

			for (int i = 0; i < jugadores.size(); i++){
				if ((jugadores[i]->llegoBordeLocalIzquierdo() && jugadoresActivos[i] == false) || (((Personaje*)jugadores[i]->getDibujable())->getEstadoMuerto())){
					jugadores[i]->moverGlobalDerecha();
				}
			}

			pos_borde_derecha += VELOCIDAD_CODY;
			pos_borde_izquierda += VELOCIDAD_CODY;
			moverCapasIzquierda();
			moverElementosIzquierda();
			moverEnemigosIzquierda();
			moverJugadoresIzquierdaExcepto(numeroJugador);
		}else {
			jugador->moverLocalDerecha();
		}

		jugador->moverGlobalDerecha();
	}

}

bool Nivel::alguienLlegoBordeLocalDerecho() {
	int i = 0;
	for (EntidadUbicada* jugador : jugadores) {
		if ((jugador->llegoBordeLocalDerecho() && jugadoresActivos[i] == true) && !(((Personaje*)jugadores[i]->getDibujable())->getEstadoMuerto()))
			return true;
		i++;
	}

	return false;
}

bool Nivel::alguienLlegoBordeLocalIzquierdo() {
	int i = 0;
	for (EntidadUbicada* jugador : jugadores) {
		if ((jugador->llegoBordeLocalIzquierdo() && jugadoresActivos[i] == true ) && !(((Personaje*)jugadores[i]->getDibujable())->getEstadoMuerto()))
			return true;

		i++;
	}

	return false;
}


bool Nivel::alguienLlegoBordeGlobalDerecho() {
	for (EntidadUbicada* jugador : jugadores) {
		if (jugador->llegoBordeGlobalDerecho())
			return true;
	}

	return false;
}

bool Nivel::alguienLlegoBordeGlobalIzquierdo() {
	for (EntidadUbicada* jugador : jugadores) {
		if (jugador->llegoBordeGlobalIzquierdo())
			return true;
	}

	return false;
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

int Nivel::generarXaleatorioEnemigo(){
	int x = rand()%(static_cast<int>(ANCHO_CAPA_PIXELES_ESCALADA) - MARGEN_DERECHO - WINDOW_SIZE_HORIZONTAL - 100);
	return x + WINDOW_SIZE_HORIZONTAL + 100;
}

int Nivel::generarXaleatorio(){
	int x = rand()%(static_cast<int>(ANCHO_CAPA_PIXELES_ESCALADA) - MARGEN_DERECHO - MARGEN_IZQUIERDO - 150);
	return x + MARGEN_IZQUIERDO + 50;
}
int Nivel::generarYaleatorioEnemigos(){
	int y = rand()% (120+1);
	y = 600-245-y;
	return y;
}

int Nivel::generarYaleatorioCuchillosYCanios(){
	int y = rand()% (70+1); //el 70 es por el alto del cuchilo (objeto mas chico)
	y = 600-100-y; //el 100 es por el alto de la caja (objeto mas grande)
	return y;
}

int Nivel::generarYaleatorioBarriles(){
	int y = rand()% (70+1); //el 70 es por el alto del cuchilo (objeto mas chico)
	y = 600-260-y; //el 100 es por el alto de la caja (objeto mas grande)
	return y;
}

int Nivel::generarYaleatorioCajas(){
	int y = rand()% (70+1); //el 70 es por el alto del cuchilo (objeto mas chico)
	y = 600-200-y; //el 100 es por el alto de la caja (objeto mas grande)
	return y;
}

void Nivel::ubicarEnemigosYElementos(int cantCuchillos, int cantCajas, int cantCanios, int cantBarriles){

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
		int y = generarYaleatorioCuchillosYCanios();
    Logger::getInstance()->log(DEBUG, std::string("Posición de cuchillo " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");
		EntidadUbicada* cuchillo = factory.crearEntidadConCuchillo(x,y);
		elementos.push_back(cuchillo);
	}
	for(int i=0; i<cantCanios; i++){
		int x = generarXaleatorio();
		int y = generarYaleatorioCuchillosYCanios();
    Logger::getInstance()->log(DEBUG, std::string("Posición de caño " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");

		EntidadUbicada* canio = factory.crearEntidadConCanio(x,y);
		elementos.push_back(canio);
	}
	for(int i=0; i<cantCajas; i++){
		int x = generarXaleatorio();
		int y = generarYaleatorioCajas();
    Logger::getInstance()->log(DEBUG, std::string("Posición de caja " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");
		EntidadUbicada* caja = factory.crearEntidadConCaja(x,y);
		elementos.push_back(caja);
	}

	for(int i=0; i<cantBarriles; i++){
		int x = generarXaleatorio();
		int y = generarYaleatorioBarriles();
    Logger::getInstance()->log(DEBUG, std::string("Posición de barril " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");
		EntidadUbicada* barril = factory.crearEntidadConBarril(x,y);
		elementos.push_back(barril);
	}

	Logger::getInstance()->log(INFO, "Posicionando enemigos...");
	for(int i=0; i<this->cantEnemigos; i++){
		int x = generarXaleatorioEnemigo();
		int y = generarYaleatorioEnemigos();
    Logger::getInstance()->log(DEBUG, std::string("Posición inicial de enemigo " +
                                                  std::to_string(i+1) + ": (" +
                                                  std::to_string(x) + ", " +
                                                  std::to_string(y)) + ")");
    	int tipoEnemigo = rand() % 3;
		EntidadUbicada* enemigo = factory.crearEntidadConEnemigo(x, y, tipoEnemigo);
		enemigos.push_back(enemigo);
	}

}


vector<bool> Nivel::getJugadoresActivos() {
	return this->jugadoresActivos;
}
void Nivel::setJugadoresActivos(vector<bool> jugadores) {
	this->jugadoresActivos = jugadores;
}

void Nivel::desconexionDeJugador(int i) {
	jugadoresActivos[i] = false;
	((Personaje*)jugadores[i]->getDibujable())->disableTestMode();
	((Personaje*)jugadores[i]->getDibujable())->disableHitbox();

}

void Nivel::conexionDeJugador(int i) {
	jugadoresActivos[i] = true;
	((Personaje*)jugadores[i]->getDibujable())->enableHitbox();
}

bool Nivel::jugadorConectado(int i) {
	return jugadoresActivos[i];
}

void Nivel::moverEnemigos(){
	this->ia->moverEnemigos(this->pos_borde_derecha, this->pos_borde_izquierda, this->jugadoresActivos, this->elementos);
}

Personaje* Nivel::getPersonaje(int numeroJugador) {
	return (Personaje*)jugadores.at(numeroJugador)->getDibujable();
}

bool Nivel::terminoElNivel(){

	// si al menos uno llego y mataron todos los enemigos
	return (alguienLlegoBordeGlobalDerecho() && enemigos.size() == 0);

}


bool Nivel::hacerDanio(int numeroJugador, Hitbox hitbox, int danio, int score){
	bool hizoDanio = false;

	EntidadUbicada* jugador = jugadores.at(numeroJugador);

	HitboxUbicada hitboxUbicada(hitbox, *jugador->getPosicionGlobal());

	Personaje* personaje = (Personaje*) jugador->getDibujable();

	EntidadUbicada* colisionador = this->colisionaConOtroDibujable(hitboxUbicada, jugador->getDibujable());

	if (colisionador != NULL && colisionador->getDibujable()->getVidas() > 0 && typeid(*(colisionador->getDibujable())) != typeid(Personaje)){
		hizoDanio = true;
		puntosExtras = colisionador->getDibujable()->recibirDanio(danio);
		Personaje* pjActual = (Personaje*)jugador->getDibujable();
		if(puntosExtras != PUNTOS_CAJA && puntosExtras != PUNTOS_BARRIL && puntosExtras != PRIMER_GOLPE_A_CAJA){
			pjActual->aumentarScore(score+puntosExtras);
		}else if(puntosExtras != PRIMER_GOLPE_A_CAJA){
			pjActual->aumentarScore(puntosExtras);
		}
	}
	return hizoDanio;
}

void Nivel::hacerDanioEnemigo(EntidadUbicada* jugador, Hitbox hitbox, int danio){

	HitboxUbicada hitboxUbicada(hitbox, *jugador->getPosicionGlobal());

	Personaje* personaje = (Personaje*) jugador->getDibujable();

	personaje->recibirDanio(danio);

}

void Nivel::cargarFinalBoss(){
	float horizontalGlobal = ANCHO_CAPA_PIXELES_ESCALADA - WINDOW_SIZE_HORIZONTAL + JUGADOR_POSICION_HORIZONTAL_INICIAL - 150 - 400;
	EntidadUbicada* boss = factory.crearEntidadConBoss(JUGADOR_POSICION_HORIZONTAL_INICIAL - 400,JUGADOR_POSICION_VERTICAL_INICIAL,horizontalGlobal, JUGADOR_POSICION_VERTICAL_INICIAL);/*ANCHO_CAPA_PIXELES_ESCALADA - WINDOW_SIZE_HORIZONTAL - 20 , WINDOW_SIZE_VERTICAL + 100, FINAL_BOSS);*/
	boss->getDibujable()->setSource(0,0,325,280);
	enemigos.push_back(boss);
	ia->setEnemigos(this->enemigos);
	this->cantEnemigos = enemigos.size();

}

bool Nivel::todosMuertos(){

	for(uint i = 0; i < jugadores.size(); i++){
		if(((Personaje*)jugadores[i]->getDibujable())->getVidas() > 0){
			return false;
		}
	}
	return true;
}

void Nivel::setNombresUsuario(string nombresApasar[MAX_CLIENTES], int cantClientes){
	for(int i=0; i<cantClientes; i++){
		nombres[i] = nombresApasar[i];
	}
}

string Nivel::getNombres(int i){

	return nombres[i];

}

void Nivel::jugadorReConectado(int i){
	((Personaje*)jugadores[i]->getDibujable())->reconexion();
}
