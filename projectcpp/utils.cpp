#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring> // Include for std::string
#include <fstream>
#include <streambuf>

#include "utils.h"


using namespace std;
 

std::string parse_html(string htmlContent,bool valid){

	std::string response;

	if(valid){
        response += "HTTP/1.1 201 Accapted\r\n"; // Corrected line
        
	}

	else{
		response += "HTTP/1.1 404 Not Found\r\n";
		// esponse += "HTTP/1.1 201 Accapted\r\n";


	}

	response += "Content-Type: text/html\r\n";
    response += "Content-Length: " + std::to_string(htmlContent.size()) + "\r\n\r\n";
    response += htmlContent;

    return response;

}


std::string render_html(std::string fileName, std::string dir) {
    bool valid = false;
    string html_file_path = dir + "/" + fileName; 
    
    std::ifstream file(html_file_path);

    if (file.is_open()) {
        valid = true;
        std::string htmlContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close(); // Close the file
        return parse_html(htmlContent, valid);
    } else {
        html_file_path = "default_html/not_found.html";
        std::ifstream default_file(html_file_path);
        if (default_file.is_open()) {
            std::string htmlContent((std::istreambuf_iterator<char>(default_file)), std::istreambuf_iterator<char>());
            default_file.close(); // Close the file
            return parse_html(htmlContent, valid);
        } else {
            return "HTTP/1.1 404 Not Found\r\n\r\n<html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1></body></html>";
        }
    }
}

