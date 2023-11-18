// Copyright 2023 cbravor@fi.uba.ar

#include "server_game.h"

#include <iostream>
#include <sstream>
#include <vector>

#include <netinet/in.h>
#define CODIGO_JUGADORES 0X06

Game::Game(Queue<BroadcastMessage>& cola_jugador, Monitor& monitor):
        cola_jugador(cola_jugador), monitor(monitor) {}


bool Game::unir_jugador_a_partida() {
    std::lock_guard<std::mutex> lck(mutex_game);
    monitor.unir_jugador_partida(cola_jugador);
    BroadcastMessage broadcast;
    broadcast.cargar_codigo(CODIGO_JUGADORES);
    broadcast.cargar_numero_jugador_recibido(monitor.obtener_jugadores_activos_partida());
    ingresar_mensaje_broadcast(broadcast);
    return true;
}


int Game::obtener_cantidad_jugadores_activos() {
    return monitor.obtener_jugadores_activos_partida();
}

void Game::eliminar_jugador_partida() { monitor.eliminar_jugador_de_partida(cola_jugador); }


void Game::ingresar_mensaje_broadcast(BroadcastMessage& broadcast) {

    broadcast.imprimir_mensaje();
    monitor.ingresar_mensaje_broadcast(broadcast);
}
