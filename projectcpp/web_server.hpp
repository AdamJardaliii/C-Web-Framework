#ifndef WEB_SERVER_HPP
#define WEB_SERVER_HPP

#include <string>
#include <map>
#include "routes.h"

class WebServer {
public:
    WebServer();
    ~WebServer();

    bool bind(int port);
    void close();
    void listen();
    std::string get(const std::string& path,const std::string& method);
    std::string post(const std::string& path,const std::string& method);
    Routes routes;


    // Methods to register and get a route
    // void registerRoute(const std::string& path, const std::string& handler);
    // std::string getRouteHandler(const std::string& path);

    std::unordered_map<std::string, std::string> parseHttpRequest(const std::string& httpRequest);

private:
    int serverSocket;
    // std::map<std::string, std::string> routes; // Map to store routes and their handlers
};

#endif // WEB_SERVER_HPP
