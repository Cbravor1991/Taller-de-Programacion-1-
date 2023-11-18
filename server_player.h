// Copyright 2023 cbravor@fi.uba.ar

#ifndef SERVER_PLAYER_H_
#define SERVER_PLAYER_H_

#include <atomic>
#include <string>
#include <vector>

#include "common_socket.h"
#include "server_client_receiver.h"
#include "server_protocol.h"
#include "server_thread.h"

class Player: public Thread {
private:
    Queue<BroadcastMessage> cola_jugador;
    Game game;
    ServerProtocol serverProtocol;
    std::atomic<bool> esta_vivo{true};

    /*Mientras el hilo este vivo envia el mensaje
    * al cliente de los mensejes que se
    encuentran ingreados en el broadcast
    **/
    void enviar_mensaje();

public:
    Player(Socket skt_jugador, Monitor& monitor);

    /*Inicia el hilo del cliente corrspondiente
     * a la rececpción de mensajes de chat
     * y jugadores y envia los mensajes
     * del broadcast al cliente*/
    void run() override;


    /*Indica si el hilo enviador (el hilo Player) esta  vivo*/
    bool is_alive() const override;


    /*Detiene el hilo y cierra la cola de jugador y
     * detiene cierra los sockets a traves de
     * cerrar_conexion de los sockets
     * */
    void stop() override;


    /*
     * Deshabilitamos copias
     */
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
};
#endif  // SERVER_PLAYER_H_
