// Copyright 2023 cbarvor@fi.uba.ar

#include "server_server.h"

#include "server_acceptorthread.h"

Server::Server(const char* servname): servname(servname) {}

void Server::run() {
    AcceptorThread thread_acceptador(servname);
    thread_acceptador.start();
    while (std::cin.get() != 'q') {}
    thread_acceptador.stop();
    thread_acceptador.join();
}
