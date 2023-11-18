// Copyright 2023 cbravor@fi.uba.ar

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "client_client.h"

int main(int argc, char* argv[]) {
    try {
        if (argc == 3) {
            const std::string hostname = std::string(argv[1]);
            const std::string servname = std::string(argv[2]);
            Client client(argv[1], argv[2]);
            client.run();
            return 0;
        } else {
            std::cerr << "Bad program call. Expected "
                         " <hostname> <servername>\n";
            return -1;
        }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an"
                     " unknown exception was caught.\n";
        return -1;
    }
}
