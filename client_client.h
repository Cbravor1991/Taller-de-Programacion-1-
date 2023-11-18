// Copyright 2023 cbravor@fi.uba.ar

#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "client_message.h"
#include "client_protocol.h"


class Client {
private:
    ClientProtocol clientProtocol;
    Message message;


    /*Indica que se debe obtener
     * una cierta cantidad de
     *mensajes del broadcast
     */

    void leer_mensajes_broadcast(const std::string& cantidad_mensajes);


public:
    Client(const char* hostname, const char* servname);

    /*
     * Inicia el cliente y se ejecuta un loop
     * que segun la entrada ingresada realizara una accion, la
     * misma puede ser chat lee el mensaje ingresado
     * por consola, Read N obtiene N mensajes
     * provenientes del broadcast
     * y Exit finaliza el cliente
     */
    int run();


    /*
     * Deshabilitamos copias
     */
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
};

#endif  // CLIENT_CLIENTE_H_
