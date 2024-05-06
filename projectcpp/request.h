// request.h
#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <vector>
#include <map>

class Request {
private:
    std::string method;
    std::string path;
    std::map<std::string, std::string> body;
    std::map<std::string, std::string> parseJsonFromBody(const std::string& body);



public:
    Request(const std::string& httpRequest);
    std::string getMethod() const;
    void setMethod(const std::string& method);
    std::string getPath() const;
    void setPath(const std::string& path);
    std::map<std::string, std::string> getBody() const;
    void setBody(const std::map<std::string, std::string>& body);
    void toString() const;


};

#endif // REQUEST_H
