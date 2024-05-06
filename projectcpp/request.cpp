// request.cpp
#include <sstream>
#include <map>
#include <iostream>

#include "request.h"
#include "json.hpp"


using json = nlohmann::json; // Alias for convenience

using namespace std;

vector<string> methods = {"GET", "POST", "PUT", "DELETE", "HEAD", "PATCH"};

Request::Request(const std::string& httpRequest) {
    // Extract method
    for (const auto& m : methods) {
        if (httpRequest.find(m) == 0) {
            method = m;
            break;
        }
    }

    // Extract path
    size_t pathStart = httpRequest.find(' ') + 1;
    size_t pathEnd = httpRequest.find(' ', pathStart);
    path = httpRequest.substr(pathStart, pathEnd - pathStart);

    size_t bodyStart = httpRequest.find("{");

    if (bodyStart != std::string::npos) {
        std::string bodyStr = httpRequest.substr(bodyStart);
        body = parseJsonFromBody(bodyStr);
    }
}

std::string Request::getMethod() const {
    return method;
}

void Request::setMethod(const std::string& method) {
    this->method = method;
}

std::string Request::getPath() const {
    return path;
}

std::map<std::string, std::string> Request::getBody() const{
    return body;
 }

void Request::setPath(const std::string& path) {
    this->path = path;
}

std::map<std::string, std::string> Request::parseJsonFromBody(const std::string& body1) {
    std::map<std::string, std::string> jsonMap;

    try {
        json j = json::parse(body1);

        for (auto it = j.begin(); it != j.end(); ++it) {
            jsonMap[it.key()] = it.value().dump();
        }

    } catch (const std::exception& e) {
        std::cout << "Error parsing JSON: " << e.what() << std::endl;
    }

    return jsonMap;
}

void Request::toString() const{
    cout << "START\n";
    cout << "Path: " << path << '\n';
    cout << "Method: " << method << '\n';
    cout << "Body: \n";

    for (const auto& pair : body) {
            std::cout << pair.first << ": " << pair.second << std::endl;
    }
    cout << "END\n";
}
