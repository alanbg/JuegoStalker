#include <random>

#include "../Personaje.hpp"
#include "../../Red/ServidorRed.hpp"

class PerseguidorHumanoRemoto : public Personaje {
private:
	ServidorRed red;

public:
	PerseguidorHumanoRemoto(Posicion posicionInicial, std::random_device& semilla);
	~PerseguidorHumanoRemoto();

	void mover() override;

};