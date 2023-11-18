// Copyright 2023 cbravor@fi.uba.ar

#include "client_protocol.h"

#include <cstring>
#include <iostream>
#include <string>

#include <netinet/in.h>

#include "common_liberror.h"

#define CODIGO_JUGADORES 0X06
#define CODIGO_MENSAJE 0X09
#define CODIGO_CHAT 0X05


ClientProtocol::ClientProtocol(const char* hostname, const char* servname):
        skt(hostname, servname) {}


void ClientProtocol::enviar_tamanio_mensaje(const uint16_t& datosEnviar) {
    bool was_closed = false;
    int bytes_enviar = 2;
    uint16_t datosSerializados = htons(datosEnviar);
    skt.sendall(&datosSerializados, bytes_enviar, &was_closed);

    if (was_closed) {
        throw LibError(errno, "No se pudo enviar el tamanio del mensaje\n");
    }
}


void ClientProtocol::obtener_mensaje_broadcast(Message& message) {


    uint8_t codigo_recibido = recibir_codigo_broadcast();

    if (codigo_recibido == CODIGO_JUGADORES) {
        int cantidad_jugadores = recibir_codigo_broadcast();
        message.cargar_mensaje(codigo_recibido, std::to_string(cantidad_jugadores));
    } else if (codigo_recibido == CODIGO_MENSAJE) {
        uint16_t tamanioMensaje = recibir_tamanio_mensaje_broadcast();
        int largoMensaje = static_cast<int>(tamanioMensaje);
        std::string mensaje = recibir_mensaje_broadcast(largoMensaje);
        message.cargar_mensaje(codigo_recibido, mensaje);
    }
}


void ClientProtocol::enviar_mensaje_broadcast(const std::string& mensaje) {
    enviar_codigo_mensaje(CODIGO_CHAT);
    uint16_t longitud_string = static_cast<uint16_t>(mensaje.size());
    enviar_tamanio_mensaje(longitud_string);
    enviar_mensaje(longitud_string, mensaje);
}


void ClientProtocol::enviar_mensaje(const uint16_t& longitudString, const std::string& nombre) {
    bool was_closed = false;

    int tamanio_en_bytes_int = static_cast<int>(longitudString);
    skt.sendall(nombre.c_str(), tamanio_en_bytes_int, &was_closed);

    if (was_closed) {
        throw LibError(errno, "No se pudo enviar el mensaje del chat\n");
    }
}


std::string ClientProtocol::recibir_mensaje_broadcast(const int& tamanioString) {
    bool was_closed = false;
    std::vector<char> buffer_nombre(tamanioString);
    skt.recvall(buffer_nombre.data(), tamanioString, &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje del broadcast \n");
    }

    std::string mensaje(buffer_nombre.begin(), buffer_nombre.end());
    return mensaje;
}

uint16_t ClientProtocol::recibir_tamanio_mensaje_broadcast() {
    bool was_closed = false;
    int cant_bytes_recibidos = 2;
    uint16_t datosRecibidos = 0;
    skt.recvall(&datosRecibidos, cant_bytes_recibidos, &was_closed);
    if (was_closed) {
        throw LibError(errno,
                       "No se pudo recibir el tamanio del mensaje proveniente del broadcast\n");
    }

    return ntohs(datosRecibidos);
}

uint8_t ClientProtocol::recibir_codigo_broadcast() {

    bool was_closed = false;
    int cant_bytes_recibidos = 1;
    uint8_t datosRecibidos = 0;
    skt.recvall(&datosRecibidos, cant_bytes_recibidos, &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se puede recibir el codigo del broadcastr\n");
    }

    return datosRecibidos;
}


void ClientProtocol::enviar_codigo_mensaje(const uint8_t& datosEnviar) {
    bool was_closed = false;
    int bytes_enviar = 1;
    skt.sendall(&datosEnviar, bytes_enviar, &was_closed);

    if (was_closed) {
        throw LibError(errno, "No se pudo enviar el codigo del mensaje\n");
    }
}


void ClientProtocol::cerrar_conexion_socket() {
    skt.shutdown(2);
    skt.close();
}

ClientProtocol::~ClientProtocol() {}
