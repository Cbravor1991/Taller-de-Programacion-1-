// Copyright 2023 cbravor@fi.uba.ar
#include "server_broadcast_message.h"

#include <iostream>
#define CODIGO_JUGADORES 0X06
#define CODIGO_MENSAJE 0X09

BroadcastMessage::BroadcastMessage() {
    codigo_mensaje= 0x00;
    numero_jugadores = 0x00;
}

void BroadcastMessage::cargar_codigo(const uint8_t& codigo_mensaje_recibido) {
  codigo_mensaje= codigo_mensaje_recibido;

}

void BroadcastMessage::cargar_numero_jugador_recibido(const uint8_t& numero_jugadores_recibidos) {
   numero_jugadores = numero_jugadores_recibidos;
}

void BroadcastMessage::cargar_mesaje_recibido(const std::string& mensaje_recibido) {
  
     mensaje_broadcast = mensaje_recibido;
}


 uint8_t BroadcastMessage:: obtener_cantidad_jugadores(){
    return numero_jugadores;
}

   std::string BroadcastMessage:: obtener_mensaje_broadcast(){
    return mensaje_broadcast;
}

  uint8_t BroadcastMessage:: obtener_codigo_mensaje(){
    return codigo_mensaje;
}

void BroadcastMessage::imprimir_mensaje() {
  std::string mensaje_imprimir;
    if (codigo_mensaje == CODIGO_JUGADORES) {
        mensaje_imprimir =
                "Jugadores " + std::to_string(numero_jugadores) + 
                ", esperando al resto de tus amigos...";
                    std::cout << mensaje_imprimir << '\n';
    }

    if (codigo_mensaje == CODIGO_MENSAJE) {
     
        mensaje_imprimir = mensaje_broadcast;
           std::cout << mensaje_imprimir << '\n';
    }

}



