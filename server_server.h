// Copyright 2023 cbravor@fi.uba.ar

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_


#include <string>

class Server {
private:
    const char* servname;

public:
    explicit Server(const char* servname);

    /*
     * Inicia el hilo aceptador, 
     * en caso de que se ingrese q por consola detiene el hilo
     */
    void run();

    /*
     * Deshabilitamos copias
     */
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
};

#endif  // SERVER_SERVER_H_
