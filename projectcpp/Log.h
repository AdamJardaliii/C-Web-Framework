// Log.h
#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Log {
public:
    Log(const std::string& logFile = "log.txt");

    void log(const std::string& message);

private:
    std::ofstream logFile;
    std::string = "log.txt";
};

#endif // LOG_H
