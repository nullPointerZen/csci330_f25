#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

class FileManager {
private:
    std::unique_ptr<FILE, decltype(&std::fclose)> file;

public:
    // Constructor opens the file and sets up the custom deleter
    FileManager(const std::string& filename, const std::string& mode)
        : file(std::fopen(filename.c_str(), mode.c_str()), &std::fclose) {}

    // Write data to file
    bool write(const std::string& data) {
        if (!file) return false;
        return std::fputs(data.c_str(), file.get()) != EOF;
    }

    // Read one line from file
    std::string read_line() {
        if (!file) return "";
        char buffer[1024];
        if (std::fgets(buffer, sizeof(buffer), file.get())) {
            return std::string(buffer);
        }
        return "";
    }

    // Check if file is open
    bool is_open() const {
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
    }  // File automatically closed here

    {
        FileManager reader("test.txt", "r");
        if (reader.is_open()) {
            std::cout << "Line 1: " << reader.read_line();
            std::cout << "Line 2: " << reader.read_line();
        }
    }  // File automatically closed here

    return 0;
}