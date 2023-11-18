// Copyright 2023 cbravor@fi.uba.ar

#ifndef SERVER_GAME_H_
#define SERVER_GAME_H_

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "server_broadcast_message.h"
#include "server_monitor.h"

class Game {
private:
    Queue<BroadcastMessage>& cola_jugador;
    std::uint32_t codigo_partida = -1;
    Monitor& monitor;
    int numero_jugadores = 0;
    std::mutex mutex_game;


public:
    Game(Queue<BroadcastMessage>& cola_jugador, Monitor& monitor);

    /*Une el jugador a la partida ingresando la cola del jugador recibida a traves de monitor.
    * Genera lo que se quiere transmitir con BroadcaMessage, e ingresa esa información a las colas
    de los jugadores de la partid a usando el monitor  */
    bool unir_jugador_a_partida();

    /*Ingresa los datos que se quieren transmitir a las colas de los jugadores
     * de la partida usando el monitor
     *A traves de broadcastMessage imprime el mensaje que corresponde segun los datos que son
     *ingresados en las colas de los jugadores de la partida
     */
    void ingresar_mensaje_broadcast(BroadcastMessage& broadcast);

    /*Obtiene a traves del monitor
     * la contidad de colas de
     * los jugadores activos*/
    int obtener_cantidad_jugadores_activos();

    /*Elimina el jugador de la partida,
     * eliminando la cola del jugador del vector de
     *  jugadores de partida llamando a monitor
     */
    void eliminar_jugador_partida();

    /*
     * Deshabilitamos copias
     */
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};

#endif  // SERVER_Game_H_
