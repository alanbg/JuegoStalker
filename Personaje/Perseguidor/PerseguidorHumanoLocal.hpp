#include "../Personaje.hpp"
#include "../../UI/UINcurses.hpp"

class PerseguidorHumanoLocal : public Personaje {
private:
	void moverLocal(Direccion direccion);

public:

	PerseguidorHumanoLocal();
	~PerseguidorHumanoLocal();

	void mover() override;

};