#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <sstream>

enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
public:
    Logger() = delete;
    
    using LogListener = std::function<void(LogLevel, const std::string&)>;
    
    static void addListener(LogListener listener) {
        listeners_.push_back(listener);
    }

    template <typename... Args>
    static void info(Args&&... args) {
        logRaw(LogLevel::Info, buildString(std::forward<Args>(args)...));
    }

    template <typename... Args>
    static void warn(Args&&... args) {
        logRaw(LogLevel::Warning, buildString(std::forward<Args>(args)...));
    }

    template <typename... Args>
    static void error(Args&&... args) {
        logRaw(LogLevel::Error, buildString(std::forward<Args>(args)...));
    }

private:
    static inline std::vector<LogListener> listeners_;
    
    static void logRaw(LogLevel level, const std::string& message) {
        if (listeners_.empty()) {
            std::cout << message << std::endl;
            return;
        }

        for (const auto& listener : listeners_) {
            listener(level, message);
        }
    }

    template <typename... Args>
    static std::string buildString(Args&&... args) {
        std::stringstream ss;
        (ss << ... << std::forward<Args>(args));
        return ss.str();
    }
};

inline void consoleLogListener(LogLevel level, const std::string& message) {
    switch (level) {
        case LogLevel::Info:
            // Default color fo info
            std::cout << "[INFO] " << message << std::endl;
            break;
        case LogLevel::Warning:
            // Yellow for warning
            std::cout << "\033[33m" << "[WARNING] " << "\033[0m" << message << std::endl;
            break;
        case LogLevel::Error:
            // Red for error
            std::cerr << "\033[31m" << "[ERROR] " << "\033[0m" << message << std::endl;
            break;
    }
}