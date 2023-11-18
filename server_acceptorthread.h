// Copyright 2023 cbravor@fi.uba.ar

#ifndef SERVER_ACCEPTORTHREAD_H_
#define SERVER_ACCEPTORTHREAD_H_

#include <atomic>
#include <string>
#include <vector>

#include "common_socket.h"
#include "server_monitor.h"
#include "server_thread.h"

class AcceptorThread: public Thread {
private:
    Socket skt_escuchador;

    std::vector<Thread*> threads;
    Monitor monitor;
    std::atomic<bool> esta_vivo{true};

    /*
     * Crea un Thread Player (jugador) y lo inicializa.
     */
    void iniciar_hilo_manejador_jugador(Socket&& skt_cliente, Monitor& monitor);
    /*
     *Busca en el thread los jugadores muertos y los
     * detiene y libera memoria usa stop y join
     */
    void eliminar_jugadores_muertos();

    /*
     * Detiene todos los jugadores libera memoria utiliza stop y join
     */
    void eliminar_todos_jugadores();

    /*
     * Indica si el hilo AcceptorThread se encuentra vivo
     */
    bool is_alive() const override;

public:
    explicit AcceptorThread(const char* servname);

    /*
     * Es el meotodos que pone en marcha los hilos jugadores cheque en un loop si el hilo Aceptador
     * esta vivo en caso contrario detiene todos los hilos de los jugadores y libera la memoria
     */
    void run() override;

    /*
     * Detiene y cierra socket del hilo aceptador.
     */
    void stop() override;


    /*
     * Deshabilitamos copias
     */
    AcceptorThread(const AcceptorThread&) = delete;
    AcceptorThread& operator=(const AcceptorThread&) = delete;
};
#endif
