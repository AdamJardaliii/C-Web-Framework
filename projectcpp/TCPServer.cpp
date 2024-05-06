#include "TCPServer.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

TCPServer::TCPServer() : stop_(false), serverSocket_(-1) {}

TCPServer::~TCPServer() {
    stop();
}

bool TCPServer::start(int port) {
    // Create a TCP socket
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_ == -1) {
        std::cerr << "Error: Could not create socket\n";
        return false;
    }

    // Bind the socket to an address and port
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if (bind(serverSocket_, (struct sockaddr *)&address, sizeof(address)) == -1) {
        std::cerr << "Error: Could not bind to port " << port << "\n";
        close(serverSocket_);
        return false;
    }

    // Listen for incoming connections
    if (listen(serverSocket_, 5) == -1) {
        std::cerr << "Error: Could not listen on socket\n";
        close(serverSocket_);
        return false;
    }

    std::cout << "Server started. Listening for connections on port " << port << "\n";

    // Accept and handle incoming connections in separate threads
    while (!stop_) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket_, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            std::cerr << "Error: Could not accept connection\n";
            continue;
        }

        threads_.emplace_back([this, clientSocket]() {
            handleClient(clientSocket);
        });
    }

    // Wait for all threads to finish
    for (auto& thread : threads_) {
        thread.join();
    }

    return true;
}

void TCPServer::stop() {
    if (serverSocket_ != -1) {
        stop_ = true;
        close(serverSocket_);
        serverSocket_ = -1;
    }
}

void TCPServer::handleClient(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;

    // Receive data from client
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
        // Echo back to the client
        send(clientSocket, buffer, bytesRead, 0);
    }

    // Close the socket when done
    close(clientSocket);
}
