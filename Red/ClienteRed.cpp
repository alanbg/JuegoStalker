#include "ClienteRed.hpp"
#include <iostream>

#include <boost/asio/write.hpp>

using namespace boost::asio;

void ClienteRed::enviarDatos(void* datos, int tamano) {
    // Asignar buffer
    // TODO: verificar posibles condiciones de carrera
    send_buf.assign(
        static_cast<const uint8_t*>(datos),
        static_cast<const uint8_t*>(datos) + tamano
    );

}

void ClienteRed::leerDatos(void* datos, int tamano) {
    // Copiar datos del buffer 
    // TODO: verificar posibles condiciones de carrera
    if (recv_buf.size() < tamano) return;
    std::memcpy(datos, recv_buf.data(), tamano);

    // Limpiar el buffer temporal
    recv_buf.clear();
}

void ClienteRed::inicializar(int tamanoMensaje) {
    recv_buf.resize(tamanoMensaje);
    send_buf.resize(tamanoMensaje);

    ip::tcp::resolver resolver(io_ctx);
    auto socket = std::make_shared<ip::tcp::socket>(io_ctx);

    std::cout << "Conectando..." << std::endl;

    // Conectar y recibir handshake inicial de forma síncrona
    boost::asio::connect(*socket, resolver.resolve("localhost", "6005"));

    std::cout << "Conectado al Servidor! "<< std::endl;

    // Lanzar bucle asíncrono
    co_spawn(io_ctx, loop(socket), detached);

    // Lanzar motor de asio en hilo separado
    io_thread = std::thread([&] {
        io_ctx.run();
    });
}

awaitable<void> ClienteRed::loop(std::shared_ptr<ip::tcp::socket> socket) {
    while (true) {
        co_await boost::asio::async_write(*socket, boost::asio::buffer(send_buf));
        std::cout << "Escrito al server: " << send_buf[0] << std::endl;
        co_await boost::asio::async_read(*socket, boost::asio::buffer(recv_buf));
        std::cout << "Leido del server: " << recv_buf[0] << std::endl;
    }
}