// Copyright 2023 cbravor@fi.uba.ar

#ifndef SERVER_CLIENT_RECEIVER_H_
#define SERVER_CLIENT_RECEIVER_H_


#include <atomic>

#include "server_game.h"
#include "server_protocol.h"
#include "server_thread.h"

class ClientReceiver: public Thread {
private:
    ServerProtocol& serverProtocol;
    Game& game;
    std::atomic<bool> esta_vivo{true};
    std::mutex mutex_ingreso_datos_broadcast;


public:
    ClientReceiver(ServerProtocol& ServerProtocol, Game& game);

    /*
     * Inicia el hilo recibidor del cliente mientras
     * este vivo recibr el mensaje proveniente del cliente
     * que corresponde al hilo. Si detecta que la conexion
     *  con el cliente se cerro elimina al jugador
     * de la partida, en ingresa los datos a las colas de
     *  los jugadores restantes
     * transmitiendo la nueva cantidad de jugadores activos
     *  En caso de seguir vivo y que se produzca una excepcion la
     * catchea e informa el error.
     */
    void run() override;

    /*
     * Indica con un true o flase si el hilo Recibidor esta vivo
     */
    bool is_alive() const override;

    /*
     * Detiene el hilo recividor indicando su muerte con un false
     * cambia la variable esta_vivo del hilo
     */
    void stop() override;

    /*
     * Deshabilitamos copias
     */
    ClientReceiver(const ClientReceiver&) = delete;
    ClientReceiver& operator=(const ClientReceiver&) = delete;
};


#endif  // SERVER_CLIENTE_RECIBIDOR_H_
