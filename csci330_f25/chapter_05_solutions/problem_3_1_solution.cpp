// Problem 3.1 Solution: Advanced Logging System
// Demonstrates practical polymorphism with a logging system

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

// Abstract Logger interface
struct Logger {
    virtual ~Logger() = default;
    
    // Pure virtual function - must be implemented
    virtual void log(const std::string& message) const = 0;
    
    // Virtual function with default implementation
    virtual void log_error(const std::string& message) const {
        log("ERROR: " + message);
    }
    
    virtual void log_warning(const std::string& message) const {
        log("WARNING: " + message);
    }
};

// Console logger implementation
struct ConsoleLogger : Logger {
    void log(const std::string& message) const override {
        std::cout << "[Console] " << message << "\n";
    }
};

// File logger implementation
struct FileLogger : Logger {
    std::string filename;
    
    FileLogger(const std::string& file) : filename(file) {}
    
    void log(const std::string& message) const override {
        std::ofstream out(filename, std::ios::app);
        if (out) {
            out << "[File] " << message << "\n";
        } else {
            std::cerr << "Failed to write to file: " << filename << "\n";
        }
    }
};

// Silent logger for testing/debugging
struct SilentLogger : Logger {
    void log(const std::string& message) const override {
        // Intentionally do nothing - useful for testing
        // Could count messages or store them for later retrieval
    }
};

// Multi-logger that forwards to multiple loggers
struct MultiLogger : Logger {
    std::vector<std::unique_ptr<Logger>> loggers;
    
    void add_logger(std::unique_ptr<Logger> logger) {
        loggers.push_back(std::move(logger));
    }
    
    void log(const std::string& message) const override {
        for (const auto& logger : loggers) {
            logger->log(message);
        }
    }
};

// Application class that uses logging
struct Application {
    Logger* logger;
    
    Application(Logger* log) : logger(log) {}
    
    void run() {
        logger->log("Application started");
        do_some_work();
        logger->log("Application finished");
    }
    
private:
    void do_some_work() {
        logger->log("Doing important work...");
        
        // Simulate some processing
        for (int i = 1; i <= 3; ++i) {
            logger->log("Processing step " + std::to_string(i));
        }
        
        // Simulate potential issues
        logger->log_warning("This is just a warning");
        logger->log_error("Something went wrong!");
        logger->log("Recovered from error");
    }
};

int main() {
    std::cout << "=== Console Logger Demo ===\n";
    {
        ConsoleLogger console;
        Application app(&console);
        app.run();
    }
    
    std::cout << "\n=== File Logger Demo ===\n";
    {
        FileLogger file("app_log.txt");
        Application app(&file);
        app.run();
        std::cout << "Check app_log.txt for file output\n";
    }
    
    std::cout << "\n=== Silent Logger Demo ===\n";
    {
        SilentLogger silent;
        Application app(&silent);
        app.run();
        std::cout << "Silent logger produces no output\n";
    }
    
    std::cout << "\n=== Multi Logger Demo ===\n";
    {
        MultiLogger multi;
        multi.add_logger(std::make_unique<ConsoleLogger>());
        multi.add_logger(std::make_unique<FileLogger>("multi_log.txt"));
        
        Application app(&multi);
        app.run();
        std::cout << "Multi logger outputs to both console and file\n";
    }
    
    return 0;
}

/* Expected Output (Console portions):
=== Console Logger Demo ===
[Console] Application started
[Console] Doing important work...
[Console] Processing step 1
[Console] Processing step 2
[Console] Processing step 3
[Console] WARNING: This is just a warning
[Console] ERROR: Something went wrong!
[Console] Recovered from error
[Console] Application finished

=== File Logger Demo ===
Check app_log.txt for file output

=== Silent Logger Demo ===
Silent logger produces no output

=== Multi Logger Demo ===
[Console] Application started
[Console] Doing important work...
[Console] Processing step 1
[Console] Processing step 2
[Console] Processing step 3
[Console] WARNING: This is just a warning
[Console] ERROR: Something went wrong!
[Console] Recovered from error
[Console] Application finished
Multi logger outputs to both console and file
*/

/* Key Learning Points:
1. Polymorphism enables flexible, configurable systems
2. Same application code works with different logger implementations
3. Abstract interfaces make code testable (SilentLogger for tests)
4. Composition pattern (MultiLogger) builds complex behavior from simple parts
5. RAII and smart pointers ensure safe resource management
6. Virtual functions enable runtime strategy selection
*/