#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <memory>
#include <atomic>
#include <utility>

class Logger {
public:
    enum class Level {
        Trace = 0,
        Debug,
        Info,
        Warn,
        Error,
        Critical,
        Off
    };

private:
    // Shared log file stream for singleton
    static std::ofstream file_;

    explicit Logger(const std::string& name = "", Level defaultLevel = Level::Info)
        : consoleEnabled_(true),
          fileEnabled_(false),
          consoleLevel_(defaultLevel),
          fileLevel_(defaultLevel) {}


public:
    // Singleton accessor
    static Logger& instance() {
        static Logger loggerInstance;
        return loggerInstance;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Forward declaration of the RAII stream proxy
    class LogStream;

    // Sink control
    void enableConsole(bool enabled) {
        consoleEnabled_ = enabled;
    }

    void enableFile(bool enabled) {
        fileEnabled_ = enabled && file_.is_open();
    }

    bool setLogFile(const std::string& path, bool append = true) {
        fileEnabled_ = false;
        if (path.empty()) return true;

        std::ios_base::openmode mode = std::ios::out | (append ? std::ios::app : std::ios::trunc);
        file_.close();
        file_.open(path, mode);
        if (!file_.is_open()) {
            return false;
        }
        fileEnabled_ = true;
        return true;
    }

    // Per-sink levels
    void setConsoleLevel(Level lvl) { consoleLevel_.store(lvl, std::memory_order_relaxed); }
    void setFileLevel(Level lvl)    { fileLevel_.store(lvl, std::memory_order_relaxed); }
    Level consoleLevel() const      { return consoleLevel_.load(std::memory_order_relaxed); }
    Level fileLevel() const         { return fileLevel_.load(std::memory_order_relaxed); }
    void setAllLevels(Level lvl)    { setConsoleLevel(lvl); setFileLevel(lvl); }

    // Stream-style entry points
    LogStream trace();
    LogStream debug();
    LogStream info();
    LogStream warn();
    LogStream error();
    LogStream critical();

    // For advanced cases if needed
    LogStream log(Level level);

private:
    static std::string nowTimestamp();
    static const char* levelName(Level lvl);
    void emit(Level lvl, const std::string& message);

public:
    // RAII stream proxy that collects with operator<< and emits on destruction
    class LogStream {

    public:
        LogStream(Logger& logger, Level level)
            : logger_(logger), level_(level), enabled_(true) {}

        // Movable, not copyable
        LogStream(const LogStream&) = delete;
        LogStream& operator=(const LogStream&) = delete;

        LogStream(LogStream&& other) noexcept
            : logger_(other.logger_), level_(other.level_), enabled_(other.enabled_) {
            buffer_ << other.buffer_.str();
            other.enabled_ = false; // prevent double emission
        }
        LogStream& operator=(LogStream&& other) noexcept {
            if (this != &other) {
                flushIfNeeded();
                // logger_ is a reference and cannot be assigned after construction
                level_   = other.level_;
                enabled_ = other.enabled_;
                buffer_.str(std::string());
                buffer_.clear();
                buffer_ << other.buffer_.str();
                other.enabled_ = false;
            }
            return *this;
        }

        ~LogStream() {
            flushIfNeeded();
        }

        template <typename T>
        LogStream& operator<<(const T& value) {
            if (enabled_) {
                buffer_ << value;
            }
            return *this;
        }

        // Support manipulators like std::endl
        LogStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
            if (enabled_) {
                manip(buffer_);
            }
            return *this;
        }

        // Explicit flush (optional)
        void flush() { flushIfNeeded(); }

    private:
        void flushIfNeeded() {
            if (enabled_) {
                enabled_ = false;
                logger_.emit(level_, buffer_.str());
            }
        }

        Logger& logger_;
        Level level_;
        bool enabled_;
        std::ostringstream buffer_;
    };

private:
    // Sinks and config
    bool consoleEnabled_;
    bool fileEnabled_;
    std::atomic<Level> consoleLevel_;
    std::atomic<Level> fileLevel_;
        // Removed per-instance file_ member; use shared_file_ only
    // Removed unused mutex_
};

// LogStream factories
inline Logger::LogStream Logger::trace()    { return LogStream(*this, Level::Trace); }
inline Logger::LogStream Logger::debug()    { return LogStream(*this, Level::Debug); }
inline Logger::LogStream Logger::info()     { return LogStream(*this, Level::Info); }
inline Logger::LogStream Logger::warn()     { return LogStream(*this, Level::Warn); }
inline Logger::LogStream Logger::error()    { return LogStream(*this, Level::Error); }
inline Logger::LogStream Logger::critical() { return LogStream(*this, Level::Critical); }
inline Logger::LogStream Logger::log(Logger::Level level) { return LogStream(*this, level); }
