#include "ClienteRed.hpp"
#include <iostream>

using namespace boost::asio;

awaitable<void> ClienteRed::comunicarCliente(io_context& io_ctx) {
    // Socket TCP
    ip::tcp::socket socket(io_ctx);

    // "Resolutor" traduce a direcciones IP + puerto
    ip::tcp::resolver resolutor(io_ctx);

    auto endpoints = co_await resolutor.async_resolve("localhost", "5000");

    co_await async_connect(socket, endpoints);

    char buffer[128];

    co_await socket.async_read_some(boost::asio::buffer(buffer));

    std::cout << "El servidor dice: " << buffer << std::endl;

}

void ClienteRed::inicializar(io_context& io_ctx) {
    co_spawn(io_ctx, comunicarCliente(io_ctx), detached);

    hiloRed_ = std::thread([&io_ctx]() {
        // Encender motor de eventos asíncronos
        io_ctx.run();
        });
}