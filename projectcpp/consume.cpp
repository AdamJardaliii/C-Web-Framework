#include "consume.h"
#include <iostream>
#include <curl/curl.h>

Consume::Consume() {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);
}

std::string Consume::httpRequest(const std::string& url, const std::string& method, const std::string& data) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char* ptr, size_t size, size_t nmemb, std::string* stream) -> size_t {
            stream->append(ptr, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Error: Failed to perform HTTP request: " << curl_easy_strerror(res) << "\n";
        }

        curl_easy_cleanup(curl);
    }

    return response;
}

std::string Consume::get(const std::string& url) {
    return httpRequest(url, "GET", "");
}

std::string Consume::post(const std::string& url, const std::string& data) {
    return httpRequest(url, "POST", data);
}
