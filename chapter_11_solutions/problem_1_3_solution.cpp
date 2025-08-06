/*
 * Chapter 11, Problem 1.3: Resource Management with RAII
 * 
 * Solution: FileManager class using unique_ptr with custom deleter
 * 
 * Key concepts demonstrated:
 * - unique_ptr with custom deleter
 * - RAII for C-style resources (FILE*)
 * - Exception-safe resource management
 * - Custom deleter function specification
 */

#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

class FileManager {
private:
    // unique_ptr with custom deleter for FILE*
    // decltype(&std::fclose) gets the type of the fclose function pointer
    std::unique_ptr<FILE, decltype(&std::fclose)> file;
    
public:
    FileManager(const std::string& filename, const std::string& mode)
        : file(std::fopen(filename.c_str(), mode.c_str()), &std::fclose) {
        // Constructor opens file and stores in unique_ptr with custom deleter
        // If fopen fails, file will be nullptr
        if (!file) {
            std::cerr << "Failed to open file: " << filename << std::endl;
        }
    }
    
    bool write(const std::string& data) {
        if (!file) return false;
        
        // Use get() to access the raw FILE* pointer
        size_t written = std::fwrite(data.c_str(), 1, data.length(), file.get());
        std::fflush(file.get());  // Ensure data is written to disk
        
        return written == data.length();
    }
    
    std::string read_line() {
        if (!file) return "";
        
        char buffer[1024];
        if (std::fgets(buffer, sizeof(buffer), file.get())) {
            return std::string(buffer);
        }
        
        return "";  // End of file or error
    }
    
    bool is_open() const {
        // Convert unique_ptr to bool (true if not nullptr)
        return static_cast<bool>(file);
    }
};

int main() {
    {
        FileManager writer("test.txt", "w");
        if (writer.is_open()) {
            writer.write("Hello, Smart Pointers!\n");
            writer.write("RAII is awesome!\n");
        }
    }  // File automatically closed here via custom deleter
    
    {
        FileManager reader("test.txt", "r");
        if (reader.is_open()) {
            std::cout << "Line 1: " << reader.read_line();
            std::cout << "Line 2: " << reader.read_line();
        }
    }  // File automatically closed here via custom deleter
    
    return 0;
}

/*
 * Expected Output:
 * Line 1: Hello, Smart Pointers!
 * Line 2: RAII is awesome!
 * 
 * Key concepts demonstrated:
 * 
 * 1. Custom Deleter:
 *    - unique_ptr<FILE, decltype(&std::fclose)> specifies fclose as deleter
 *    - Automatically calls fclose when unique_ptr is destroyed
 *    - Works with C APIs that require specific cleanup functions
 * 
 * 2. RAII (Resource Acquisition Is Initialization):
 *    - Resource (file) acquired in constructor
 *    - Resource automatically released in destructor (via unique_ptr)
 *    - Exception-safe: if exception thrown, file still gets closed
 * 
 * 3. Alternative Custom Deleter Approaches:
 *    
 *    // Using lambda:
 *    auto file = std::unique_ptr<FILE, std::function<void(FILE*)>>(
 *        std::fopen("file.txt", "r"),
 *        [](FILE* f) { if (f) std::fclose(f); }
 *    );
 *    
 *    // Using function object:
 *    struct FileDeleter {
 *        void operator()(FILE* f) const {
 *            if (f) std::fclose(f);
 *        }
 *    };
 *    std::unique_ptr<FILE, FileDeleter> file(std::fopen("file.txt", "r"));
 * 
 * 4. Benefits:
 *    - No risk of forgetting to close file
 *    - Exception safety guaranteed
 *    - Clear ownership semantics
 *    - Zero overhead compared to manual management
 */