// Copyright 2023 cbravor@fi.uba.ar

#include <algorithm>
#include <utility>
#include <string>
#include "server_acceptorthread.h"

#include "server_player.h"

AcceptorThread::AcceptorThread(const char * servname) :
        skt_escuchador(Socket(servname)),
        monitor()
     {}




void AcceptorThread::run() { try {
    while (esta_vivo) {
      
            Socket acceptado = skt_escuchador.accept();
            iniciar_hilo_manejador_jugador(std::move(acceptado),
                                  monitor);
            eliminar_jugadores_muertos();
          
        }
        eliminar_todos_jugadores();
    } catch (const std::exception& err) {
 if (esta_vivo) {
            std::cerr << "Unexpected : " << err.what() << "\n";
        }
        eliminar_todos_jugadores();
        esta_vivo = false;
        }
}


void AcceptorThread::iniciar_hilo_manejador_jugador(
                Socket&& skt_cliente,
                Monitor &monitor) {
    Thread *t = new Player(std::move(skt_cliente),
            monitor);
    threads.push_back(t);
    t -> start();
}

void AcceptorThread::eliminar_jugadores_muertos() {
   
  auto terminado = [](Thread* thread) {
        if (!thread->is_alive()) {
     
            thread->stop();
            thread->join();
            delete thread;
            return true;
        }
        return false;
    };
    threads.erase(std::remove_if(threads.begin(),
                                 threads.end(), terminado), threads.end());
}

void AcceptorThread::eliminar_todos_jugadores() {

     for (Thread* jugadores : threads) {
        
    
        jugadores->stop();
        jugadores->join();
            
        delete jugadores;
 
    
    threads.clear();}
}

void AcceptorThread::stop() {
  
    esta_vivo = false;
    skt_escuchador.shutdown(2);
    skt_escuchador.close();
}

bool AcceptorThread:: is_alive() const {
         return esta_vivo;}
