// Copyright 2023 cbravor@fi.uba.ar
#include "client_message.h"

#include <iostream>
#define CODIGO_JUGADORES 0X06
#define CODIGO_MENSAJE 0X09

Message::Message() {
    // Implementación del constructor
}

void Message::cargar_mensaje(const int& codigo_mensaje, const std::string& mensaje_obtenido) {
    if (codigo_mensaje == CODIGO_JUGADORES) {
        mensaje_broadcast =
                "Jugadores " + mensaje_obtenido + ", esperando al resto de tus amigos...";
    }

    if (codigo_mensaje == CODIGO_MENSAJE) {
        mensaje_broadcast = mensaje_obtenido;
    }
}


void Message::imprimir_mensaje() { std::cout << mensaje_broadcast << '\n'; }
