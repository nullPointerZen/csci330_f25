// Problem 2.1: File Logger Class Solution
// Demonstrates RAII (Resource Acquisition Is Initialization)

#include <cstdio>

class FileLogger {
public:
    FileLogger(const char* filename) : filename{filename} {
        file = fopen(filename, "w");
        if (file) {
            printf("Log file '%s' opened successfully\n", filename);
        } else {
            printf("Error: Could not open log file '%s'\n", filename);
        }
    }
    
    ~FileLogger() {
        if (file) {
            printf("Closing log file '%s'\n", filename);
            fclose(file);
        }
    }
    
    void log_message(const char* message) {
        if (file) {
            fprintf(file, "LOG: %s\n", message);
            fflush(file); // Ensure message is written immediately
            printf("Logged: %s\n", message);
        } else {
            printf("Cannot log message (file not open): %s\n", message);
        }
    }
    
private:
    FILE* file;
    const char* filename;
};

int main() {
    printf("=== Creating FileLogger ===\n");
    {
        FileLogger logger{"test.log"};
        logger.log_message("Application started");
        logger.log_message("Processing data");
        logger.log_message("Application ending");
        printf("=== About to leave logger scope ===\n");
    }
    printf("=== Logger destroyed, file automatically closed ===\n");
    
    // Test with invalid file path
    printf("\n=== Testing error handling ===\n");
    {
        FileLogger bad_logger{"/nonexistent/invalid.log"};
        bad_logger.log_message("This won't be written");
    }
    
    return 0;
}

/* 
Compilation command:
g++ -o file_logger problem_2_1_solution.cpp

Expected Output:
=== Creating FileLogger ===
Log file 'test.log' opened successfully  
Logged: Application started
Logged: Processing data
Logged: Application ending
=== About to leave logger scope ===
Closing log file 'test.log'
=== Logger destroyed, file automatically closed ===

=== Testing error handling ===
Error: Could not open log file '/nonexistent/invalid.log'
Cannot log message (file not open): This won't be written

Key Learning Points:
1. RAII: Resource acquired in constructor, released in destructor
2. File automatically closed when object goes out of scope
3. Similar to Python's "with open()" statement
4. Error handling in constructor - object still created but marked invalid
5. Destructor handles cleanup even if constructor partially failed
6. This is much safer than manual fopen/fclose pairs

Check test.log file after running - it should contain:
LOG: Application started
LOG: Processing data
LOG: Application ending
*/