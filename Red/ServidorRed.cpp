#include "ServidorRed.hpp"
#include <iostream>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>

void ServidorRed::enviarDatos(void* datos, int tamano) {
    // Asignar buffer
    // TODO: verificar posibles condiciones de carrera
    send_buf.assign(
        static_cast<const uint8_t*>(datos),
        static_cast<const uint8_t*>(datos) + tamano
    );
}

void ServidorRed::leerDatos(void* datos, int tamano) {
    // Copiar datos del buffer 
    // TODO: verificar posibles condiciones de carrera
    std::memcpy(datos, recv_buf.data(), tamano);

    // Limpiar el buffer temporal
    recv_buf.clear();
}

void ServidorRed::inicializar(int tamanoMensaje) {
    recv_buf.resize(tamanoMensaje);
    send_buf.resize(tamanoMensaje);

    // Crear acceptor
    ip::tcp::acceptor aceptador(io_ctx, ip::tcp::endpoint( ip::tcp::v4(), 6000 ));

    // Crear el socket
    auto socket = std::make_shared<ip::tcp::socket>(io_ctx);

    // Escuchar y aceptar conexiones
    aceptador.accept(*socket);

    // Enviar handshake inicial
    //boost::asio::write(*socket, boost::asio::buffer(&init, sizeof(init)));

    // Lanzar bucle asíncrono
    co_spawn(io_ctx, loop(socket), detached);

    // Lanzar motor de asio en un hilo separado
    io_thread = std::thread([&] {
        io_ctx.run();
    });
}

awaitable<void> ServidorRed::loop(std::shared_ptr<ip::tcp::socket> socket) {
    while (true) {
        co_await boost::asio::async_write(*socket, boost::asio::buffer(send_buf));
        co_await socket->async_read_some(boost::asio::buffer(recv_buf));
    }
}