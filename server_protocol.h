// Copyright 2023 cbravor@fi.uba.ar

#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <atomic>
#include <string>
#include <vector>

#include "common_socket.h"
#include "server_broadcast_message.h"
#include "server_game.h"


class ServerProtocol {
private:
    Socket skt;
    Game& game;
    std::atomic<bool> sigo_vivo{true};
    Queue<BroadcastMessage>& cola_cliente;


    /*Recibe el tamanio del mensaje
     *que va a recibir despues,
     *el dato que recibira es de dos bytes
     */
    uint16_t recibir_tamanio_mensaje();

    /*Recibe un dato determinado
     * proveniente del jugador,
     * el mismo es de un byte
     * */
    uint8_t recibir_dato_jugador();

    /*Recibe el mensaje de chat del jugador,
     * el mismo varia segun el tamanio
     * que se le indique
     * */
    std::string recibir_mensaje_chat(const int& tamanioString);

    /*Verifica el estado del socket y
     * en caso de estar cerrado le indica
     * al servidro que no esta vivo
     * */
    void verificar_estado_socket(bool was_closed);

    /*Envia el tamanio del mensaje que se va
     *a enviar al jugador, este dato
     *es de 2 bytes
     */
    void enviar_tamanio_mensaje(const uint16_t& datosEnviar);

    /*Envia un mensaje al
     *jugador cuyo tamanio
     * depende de la longitud dada
     **/

    void enviar_mensaje_jugador(const uint16_t& longitudString, const std::string& mensaje);

    /*envia determinados datos al
     * jugador, los mismos son
     * de un byte*/
    void enviar_datos_jugador(const uint8_t& datosEnviar);


public:
    ServerProtocol(Socket skt_cliente, Game& game, Queue<BroadcastMessage>& cola_cliente);


    /*Obtiene la informacion que quiere
     * transmitir de la cola del jugador, que se encuantra en
     *BroadcastMessague, segun el tipo de informacion obtenida
     * (si es un numero de jugador en la sala o si es un mensaje
     *que envio un jugador por chat),
     * prepara los datos y los envia
     * */
    void enviar_mensaje_broadcast();

    /*Recibe un mensaje proveniente
     * del jugador, en un comienzo
     *recibe el dato que indica que va a
     * recibir un mensaje de chat, prepara
     *la informacion que se desea broadcastear utilizando broadcastMessage
     *y la ingresa a las colas de los jugadores activos  llamando a game
     */
    BroadcastMessage recibir_mensaje_jugador();

    /*
     * Retorna el estado del server
     */
    bool sigue_vivo();

    /*
     * Realiza un shutdown del socket y luego lo cierra
     */


    void cerrar_conexion();


    /*
     *
     */
    ~ServerProtocol();

    /*
     * Deshabilitamos copias
     */
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;
};

#endif  // SERVER_PROTOCOLO_H_
