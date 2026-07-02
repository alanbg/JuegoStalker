#include "PerseguidorHumanoRemoto.hpp"

PerseguidorHumanoRemoto::PerseguidorHumanoRemoto() {
    red.inicializar(sizeof(Posicion));
}

PerseguidorHumanoRemoto::~PerseguidorHumanoRemoto() {

}

void PerseguidorHumanoRemoto::mover() {
    Posicion posicionPerseguidor;
    Posicion miPosicion{ 1, 1 };

    // Recibir posición del perseguidor remoto
    red.leerDatos(&posicionPerseguidor, sizeof(posicionPerseguidor));

    // Enviar mi posición (heroe local) al cliente
    red.enviarDatos(&miPosicion, sizeof(miPosicion));
}