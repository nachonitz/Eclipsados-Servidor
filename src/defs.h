#ifndef SRC_DEFS_H_
#define SRC_DEFS_H_

#include "SDL2/SDL_image.h"

struct informacionRec{
	int animacionActual;
	int movimiento;
	SDL_RendererFlip flip;
	int numeroDeCliente;
};


#define WINDOW_SIZE_HORIZONTAL 800
#define WINDOW_SIZE_VERTICAL 600


#define JUGADOR_SIZE_HORIZONTAL 230
#define JUGADOR_SIZE_VERTICAL 280

#define JUGADOR_POSICION_HORIZONTAL_INICIAL 100
#define JUGADOR_POSICION_VERTICAL_INICIAL 600-250-50

//Para el source
#define ANCHO_CAPA_PIXELES 2250
//Para el destino
#define ANCHO_CAPA_PIXELES_ESCALADA 2250 *2.05

#define MARGEN_IZQUIERDO 50
#define MARGEN_DERECHO 300
#define MARGEN_PISO_ARRIBA 390
#define MARGEN_PISO_ABAJO 270

#define VELOCIDAD_CODY 6
#define VELOCIDAD_SALTO_INICIAL 45
#define ALTURA_MAXIMA 200 //Lo maximo que puede saltar cody
#define GRAVEDAD -10
#define DELTA_T 0.16

#define SALTO_VERTICAL 0
#define SALTO_DERECHA 1
#define SALTO_IZQUIERDA 2


//infoRec.movimiento
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#define STAND 4


//infoRec.animacionActual:
#define ACCION_PARADO 0
#define ACCION_CAMINAR 1
#define ACCION_SALTO 2
#define ACCION_GOLPEAR 3
#define ACCION_SALTO_PATADA 4
#define ACCION_AGACHADO 5
#define ACCION_SALTO_VERTICAL 6

//animados.elementoEnMano
#define ELEMENTO_MANO 0
#define ELEMENTO_CUCHILLO 1
#define ELEMENTO_CANIO 2

#define DANIO_PATADA 75
#define DANIO_CUCHILLO 50
#define DANIO_CANIO 35
#define DANIO_PUNIO 20

#define PUNTOS_PATADA 400
#define PUNTOS_CANIO 200
#define PUNTOS_CUCHILLO 150
#define PUNTOS_PUNIO 100

#define PUNTOS_ENEMIGO 500
#define PUNTOS_BARRIL 300
#define PUNTOS_CAJA 200

#define MAX_CLIENTES 4		// usado en Juego.h

#define FRAME_DELAY 1000/60

#define MAX_CANT_ANIMADOS 100

#define MAX_CANT_ELEMENTOS 200

#define MAX_USER_LEN 30

#define MAX_PASS_LEN 30

#define CANT_HILOS_RECONEXION 50

// HITBOX
#define HBX_DEPTH_DEFECTO 12
#define HBX_EXTRA_HEIGHT_AL_AGARRAR 40

#define PRIMER_GOLPE_A_CAJA -1

#endif /* SRC_DEFS_H_ */
