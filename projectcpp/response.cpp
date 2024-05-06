#include "response.h"

std::string Response::generateResponse(const std::string& body, int statusCode, const std::string& contentType, const std::map<std::string, std::string>& headers, const std::string& startLine, const std::map<std::string, std::string>& cookies) {
    std::string response = startLine + " " + std::to_string(statusCode) + " OK\r\n";
    
    // Add custom headers
    for (const auto& header : headers) {
        response += header.first + ": " + header.second + "\r\n";
    }
    
    response += "Content-Type: " + contentType + "\r\n";
    response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
    
    // Add cookies
    for (const auto& cookie : cookies) {
        response += "Set-Cookie: " + cookie.first + "=" + cookie.second + "\r\n";
    }
    
    response += "\r\n";
    response += body;

    return response;
}
