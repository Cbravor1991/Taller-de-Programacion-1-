// Copyright 2023 cbravor@fi.uba.ar

#include "server_monitor.h"

#include <algorithm>
#include <iostream>

Monitor::Monitor() {}

void Monitor::unir_jugador_partida(Queue<BroadcastMessage>& queue) {
    std::lock_guard<std::mutex> lck(mutex_partida);  // siempre
    jugadores_partida.push_back(queue);
}

void Monitor::ingresar_mensaje_broadcast(const BroadcastMessage& broadcast) {

    std::lock_guard<std::mutex> lck(mutex_partida);
    auto cola_it = jugadores_partida.begin();
    while (cola_it != jugadores_partida.end()) {
        Queue<BroadcastMessage>& cola = cola_it->get();
        try {
            cola.push(broadcast);
            ++cola_it;
        } catch (...) {
            cola_it = jugadores_partida.erase(cola_it);
        }
    }
}

int Monitor::obtener_jugadores_activos_partida() {
    std::lock_guard<std::mutex> lck(mutex_partida);
    return (jugadores_partida.size());
}


void Monitor::eliminar_jugador_de_partida(Queue<BroadcastMessage>& cola_jugador) {
    std::lock_guard<std::mutex> lck(mutex_partida);
    auto it = std::find_if(
            jugadores_partida.begin(), jugadores_partida.end(),
            [&cola_jugador](const std::reference_wrapper<Queue<BroadcastMessage>>& ref) {
                return &ref.get() == &cola_jugador;
            });
    if (it != jugadores_partida.end()) {
        jugadores_partida.erase(it);
    }
}
