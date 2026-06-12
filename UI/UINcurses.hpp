#include <curses.h>
#include "UI.hpp"

class UINcurses : public UI {
public:
    UINcurses();
    ~UINcurses();

    void dibujarPared(int x, int y) override;
    void borrarPared(int x, int y) override;
};