// Copyright 2023 cbravor@fi.uba.ar

#include "server_player.h"

#include <iostream>
#include <sstream>
#include <utility>


Player::Player(Socket skt_player, Monitor& monitor):
        cola_jugador(50),
        game(cola_jugador, monitor),
        serverProtocol(std::move(skt_player), game, cola_jugador) {
    game.unir_jugador_a_partida();
}

void Player::run() {

    ClientReceiver thread_recibidor(serverProtocol, game);
    thread_recibidor.start();
    enviar_mensaje();
    thread_recibidor.join();
}

void Player::enviar_mensaje() {
    try {
        while (esta_vivo) {
            serverProtocol.enviar_mensaje_broadcast();
            esta_vivo = serverProtocol.sigue_vivo();
        }


    } catch (const std::exception& err) {
        if (esta_vivo) {
            std::cerr << "Unexpected exception: " << err.what() << "\n";
        }
    }
}

bool Player::is_alive() const { return esta_vivo; }

void Player::stop() {
    cola_jugador.close();
    esta_vivo = false;
    serverProtocol.cerrar_conexion();
}
