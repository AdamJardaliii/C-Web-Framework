#ifndef CONSUME_H
#define CONSUME_H

#include <string>

class Consume {
public:
    Consume();

    // Function to make a GET request to the specified URL
    std::string get(const std::string& url);

    // Function to make a POST request to the specified URL with the given data
    std::string post(const std::string& url, const std::string& data);

private:
    // Helper function to perform HTTP request
    std::string httpRequest(const std::string& url, const std::string& method, const std::string& data);
};

#endif // CONSUME_H
