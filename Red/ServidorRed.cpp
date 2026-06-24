#include "ServidorRed.hpp"
#include <iostream>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>

using namespace boost::asio;

awaitable<void> ServidorRed::escribirDatos(std::shared_ptr<ip::tcp::socket> socket) {

    co_await async_write(*socket, buffer("Hola!"));
}

awaitable<void> ServidorRed::aceptarConexion(io_context& io_ctx) {
    while (true) {

        auto socket = std::make_shared<ip::tcp::socket>(io_ctx);

        co_await aceptador_->async_accept(*socket);

        co_spawn(io_ctx, escribirDatos(socket), detached);
    }
}

void ServidorRed::inicializar(io_context& io_ctx) {
    aceptador_ = std::make_unique<ip::tcp::acceptor>(io_ctx, ip::tcp::endpoint(ip::tcp::v4(), 5000));

    co_spawn(io_ctx, aceptarConexion(io_ctx), detached);

    hiloRed_ = std::thread([&io_ctx]() {
        io_ctx.run();
        });

}