#include <curses.h>

#include "JuegoStalker.h"
#include "Laberinto/Laberinto.hpp"

int main()
{
	std::shared_ptr<UI> ui;

//#ifdef CURSES
	ui = std::make_shared<UINcurses>();
//#endif

	if (ui == nullptr) {
		std::cout << "Ninguna biblioteca de UI disponible" << std::endl;
		return -1;
	}

	std::shared_ptr<Laberinto> laberinto = std::make_shared<Laberinto>(ui);
	laberinto->dibujarLaberinto();

	// Game loop
	//while(true) {
	// 
	//}

	return 0;
}
