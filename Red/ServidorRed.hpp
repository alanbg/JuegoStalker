#include <boost/asio.hpp>

using namespace boost::asio;

class ServidorRed {
private:
	std::unique_ptr<boost::asio::ip::tcp::acceptor> aceptador_;
	std::thread hiloRed_;

	awaitable<void> escribirDatos(std::shared_ptr<ip::tcp::socket> socket);
	awaitable<void> aceptarConexion(io_context& io_context);

public:
	void inicializar(io_context& io_ctx);
};