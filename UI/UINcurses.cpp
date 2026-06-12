#include "UINcurses.hpp"

UINcurses::UINcurses() {
    initscr();
    noecho();
    curs_set(0);

    clear(); // Borra la pantalla anterior
}
UINcurses::~UINcurses() {
    // Restauración obligatoria de la terminal antes de salir
    endwin();
}

void UINcurses::dibujarPared(int x, int y) {
    mvaddch(x, y, ACS_BLOCK);
    refresh();

}
void UINcurses::borrarPared(int x, int y) {
    mvaddch(x, y, ' ');
    refresh();

}
