// Copyright 2023 cbravor@fi.uba.ar

#include "server_protocol.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include <netinet/in.h>

#include "common_liberror.h"

#define CODIGO_JUGADORES 0X06
#define CODIGO_MENSAJES 0X09
#define CHAT_IDENTIFICADOR 0X05
#define CANT_BYTES_DATOS_JUGADOR 1
#define CANT_BYTES_TAMANIO_MENSAJE 2


ServerProtocol::ServerProtocol(Socket skt_cliente, Game& game,
                               Queue<BroadcastMessage>& cola_cliente):
        skt(std::move(skt_cliente)), game(game), cola_cliente(cola_cliente) {}


uint8_t ServerProtocol::recibir_dato_jugador() {

    bool was_closed = false;
    int cant_bytes_recibidos = 1;
    uint8_t datosRecibidos = 0;
    skt.recvall(&datosRecibidos, cant_bytes_recibidos, &was_closed);
    if (was_closed) {
        sigo_vivo = false;
    }
    return datosRecibidos;
}


uint16_t ServerProtocol::recibir_tamanio_mensaje() {

    bool was_closed = false;
    int cant_bytes_recibidos = 2;
    uint16_t datosRecibidos = 0;
    skt.recvall(&datosRecibidos, cant_bytes_recibidos, &was_closed);
    if (was_closed) {
        sigo_vivo = false;
    }
    return ntohs(datosRecibidos);
}


std::string ServerProtocol::recibir_mensaje_chat(const int& tamanioString) {

    bool was_closed = false;
    std::vector<char> buffer_mensaje(tamanioString);
    skt.recvall(buffer_mensaje.data(), tamanioString, &was_closed);
    if (was_closed) {
        sigo_vivo = false;
    }
    std::string mensaje(buffer_mensaje.begin(), buffer_mensaje.end());
    return mensaje;
}


BroadcastMessage ServerProtocol::recibir_mensaje_jugador() {

    BroadcastMessage broadcast;
    uint8_t datosRecibidos = recibir_dato_jugador();
    if (datosRecibidos == CHAT_IDENTIFICADOR) {
        int longitud_string = static_cast<int>(recibir_tamanio_mensaje());
        std::string mensaje = recibir_mensaje_chat(longitud_string);
        broadcast.cargar_codigo(CODIGO_MENSAJES);
        broadcast.cargar_mesaje_recibido(mensaje);
    }

    return broadcast;
}

void ServerProtocol::enviar_mensaje_jugador(const uint16_t& longitudString,
                                            const std::string& mensaje) {

    bool was_closed = false;
    int tamanio_en_bytes_int = static_cast<int>(longitudString);
    skt.sendall(mensaje.c_str(), tamanio_en_bytes_int, &was_closed);
    if (was_closed) {
        sigo_vivo = false;
    }
}


void ServerProtocol::enviar_datos_jugador(const uint8_t& datosEnviar) {


    bool was_closed = false;
    int bytes_enviar = 1;
    skt.sendall(&datosEnviar, bytes_enviar, &was_closed);
    if (was_closed) {
        sigo_vivo = false;
    }
}


void ServerProtocol::enviar_tamanio_mensaje(const uint16_t& datosEnviar) {
    bool was_closed = false;
    int bytes_enviar = 2;
    uint16_t datosSerializados = htons(datosEnviar);
    skt.sendall(&datosSerializados, bytes_enviar, &was_closed);
    if (was_closed) {
        sigo_vivo = false;
    }
}


void ServerProtocol::enviar_mensaje_broadcast() {

    BroadcastMessage ultimo_mensaje_broadcast = cola_cliente.pop();


    if (ultimo_mensaje_broadcast.obtener_codigo_mensaje() == CODIGO_JUGADORES) {

        uint8_t numero_jugadores_a_enviar = ultimo_mensaje_broadcast.obtener_cantidad_jugadores();

        enviar_datos_jugador(CODIGO_JUGADORES);
        enviar_datos_jugador(numero_jugadores_a_enviar);

    } else if (ultimo_mensaje_broadcast.obtener_codigo_mensaje() == CODIGO_MENSAJES) {

        enviar_datos_jugador(CODIGO_MENSAJES);
        std::string mensaje_chat = ultimo_mensaje_broadcast.obtener_mensaje_broadcast();
        uint16_t tamanio_mensaje = static_cast<uint16_t>(mensaje_chat.size());
        enviar_tamanio_mensaje(tamanio_mensaje);
        enviar_mensaje_jugador(tamanio_mensaje, mensaje_chat);
    }
}


bool ServerProtocol::sigue_vivo() { return sigo_vivo; }


void ServerProtocol::cerrar_conexion() {


    skt.shutdown(2);
    skt.close();
}


ServerProtocol::~ServerProtocol() {}
