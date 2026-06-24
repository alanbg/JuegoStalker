
enum class Direccion {
	ARRIBA = 0,
	ABAJO,
	IZQUIERDA,
	DERECHA
};

class Personaje {
public:
	virtual void mover(Direccion dir) = 0;
	virtual void inicializar() = 0;
};