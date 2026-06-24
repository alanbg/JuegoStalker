#include <boost/asio.hpp>

using namespace boost::asio;

class ClienteRed {
private:
	awaitable<void> comunicarCliente(io_context& io_context);
	std::thread hiloRed_;

public:
	void inicializar(io_context& io_ctx);
};