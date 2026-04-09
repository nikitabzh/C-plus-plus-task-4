#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <mutex>

enum class LogLevel { INFO, WARNING, ERR };

class Logger {
private:
    std::ofstream logFile;
    std::mutex mtx;
    Logger() { logFile.open("app_activity.log", std::ios::app); }
    ~Logger() { if (logFile.is_open()) logFile.close(); }
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!logFile.is_open()) return;

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        struct tm timeinfo;
        localtime_s(&timeinfo, &in_time_t);

        std::stringstream ss;
        ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");

        std::string levelStr = (level == LogLevel::INFO) ? "[INFO] " : (level == LogLevel::WARNING ? "[WARN] " : "[ERR ] ");
        logFile << "[" << ss.str() << "] " << levelStr << message << std::endl;
    }
};

#define LOG_INFO(msg) Logger::getInstance().log(LogLevel::INFO, msg)
#define LOG_ERR(msg) Logger::getInstance().log(LogLevel::ERR, msg)