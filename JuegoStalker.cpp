
#include "JuegoStalker.hpp"

int main()
{
	std::shared_ptr<UI> ui;

#ifdef CURSES
	ui = std::make_shared<UINcurses>();
#elif QT
//	ui = std::make_shared<UIQT>();
#else
	if (ui == nullptr) {
		std::cout << "Ninguna biblioteca de UI disponible" << std::endl;
		return -1;
	}
#endif

	std::shared_ptr<Laberinto> laberinto = std::make_shared<Laberinto>(ui);

	laberinto->dibujarLaberinto();

	// Game loop
	//while(true) {
	// 
	//}

	return 0;
}
