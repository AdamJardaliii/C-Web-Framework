#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <string>

class UDPServer {
public:
    UDPServer(int port);
    ~UDPServer();

    void start();

private:
    int serverSocket;
    int port;

    void handleClient();
};

#endif // UDP_SERVER_H
