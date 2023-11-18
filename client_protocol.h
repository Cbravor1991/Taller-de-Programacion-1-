// Copyright 2023 cbravor@fi.uba.ar

#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <map>
#include <string>
#include <vector>

#include "client_message.h"
#include "common_socket.h"

class ClientProtocol {
private:
    Socket skt;
    std::map<std::string, std::uint8_t> accion;

    /*
     * Envia el tamanio del mensaje
     *que desea broadcastear,
     *se envian dos bytes con este dato
     */
    void enviar_tamanio_mensaje(const uint16_t& datosEnviar);
    /*
     * Envia el codigo del tipo de
     * informacion que se desea brodcastear,
     *se envia un byte con este dato
     */
    void enviar_codigo_mensaje(const uint8_t& datosEnviar);

    /*
     * Recibe el tamanio del mensaje
     * broadcasteado que se envia desde
     * broadcast(la cola correspondiente al jugador),
     *se reciben dos bytes con este dato
     */
    uint16_t recibir_tamanio_mensaje_broadcast();

    /*
     * Recibe el codigo del tipo
     * de informacion que se enviara
     * desde el broadcast
     * se reciben un byte con este dato
     */
    uint8_t recibir_codigo_broadcast();

    /*
     * Envia el  mensaje que desea broadcastear,
     * el tamanio del mensaje seara variable segun el
     * mensaje que se desse enviar
     */
    void enviar_mensaje(const uint16_t& longitudString, const std::string& nombre);


    /* Recibe un mensaje enviado desde el broadcast
     * el tamanio del mensaje sera variable segun el tamaño
     * del menasje que se va a recibir
     * y carga el mensaje llamando a message*/

    std::string recibir_mensaje_broadcast(const int& tamanioStringr);


public:
    ClientProtocol(const char* hostname, const char* servname);


    /*Obtiene el mensaje enviado
     *desde el broadcast segun el tipo
     *de codigo de mensaje que se envia,
     *y carga el mensaje llamando a message
     */
    void obtener_mensaje_broadcast(Message& message);


    /*
     *Envia el codigo del mensaje
     * el tamanio del mensaje y
     * el mensaje al broadcast
     */

    void enviar_mensaje_broadcast(const std::string& mensaje);

    /*
     * Cierra la conexion del socket
     *del cliente hace un shutdown
     * y luego cierra el socket
     */

    void cerrar_conexion_socket();

    ~ClientProtocol();

    /*
     * Deshabilitamos copias
     */
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;
};

#endif  // CLIENT_PROTOCOL_H_
