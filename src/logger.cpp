#include "logger.hpp"

Logger* Logger::s_instance = 0;

Logger& Logger::instance() {
    // Initialize the single logger instance if uninitialized.
    if (Logger::s_instance == nullptr) {
        Logger::s_instance = new Logger();
    }

    return *Logger::s_instance;
}

void Logger::debug(const std::string& msg) {
    std::cout << "[DEBUG] " << msg << std::endl;
}

void Logger::error(const std::string& msg) {
	std::cout << "[ERROR] " << msg << std::endl;
}
