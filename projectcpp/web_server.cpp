#include "web_server.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring> // Include for std::string
#include <fstream>
#include <streambuf>
#include <unordered_map>
#include <sstream>
#include <map>

#include "utils.h"
#include "request.h"
#include "routes.h"

using namespace std;


WebServer::WebServer() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error: Could not create socket\n";
    }
}

WebServer::~WebServer() {
    cout <<"Closed";
    close();
}

bool WebServer::bind(int port) {
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (::bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) == -1) {
        std::cerr << "Error: Could not bind to port " << port << "\n";
        return false; // Return false indicating failure
    }

    cout << "Running: 127.0.0.1:" << port << '\n';

    return true;
}


void WebServer::close() {
    if (serverSocket != -1) {
        ::close(serverSocket);
        serverSocket = -1;
    }
}

void WebServer::listen() {
    ::listen(serverSocket, 5); 
    std::cout << "Listening for connections...\n";
    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            std::cerr << "Error: Could not accept connection\n";
            ::close(clientSocket);
            break;
        }

        // Read HTTP request
        char buffer[30000];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            ::close(clientSocket); 
            continue;
        }
        buffer[bytesRead] = '\0';
        std::string httpRequest(buffer);


        cout << httpRequest << '\n';

        
        Request request(httpRequest);


        std::string method = request.getMethod(), path = request.getPath();
        std::map<std::string, std::string> body = request.getBody();

        request.toString();



        if (method == "GET") {
            std::string response = get(path,method);
            send(clientSocket, response.c_str(), response.size(), 0);
        } 

        else if (method == "POST") {

            std::string response = post(path,method);

            send(clientSocket, response.c_str(), response.size(), 0);
        }

        ::close(clientSocket);
    }
}




std::string WebServer::get(const std::string& path,const std::string& method) {
    
    Routes routes;

    std::string response;
    std::string file_name = routes.getRouteHandler(path,method);

    response = render_html(file_name,"html_folders");

    return response;
}

std::string WebServer::post(const std::string& path,const std::string& method) {
    Routes routes;
    std::string response;
    std::string file_name = routes.getRouteHandler(path,method);

    response = render_html(file_name,"html_folders");

    return response;
}

std::unordered_map<std::string, std::string> WebServer::parseHttpRequest(const std::string& httpRequest) {
    std::unordered_map<std::string, std::string> headers;

    // Split the HTTP request by newline characters
    std::istringstream ss(httpRequest);
    std::string line;
    while (std::getline(ss, line)) {
        // Split each header by the first colon (:)
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            
            // Trim leading and trailing whitespace from the key and value
            key.erase(0, key.find_first_not_of(" \t\r\n"));
            key.erase(key.find_last_not_of(" \t\r\n") + 1);
            value.erase(0, value.find_first_not_of(" \t\r\n"));
            value.erase(value.find_last_not_of(" \t\r\n") + 1);

            // Add the key-value pair to the dictionary
            headers[key] = value;
        }
    }

    return headers;
}
