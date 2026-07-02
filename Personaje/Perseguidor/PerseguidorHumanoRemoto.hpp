#include "../Personaje.hpp"
#include "../../Red/ServidorRed.hpp"

class PerseguidorHumanoRemoto : public Personaje {
private:
	ServidorRed red;

public:
	PerseguidorHumanoRemoto();
	~PerseguidorHumanoRemoto();

	void mover() override;

};