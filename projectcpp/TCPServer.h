#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <atomic>
#include <vector>
#include <thread>

class TCPServer {
public:
    TCPServer();
    ~TCPServer();

    bool start(int port);
    void stop();

private:
    std::atomic_bool stop_;
    int serverSocket_;
    std::vector<std::thread> threads_;

    void handleClient(int clientSocket);
};

#endif // TCP_SERVER_H
