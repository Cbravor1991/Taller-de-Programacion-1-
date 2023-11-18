// Copyright 2023 cbravor@fi.uba.ar

#ifndef SERVER_MONITOR_H_
#define SERVER_MONITOR_H_

#include <string>
#include <vector>

#include "server_broadcast_message.h"
#include "server_queue.h"

class Monitor {
private:
    std::vector<std::reference_wrapper<Queue<BroadcastMessage>>> jugadores_partida;
    std::mutex mutex_partida;
    int jugadores = 0;

public:
    Monitor();

    /*
     * Ingresa al vector de colas de  jugadores_partida
     * la cola recibida por parametro de esta manera une el jugador a la partida.
     */
    void unir_jugador_partida(Queue<BroadcastMessage>& queue);

    /*
     * Realiza una itaracion por las colas de lo jugadores en el vector, donde se encuentran la
     * mismas e ingresa el mensaje que se debe braodcastear, si la cola esta cerrada se elimina.
     */
    void ingresar_mensaje_broadcast(const BroadcastMessage& broadcast);
    /*
     * Devuelve los jugadores que se encuentran activos en la partida
     *
     */
    int obtener_jugadores_activos_partida();

    /*
     * Elimina a un jugador de la partida, elimina la cola de mensajes del jugador, del vector
     * jugadores partida.
     */
    void eliminar_jugador_de_partida(Queue<BroadcastMessage>& cola_jugador);


    /*
     * Deshabilitamos copias
     */
    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;
};
#endif  // SERVER_MONITOR
