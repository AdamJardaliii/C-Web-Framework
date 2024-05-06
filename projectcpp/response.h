#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>
#include <map>

class Response {
public:
    static std::string generateResponse(const std::string& body, int statusCode = 200, const std::string& contentType = "text/html", const std::map<std::string, std::string>& headers = {}, const std::string& startLine = "HTTP/1.1", const std::map<std::string, std::string>& cookies = {});
};

#endif // RESPONSE_H
