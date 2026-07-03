#include "../Personaje.hpp"
#include "../../Red/ClienteRed.hpp"

class HeroeRemoto: public Personaje {
private:
	ClienteRed red;

public:
	HeroeRemoto(Posicion posicionInicial);
	~HeroeRemoto();

	void mover() override;

};