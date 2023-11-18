// Copyright 2023 cbravor@fi.uba.ar

#include <iostream>
#include <string>
#include <vector>

#include "server_server.h"

int main(int argc, char* argv[]) {
    try {
        if (argc == 2) {

            Server server(argv[1]);
            server.run();
            return 0;
        } else {
            std::cerr << "Bad program call. Expected " << argv[0] << "<servername>\n";
            return -1;
        }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and "
                     "an unknown exception was caught.\n";
        return -1;
    }
}
