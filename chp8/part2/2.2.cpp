#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>

class FileProcessor {
private:
    std::ifstream file;
    std::string filename;

public:
    // Constructor - acquire resource
    FileProcessor(const std::string& filename) : filename(filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
    }

    // Destructor - release resource
    ~FileProcessor() {
        if (file.is_open()) {
            file.close();
            std::cout << "File closed: " << filename << std::endl;
        }
    }

    // Delete copy constructor and assignment operator
    FileProcessor(const FileProcessor&) = delete;
    FileProcessor& operator=(const FileProcessor&) = delete;

    int count_lines() {
        if (!file.is_open()) throw std::runtime_error("File not open");

        file.clear(); // clear any EOF flags
        file.seekg(0); // rewind to beginning

        int lines = 0;
        std::string line;
        while (std::getline(file, line)) {
            ++lines;
        }

        file.clear();
        file.seekg(0);
        return lines;
    }

    int count_words() {
        if (!file.is_open()) throw std::runtime_error("File not open");

        file.clear();
        file.seekg(0);

        int words = 0;
        std::string word;
        while (file >> word) {
            ++words;
        }

        file.clear();
        file.seekg(0);
        return words;
    }

    int count_characters() {
        if (!file.is_open()) throw std::runtime_error("File not open");

        file.clear();
        file.seekg(0);

        int chars = 0;
        char ch;
        while (file.get(ch)) {
            ++chars;
        }

        file.clear();
        file.seekg(0);
        return chars;
    }
};

// Test function that demonstrates RAII even with exceptions
void test_file_processing(const std::string& filename) {
    try {
        FileProcessor processor(filename);

        std::cout << "Lines: " << processor.count_lines() << std::endl;
        std::cout << "Words: " << processor.count_words() << std::endl;
        std::cout << "Characters: " << processor.count_characters() << std::endl;

        // Simulate an exception
        if (processor.count_lines() > 100) {
            throw std::runtime_error("File too large!");
        }

    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        // File is closed automatically due to RAII
    }
}

int main() {
    std::string validFile = "sample.txt";
    std::string invalidFile = "nonexistent.txt";

    std::cout << "\n--- Testing valid file ---\n";
    test_file_processing(validFile);

    std::cout << "\n--- Testing invalid file ---\n";
    test_file_processing(invalidFile);

    return 0;
}