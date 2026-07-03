#include "../Personaje.hpp"
#include "../../UI/UINcurses.hpp"
#include "../../Red/ClienteRed.hpp"


class PerseguidorHumanoLocal : public Personaje {
private:
	void moverLocal(Direccion direccion);
	ClienteRed red;
public:

	PerseguidorHumanoLocal(Posicion posicionInicial);
	~PerseguidorHumanoLocal();

	void mover() override;

};