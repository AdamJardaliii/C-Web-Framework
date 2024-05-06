// Log.cpp
#include "Log.h"


Log::Log(const std::string& logFile) {
    logFile.open(logFile, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {        std::cerr << "Error: Could not open log file: " << logFile << std::endl;
    }
}

void Log::log(const std::string& message) {
    std::time_t currentTime = std::time(nullptr);
    std::string timeStr = std::ctime(&currentTime);
    timeStr.pop_back(); // Remove newline character from ctime output

    std::cout << "[" << timeStr << "] " << message << std::endl;

    if (logFile.is_open()) {
        logFile << "[" << timeStr << "] " << message << std::endl;
        logFile.flush();
    }
}
