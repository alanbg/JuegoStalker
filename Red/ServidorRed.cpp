#include "ServidorRed.hpp"
#include <iostream>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>

void ServidorRed::enviarDatos(void* datos, int tamano) {
    // Asignar buffer
    // TODO: verificar posibles condiciones de carrera
    send_buf.assign( static_cast<const uint8_t*>(datos), static_cast<const uint8_t*>(datos) + tamano );
}

void ServidorRed::leerDatos(void* datos, int tamano) {
    // Copiar datos del buffer 
    // TODO: verificar posibles condiciones de carrera
    if (recv_buf.size() < tamano) return;
    std::memcpy(datos, recv_buf.data(), tamano);

    // Limpiar el buffer temporal
    recv_buf.clear();
}

void ServidorRed::inicializar(int tamanoMensaje) {
    recv_buf.resize(1);
    send_buf.resize(1);

    // Crear acceptor
    ip::tcp::acceptor aceptador(io_ctx, ip::tcp::endpoint( ip::tcp::v4(), 6005 ));

    // Crear el socket
    auto socket = std::make_shared<ip::tcp::socket>(io_ctx);

    // Escuchar y aceptar conexiones
    aceptador.accept(*socket);

    std::cout << "Cliente conectado!" << std::endl;

    // Enviar handshake inicial (semilla)
    //boost::asio::write(*socket, boost::asio::buffer("12345678"));

    // Lanzar bucle asíncrono
    co_spawn(io_ctx, loop(socket), detached);

    // Lanzar motor de asio en un hilo separado
    io_thread = std::thread([&] {
        io_ctx.run();
    });
}

awaitable<void> ServidorRed::loop(std::shared_ptr<ip::tcp::socket> socket) {
    while (true) {
        co_await boost::asio::async_read(*socket, boost::asio::buffer(recv_buf));
        std::cout << "Leido del cliente: " << recv_buf[0] << std::endl;
        co_await boost::asio::async_write(*socket, boost::asio::buffer(send_buf));
        std::cout << "Escrito al cliente: " << send_buf[0] << std::endl;
    }
}