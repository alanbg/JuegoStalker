#include "../Personaje.hpp"
#include "../../UI/UINcurses.hpp"

class HeroeLocal : public Personaje {
private:
	void moverLocal(Direccion direccion);

public:

	HeroeLocal(Posicion posicionInicial);
	~HeroeLocal();

	void mover() override;

};