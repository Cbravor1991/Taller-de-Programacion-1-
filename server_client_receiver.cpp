// Copyright 2023 cbravor@fi.uba.ar

#include "server_client_receiver.h"

#include <sstream>
#include <string>

#define CODIGO_JUGADORES 0X06

ClientReceiver::ClientReceiver(ServerProtocol& serverProtocol, Game& game):
        serverProtocol(serverProtocol), game(game) {}


void ClientReceiver::run() {
    try {
        while (esta_vivo) {
            std::lock_guard<std::mutex> lck(mutex_ingreso_datos_broadcast);
            BroadcastMessage broadcast = serverProtocol.recibir_mensaje_jugador();
            game.ingresar_mensaje_broadcast(broadcast);
            esta_vivo = serverProtocol.sigue_vivo();
            if (esta_vivo == false) {
                game.eliminar_jugador_partida();
                broadcast.cargar_codigo(CODIGO_JUGADORES);
                broadcast.cargar_numero_jugador_recibido(game.obtener_cantidad_jugadores_activos());
                game.ingresar_mensaje_broadcast(broadcast);
            }
        }
    } catch (const std::exception& err) {
        if (esta_vivo) {
            std::cerr << "Unexpected Exception : " << err.what() << "\n";
        }
    }
}


bool ClientReceiver::is_alive() const { return esta_vivo; }

void ClientReceiver::stop() { esta_vivo = false; }
