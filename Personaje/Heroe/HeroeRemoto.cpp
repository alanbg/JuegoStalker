#include "HeroeRemoto.hpp"

HeroeRemoto::HeroeRemoto() {
    red.inicializar(sizeof(Posicion));
}

HeroeRemoto::~HeroeRemoto() {

}

void HeroeRemoto::mover() {
    Posicion posicionHeroe;
    Posicion miPosicion{ 1, 1 };

    // Recibir posición del heroe remoto
    red.leerDatos(&posicionHeroe, sizeof(posicionHeroe));

    // Enviar mi posición (stalker local) al servidor
    red.enviarDatos(&miPosicion, sizeof(miPosicion));
}