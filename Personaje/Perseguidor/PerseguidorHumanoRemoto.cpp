#include "PerseguidorHumanoRemoto.hpp"

PerseguidorHumanoRemoto::PerseguidorHumanoRemoto(Posicion posicionInicial, std::random_device& semilla) {

    posicion = posicionInicial;
    red.inicializar(sizeof(Posicion));

    // "Handshake" inicial
    red.enviarDatos(&semilla, sizeof(semilla));
}

PerseguidorHumanoRemoto::~PerseguidorHumanoRemoto() {

}

void PerseguidorHumanoRemoto::mover() {
    Posicion posicionPerseguidorRemoto;

    // Recibir posición del perseguidor remoto
    red.leerDatos(&posicionPerseguidorRemoto, sizeof(posicionPerseguidorRemoto));

    posicion = posicionPerseguidorRemoto;

}