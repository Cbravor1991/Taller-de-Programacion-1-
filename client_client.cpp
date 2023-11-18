// Copyright 2023 cbravor@fi.uba.ar

#include "client_client.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

Client::Client(const char* hostname, const char* servname):
        clientProtocol(hostname, servname), message() {}

int Client::run() {

    std::string comando;
    std::string mensaje;
    std::string cant_mensajes_a_leer;


    while (std::cin >> comando) {


        if (comando != "Chat" && comando != "Read" && comando != "Exit") {
            continue;
        }

        if (comando == "Chat") {


            std::getline(std::cin, mensaje);

            mensaje.erase(mensaje.begin(), std::find_if(mensaje.begin(), mensaje.end(),
                                                        [](int ch) { return !std::isspace(ch); }));

            clientProtocol.enviar_mensaje_broadcast(mensaje);

        } else if (comando == "Read") {


            std::cin >> cant_mensajes_a_leer;
            leer_mensajes_broadcast(cant_mensajes_a_leer);

        } else if (comando == "Exit") {

            clientProtocol.cerrar_conexion_socket();
            break;
        }
    }


    return 0;
}


void Client::leer_mensajes_broadcast(const std::string& cantidad_mensajes) {

    int cantidad = std::stoul(cantidad_mensajes);
    for (int i = 0; i < cantidad; i++) {
        clientProtocol.obtener_mensaje_broadcast(message);
        message.imprimir_mensaje();
    }
}
