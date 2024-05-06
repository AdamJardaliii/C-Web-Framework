#ifndef ROUTES_H
#define ROUTES_H

#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <vector>

class Routes {
public:
    Routes(); // Default constructor
    Routes(const std::string& path, const std::string& htmlPath, std::vector<bool>& methods); // Constructor with route path and methods

    void registerRoute(const std::string& path, const std::string& htmlPath, std::vector<bool>& methods);
    std::string getRouteHandler(const std::string& path, const std::string& method);

    void toString();


private:
    std::unordered_map<std::string, std::map<std::string, std::string>> routes;
    std::set<std::map<std::string,std::unordered_map<std::string, std::map<std::string, std::string>>>> TreeRoute;

    bool isMethodAllowed(const std::string& path, const std::string& method);
};

#endif // ROUTES_H
