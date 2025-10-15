#include <iostream>
#include <fstream>
#include <string>

// Abstract base class for logging
struct Logger {
    virtual ~Logger() = default;

    // Pure virtual function to be implemented by derived loggers
    virtual void log(const std::string& message) const = 0;

    // Convenience function for logging errors
    virtual void log_error(const std::string& message) const {
        log("ERROR: " + message);
    }
};