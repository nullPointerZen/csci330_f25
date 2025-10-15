#include <iostream>
#include <fstream>
#include <string>

// Abstract base class
struct Logger {
    virtual ~Logger() = default;
    virtual void log(const std::string& message) const = 0;

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

// SilentLogger: does nothing
struct SilentLogger : Logger {
    void log(const std::string& /*message*/) const override {
        // No output
    }
};

// Application class using Logger
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
        logger->log_error("Something went wrong!");
        logger->log("Recovered from error");
    }
};

int main() {
    ConsoleLogger console;
    FileLogger file("log.txt");
    SilentLogger silent;

    Application app1(&console);
    Application app2(&file);
    Application app3(&silent);

    std::cout << "=== Console Logger ===\n";
    app1.run();

    std::cout << "\n=== File Logger ===\n";
    app2.run();

    std::cout << "\n=== Silent Logger ===\n";
    app3.run();

    return 0;
}