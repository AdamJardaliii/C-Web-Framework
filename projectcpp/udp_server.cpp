#include "udp_server.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <thread>

UDPServer::UDPServer(int port) : port(port) {
    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket == -1) {
        std::cerr << "Error: Could not create socket\n";
    }

    // Bind socket to port
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Could not bind to port " << port << "\n";
    }
}

UDPServer::~UDPServer() {
    close(serverSocket);
}

void UDPServer::handleClient() {
    while (true) {
        char buffer[1024];
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        // Receive message from client
        ssize_t bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (bytesReceived == -1) {
            std::cerr << "Error: Failed to receive message from client\n";
            continue;
        }

        // Print client's address and port
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
        std::cout << "Received message from " << clientIP << ":" << ntohs(clientAddr.sin_port) << "\n";

        // Process message (here you can add your own logic)
        std::string message(buffer, bytesReceived);
        std::cout << "Message: " << message << "\n";

        // Send response back to client
        std::string response = "Server received your message: " + message;
        sendto(serverSocket, response.c_str(), response.size(), 0, (struct sockaddr *)&clientAddr, clientAddrLen);
    }
}

void UDPServer::start() {
    std::cout << "UDP server is running on port " << port << "\n";

    // Start handling clients in a separate thread
    std::thread clientHandler(&UDPServer::handleClient, this);
    clientHandler.detach(); // Detach the thread to run independently
}
