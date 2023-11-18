// Copyright 2023 cbravor@fi.uba.ar
#ifndef CLIENT_MESSAGE_H_
#define CLIENT_MESSAGE_H_

#include <map>
#include <string>
#include <vector>

class BroadcastMessage {
private:
    uint8_t codigo_mensaje;
    uint8_t numero_jugadores;
    std::string mensaje_broadcast;

public:
    BroadcastMessage();  // Declaración del constructor
    /*
     *obtiene la cantidad de jugadores que
     *se quieren transmitir a la cola de
     *los jugaores, de la partida
     */
    uint8_t obtener_cantidad_jugadores();
    /*
     *obtiene el  mensaje que se quieren
     * transmitir a la cola de los jugaores
     * , de la partida
     */
    std::string obtener_mensaje_broadcast();

    /*
     *carga el codigo del tipo de informacion
     * que se quiere transmitir a la cola de
     * los jugaores, de la partida
     */
    void cargar_codigo(const uint8_t& codigo_mensaje_recibido);

    /*
     *carga el numero de jugador recibido
     *que se quiere transmitir a la cola de
     *los jugaores, de la partida
     */
    void cargar_numero_jugador_recibido(const uint8_t& numero_jugadores_recibidos);

    /*
     *carga el  mensaje que se quieren
     *transmitir a la cola de los jugaores,
     * de la partida
     */
    void cargar_mesaje_recibido(const std::string& mensaje_recibido);

    /*
     *obtiene el codigo del tipo de informacion
     * que se quiere transmitir a la cola de
     * los jugaores, de la partida
     */
    uint8_t obtener_codigo_mensaje();

    /*
     *imprime el mensaje corrrspondiente
     *segun la informacion recibida
     *por parte del cliente
     */
    void imprimir_mensaje();
};

#endif  // CLIENT_MESSAGE_H_
