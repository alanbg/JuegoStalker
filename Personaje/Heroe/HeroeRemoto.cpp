#include "HeroeRemoto.hpp"
#include <iostream>

HeroeRemoto::HeroeRemoto(Posicion posicionInicial) {
    posicion = posicionInicial;
    red.inicializar(sizeof(Posicion));
}

HeroeRemoto::~HeroeRemoto() {

}

void HeroeRemoto::mover() {
    Posicion posicionHeroeRemoto;

    // Recibir posición del heroe remoto
    red.leerDatos(&posicionHeroeRemoto, sizeof(posicionHeroeRemoto));

    posicion = posicionHeroeRemoto;

}