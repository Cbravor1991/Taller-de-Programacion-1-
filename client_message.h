// Copyright 2023 cbravor@fi.uba.ar
#ifndef CLIENT_MESSAGE_H_
#define CLIENT_MESSAGE_H_

#include <map>
#include <string>
#include <vector>

class Message {
private:
    std::string mensaje_broadcast;

public:
    Message();

    /*Carga el codigo que indica el
     *tipo de mensaje y el mensaje
     *obtenido desde el broadcast
     */
    void cargar_mensaje(const int& codigo_mensaje, const std::string& mensaje_obtenido);

    /*Imprime el mensaje
     *según los datos ingresados
     */
    void imprimir_mensaje();


    /*
     * Deshabilitamos copias
     */
    Message(const Message&) = delete;
    Message& operator=(const Message&) = delete;
};

#endif  // CLIENT_MESSAGE_H_
