#include "routes.h"
#include "statusCode.h"
#include <algorithm>
#include <iostream>    
#include <map>    
#include <unordered_map>   
std::vector<std::string> httpMethods = {"GET", "POST", "PUT", "DELETE", "HEAD", "PATCH"};

Routes::Routes() {}

Routes::Routes(const std::string& path, const std::string& htmlPath, std::vector<bool>& methods) {
    registerRoute(path, htmlPath, methods);
}

void Routes::registerRoute(const std::string& path, const std::string& htmlPath, std::vector<bool>& methods) {
    for(int i = 0; i < std::min(methods.size(), httpMethods.size()); i++){
        routes[path][httpMethods[i]] = (methods[i]?"1":"0");
    }
    routes[path]["htmlPath"] = htmlPath;
}

bool Routes::isMethodAllowed(const std::string& path, const std::string& method) {
    return routes[path][method] == "1";
}

std::string Routes::getRouteHandler(const std::string& path, const std::string& method) {
    std::cout << "path:-" << path <<"----"<<'\n';

    if(path=="/index"){
        std::cout << "path is equal to /index\n";
        std::cout << "path of index is: " << routes["/index"]["htmlPath"] << '\n';
    }
    std::cout << "method: " << routes[path][method] << '\n';
    std::cout << "html path: " << routes[path]["htmlPath"] << '\n';
    if(isMethodAllowed(path, method)){
        std::cout << "Success\n";
        return routes[path]["htmlPath"];
    }
    return "-1";
}

void Routes::toString(){
    for(auto p:routes){

        std::cout << "URL: " << p.first << '\n';

        for(auto q:p.second){
            std::cout << "type: " << q.first << " Value: " << q.second << '\n';
            
            std::cout <<"---------------------------"<< '\n';
        }
    }

    

    std::cout <<"-------------Finished--------------"<< '\n';

}
