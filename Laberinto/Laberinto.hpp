#include <array>
#include <random>

#include <curses.h>

// Dimensiones del mapa del juego
const int LAB_WIDTH = 21;
const int LAB_HEIGHT = 21;

class UI {
public:
    virtual void dibujarPared(int x, int y) = 0;
    virtual void borrarPared(int x, int y) = 0;
    virtual ~UI() = default;
};

class UINcurses : public UI {
public:
    UINcurses();
    ~UINcurses();

    void dibujarPared(int x, int y) override;
    void borrarPared(int x, int y) override;
};

class Laberinto {
private:
    // Matriz que representa el laberinto
    std::array < std::array<int, LAB_HEIGHT>, LAB_WIDTH> laberinto;

    void dibujarCaminos(int x, int y);
    void crearCiclos(float porcentaje);

    std::shared_ptr<UI> ui;

public:
    Laberinto(std::shared_ptr<UI> ui);

    void dibujarLaberinto();
    //bool esPared(int x, int y);
};