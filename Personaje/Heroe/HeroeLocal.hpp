#include <memory>
#include <random>
#include "../../UI/UI.hpp"
#include "../../Laberinto/Laberinto.hpp"
#include "../Personaje.hpp"

class HeroeLocal: public Personaje {
public:
	int posicionX;
	int posicionY;

	std::shared_ptr<UI> ui;
	std::shared_ptr<Laberinto> laberinto;

	HeroeLocal(std::shared_ptr<Laberinto> lab, std::shared_ptr<UI> ui);
	HeroeLocal(std::shared_ptr<Laberinto> lab, std::shared_ptr<UI> ui, int posX, int posY);

	void mover(Direccion dir) override;
	void inicializar() override;
};