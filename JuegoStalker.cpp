#include <curses.h>
#include <array>
#include <random>
#include "JuegoStalker.h"

// Dimensiones del mapa del juego
const int LAB_WIDTH = 21;
const int LAB_HEIGHT = 21;

// Matriz que representa el laberinto
std::array < std::array<int, LAB_HEIGHT>, LAB_WIDTH> laberinto;

void dibujarCaminos(int x, int y) {
    // Marcar celda como visitada (camino libre)
    laberinto[x][y] = 0;
    mvaddch(x, y, ' ');

    std::array < int, 4 > movimientosX = { -2, 2, 0, 0 };
    std::array < int, 4 > movimientosY = { 0, 0, -2, 2 };
    std::array < int, 4 > direcciones = { 0, 1, 2, 3 };

    // Fuente de entropía
    std::random_device semilla;

    // Motor de generación (Mersenne Twister)
    std::mt19937 generador(semilla());

    std::shuffle(direcciones.begin(), direcciones.end(), generador);

    for (int direccion : direcciones) {
        // Decidir nuevos movimientos
        int nuevoX = x + movimientosX[direccion];
        int nuevoY = y + movimientosY[direccion];

        // Verificar límites del laberinto
        bool dentroLaberinto = nuevoX >= 0 &&
            nuevoY >= 0 &&
            nuevoX < LAB_WIDTH &&
            nuevoY < LAB_HEIGHT;

        // Si estamos dentro y si es pared, es un camino potencial
        if (dentroLaberinto && laberinto[nuevoX][nuevoY] == 1) {
            int xMedio = x + (movimientosX[direccion] / 2);
            int yMedio = y + (movimientosY[direccion] / 2);

            // "Derribar" pared intermedia
            laberinto[xMedio][yMedio] = 0;
            mvaddch(xMedio, yMedio, ' ');

            // Avanzar a la siguiente celda
            dibujarCaminos(nuevoX, nuevoY);
        }
        //refresh(); // Aplica los cambios a la pantalla (debug)

    }
       
}

void crearCiclos(float porcentaje) {
    // Fuente de entropía
    std::random_device semilla;

    // Motor de generación (Mersenne Twister)
    std::mt19937 generador(semilla());

    // Distribución uniforme (rango: porcentaje)
    std::uniform_real_distribution distribucion(0.0, 1.0);

    for (int x = 1; x < LAB_WIDTH; x++) {
        for (int y = 1; y < LAB_HEIGHT; y++) {
            // Verificar límites del laberinto
            bool dentroLaberinto = x > 0 &&
                y > 0 &&
                x < LAB_WIDTH-1 &&
                y < LAB_HEIGHT-1;

            // Verificar si la celda es pared y estamos en el limite
            if (dentroLaberinto && laberinto[x][y] == 1 &&
                distribucion(generador) < porcentaje) {

                // "Derribar" pared
                laberinto[x][y] = 0;
                mvaddch(x, y, ' ');

            }
        }
    }
}

void dibujarLaberinto() {
    clear(); // Borra la pantalla anterior

    for (int x = 0; x < LAB_HEIGHT; x++) {
        for (int y = 0; y < LAB_WIDTH; y++) {
            mvaddch(x, y, ACS_BLOCK);

            // Inincializar matriz de laberinto
            laberinto[x][y] = 1;
            //refresh(); // Aplica los cambios a la pantalla (debug)
        }
    }

    dibujarCaminos(1, 1);
    crearCiclos(0.1);

    refresh(); // Aplica los cambios a la pantalla
}

int main()
{
	/*
	*  Inicializar la terminal para permitir "dibujado"
	*/
	initscr();
	noecho();
	curs_set(0);

    //while(true)
        dibujarLaberinto();

    // Restauración obligatoria de la terminal antes de salir
    endwin();

	return 0;
}
