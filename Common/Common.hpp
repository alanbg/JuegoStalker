#pragma once
#include <cstdint>

enum class Direccion {
	ARRIBA = 0,
	ABAJO,
	IZQUIERDA,
	DERECHA
};

enum class Estado {
	JUGANDO = 0,
	GANADO,
	PERDIDO
};

struct Posicion {
	uint8_t  posicionX;
	uint8_t  posicionY;
};

struct Llave {
	uint8_t posicionX;
	uint8_t posicionY;

	bool recolectada;
};

struct EstadoJuego {
	Llave llaves[3];
	Posicion salida;

	Estado estado;
};