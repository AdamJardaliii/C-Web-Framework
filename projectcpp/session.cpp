// session.cpp

#include "sessions.h"

Session::Session() {
    srand(time(nullptr));
}

std::string Session::generateSessionID() {
    std::string sessionID;
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 32; ++i) {
        sessionID += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return sessionID;
}

std::string Session::getSessionID(const std::unordered_map<std::string, std::string>& headers) {
    auto it = headers.find("Cookie");
    if (it != headers.end()) {
        std::istringstream ss(it->second);
        std::string token;
        while (std::getline(ss, token, ';')) {
            std::istringstream token_ss(token);
            std::string key, value;
            std::getline(token_ss, key, '=');
            std::getline(token_ss, value, '=');
            if (key == "SessionID") {
                return value;
            }
        }
    }
    return "";
}

void Session::setSessionID(int clientSocket, const std::string& sessionID) {
    std::string cookie = "Set-Cookie: SessionID=" + sessionID + "; Path=/\r\n";
    send(clientSocket, cookie.c_str(), cookie.size(), 0);
}

std::unordered_map<std::string, std::string>& Session::getUserData(const std::string& sessionID) {
    return sessions[sessionID];
}
