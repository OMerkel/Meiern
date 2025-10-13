/**
 * @file Logger.cpp
 * @brief Implementation of the Logger class.
 *
 * This file contains the implementation of the Logger class, including
 * methods for logging messages at various levels, managing output
 * streams, and formatting log messages.
 *
 * @author Oliver Merkel
 * @date 2025-10-13
 */
#include "Logger.h"

std::ofstream Logger::file_;


/**
 * @brief Generates a timestamp string for log entries.
 * @return A string representing the current date and time with microsecond precision.
 */
std::string Logger::nowTimestamp() {
    using clock = std::chrono::system_clock;
    const auto now = clock::now();
    const auto t = clock::to_time_t(now);
    const auto us = std::chrono::duration_cast<std::chrono::microseconds>(
        now.time_since_epoch()).count() % 1000000;

    std::tm tm;
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << "." << std::setw(6) << std::setfill('0') << us;
    return oss.str();
}


/**
 * @brief Converts a log level enum to its string representation.
 * @param lvl The log level to convert.
 * @return A constant character pointer representing the log level name.
 */
const char* Logger::levelName(Level lvl) {
    switch (lvl) {
        case Level::Trace:    return "TRACE";
        case Level::Debug:    return "DEBUG";
        case Level::Info:     return "INFO";
        case Level::Warn:     return "WARN";
        case Level::Error:    return "ERROR";
        case Level::Critical: return "CRITICAL";
        default:              return "OFF";
    }
}


/**
 * @brief Emits a log message to the enabled sinks (console and/or file).
 * @param lvl The log level of the message.
 * @param message The message to log.
 */
void Logger::emit(Level lvl, const std::string& message) {
    // Fast check outside lock to avoid formatting if not needed
    bool toConsole = false;
    bool toFile = false;
    {
        toConsole = consoleEnabled_ && (lvl >= consoleLevel_.load(std::memory_order_relaxed));
        toFile    = fileEnabled_ && file_.is_open() && (lvl >= fileLevel_.load(std::memory_order_relaxed));
        if (!toConsole && !toFile) {
            return;
        }
    }

    const std::string line = "[" + nowTimestamp() + "] [" + levelName(lvl) + "] " + message;

    if (toConsole) {
        std::ostream& os = (lvl >= Level::Warn) ? static_cast<std::ostream&>(std::cerr)
                                                : static_cast<std::ostream&>(std::cout);
        os << line << std::endl;
    }
    if (toFile && file_) {
        file_ << line << std::endl;
        file_.flush();
    }
    // No return value
}
