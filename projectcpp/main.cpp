#include "web_server.hpp"
#include <iostream>
#include <vector>
#include <cstdlib> // Include for std::atoi

int main(int argc, char *argv[]) {
    WebServer server;

    // Check if a port number is provided as a command-line argument
    int port = 8080; // Default port number
    if (argc >= 2) {
        port = std::atoi(argv[1]); // Convert command-line argument to integer
    }

    if(server.bind(port)) {
        std::vector<bool> a = {true,true};
        server.routes.registerRoute("/index", "index.html", a);
                
        server.routes.toString();       
        server.listen();
    }

    return 0;
}
