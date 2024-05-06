// sessions.h

#ifndef SESSIONS_H
#define SESSIONS_H

#include <unordered_map>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <sys/socket.h>

class Session {
private:
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> sessions;

    std::string generateSessionID();

public:
    Session();

    std::string getSessionID(const std::unordered_map<std::string, std::string>& headers);

    void setSessionID(int clientSocket, const std::string& sessionID);

    std::unordered_map<std::string, std::string>& getUserData(const std::string& sessionID);
};

#endif // SESSIONS_H
