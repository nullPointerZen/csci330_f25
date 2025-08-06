/**
 * Problem 2.2: File Processor with RAII
 * 
 * Demonstrates:
 * - RAII (Resource Acquisition Is Initialization)
 * - Constructor/destructor resource management
 * - Exception safety
 * - Rule of 5 implementation
 * - File stream handling
 */

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
    // Constructor - acquire resource (open file)
    explicit FileProcessor(const std::string& filename) : filename(filename) {
        file.open(filename);
        
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
        
        std::cout << "File '" << filename << "' opened successfully" << std::endl;
    }
    
    // Destructor - release resource (close file)
    ~FileProcessor() {
        if (file.is_open()) {
            file.close();
            std::cout << "File '" << filename << "' closed automatically" << std::endl;
        }
    }
    
    // Delete copy constructor and assignment operator (Rule of 5)
    // RAII objects should typically not be copied
    FileProcessor(const FileProcessor&) = delete;
    FileProcessor& operator=(const FileProcessor&) = delete;
    
    // Move constructor (Rule of 5)
    FileProcessor(FileProcessor&& other) noexcept 
        : file(std::move(other.file)), filename(std::move(other.filename)) {
        // other.file is now in valid but unspecified state
    }
    
    // Move assignment (Rule of 5)
    FileProcessor& operator=(FileProcessor&& other) noexcept {
        if (this != &other) {
            // Close current file if open
            if (file.is_open()) {
                file.close();
            }
            
            // Move resources from other
            file = std::move(other.file);
            filename = std::move(other.filename);
        }
        return *this;
    }
    
    int count_lines() {
        if (!file.is_open()) {
            throw std::runtime_error("File is not open");
        }
        
        // Save current position
        auto current_pos = file.tellg();
        
        // Go to beginning of file
        file.seekg(0, std::ios::beg);
        
        int line_count = 0;
        std::string line;
        
        while (std::getline(file, line)) {
            ++line_count;
        }
        
        // Reset file position and clear any error flags
        file.clear();
        file.seekg(current_pos);
        
        return line_count;
    }
    
    int count_words() {
        if (!file.is_open()) {
            throw std::runtime_error("File is not open");
        }
        
        // Save current position
        auto current_pos = file.tellg();
        
        // Go to beginning of file
        file.seekg(0, std::ios::beg);
        
        int word_count = 0;
        std::string word;
        
        while (file >> word) {
            ++word_count;
        }
        
        // Reset file position and clear any error flags
        file.clear();
        file.seekg(current_pos);
        
        return word_count;
    }
    
    int count_characters() {
        if (!file.is_open()) {
            throw std::runtime_error("File is not open");
        }
        
        // Save current position
        auto current_pos = file.tellg();
        
        // Go to beginning and end to get file size
        file.seekg(0, std::ios::beg);
        auto begin_pos = file.tellg();
        file.seekg(0, std::ios::end);
        auto end_pos = file.tellg();
        
        int char_count = static_cast<int>(end_pos - begin_pos);
        
        // Reset file position and clear any error flags
        file.clear();
        file.seekg(current_pos);
        
        return char_count;
    }
    
    // Get filename for display purposes
    const std::string& get_filename() const {
        return filename;
    }
};

// Test function that demonstrates RAII even with exceptions
void test_file_processing(const std::string& filename) {
    std::cout << "\n=== Testing file: " << filename << " ===" << std::endl;
    
    try {
        FileProcessor processor(filename);
        
        // Get file statistics
        int lines = processor.count_lines();
        int words = processor.count_words();
        int characters = processor.count_characters();
        
        std::cout << "File statistics:" << std::endl;
        std::cout << "  Lines: " << lines << std::endl;
        std::cout << "  Words: " << words << std::endl;
        std::cout << "  Characters: " << characters << std::endl;
        
        // Simulate an exception based on file size
        if (lines > 100) {
            throw std::runtime_error("File too large for processing!");
        }
        
        if (lines == 0) {
            throw std::runtime_error("File is empty!");
        }
        
        std::cout << "File processing completed successfully" << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error during processing: " << e.what() << std::endl;
        // File should still be properly closed due to RAII
        std::cout << "Note: File cleanup handled automatically by RAII" << std::endl;
    }
}

// Helper function to create a test file
void create_test_file(const std::string& filename, const std::string& content) {
    std::ofstream out_file(filename);
    if (out_file.is_open()) {
        out_file << content;
        std::cout << "Created test file: " << filename << std::endl;
    }
}

int main() {
    std::cout << "=== RAII File Processor Demo ===" << std::endl;
    
    // Create some test files with different content
    create_test_file("small_test.txt", "Hello world!\nThis is a test file.\nIt has three lines.");
    create_test_file("empty_test.txt", "");
    
    // Create a larger test file
    std::string large_content;
    for (int i = 1; i <= 150; ++i) {
        large_content += "This is line number " + std::to_string(i) + "\n";
    }
    create_test_file("large_test.txt", large_content);
    
    // Test with different files
    test_file_processing("small_test.txt");   // Should work fine
    test_file_processing("empty_test.txt");   // Should throw "empty file" exception
    test_file_processing("large_test.txt");   // Should throw "too large" exception
    test_file_processing("nonexistent.txt"); // Should throw "cannot open" exception
    
    std::cout << "\n=== Demo completed ===" << std::endl;
    std::cout << "Notice how files are automatically closed even when exceptions occur!" << std::endl;
    
    return 0;
}