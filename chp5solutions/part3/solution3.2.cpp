#include <iostream>
#include <fstream>
#include <string>

// Abstract base class
struct Logger {
    virtual ~Logger() = default;
    virtual void log(const std::string& message) const = 0;

    // Convenience function
    virtual void log_error(const std::string& message) const {
        log("ERROR: " + message);
    }
};

// ConsoleLogger: logs to standard output
struct ConsoleLogger : Logger {
    void log(const std::string& message) const override {
        std::cout << "[Console] " << message << "\n";
    }
};

// FileLogger: logs to a file
struct FileLogger : Logger {
    std::string filename;

    FileLogger(const std::string& file) : filename(file) {}

    void log(const std::string& message) const override {
        std::ofstream out(filename, std::ios::app);
        if (out) {
            out << "[File] " << message << "\n";
        }
    }
};

// SilentLogger: does nothing (useful for testing)
struct SilentLogger : Logger {
    void log(const std::string& /*message*/) const override {
        // Intentionally does nothing
    }
};