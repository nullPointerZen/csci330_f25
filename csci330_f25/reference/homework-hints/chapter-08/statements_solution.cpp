#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>

// Grade calculator with switch statement
void grade_calculator() {
    std::cout << "=== Grade Calculator ===\n";
    std::cout << "Enter numeric grade (0-100): ";
    int grade;
    std::cin >> grade;

    if (grade < 0 || grade > 100) {
        std::cout << "Error: Grade must be between 0 and 100\n";
        return;
    }

    char letter_grade;
    int grade_range = grade / 10;

    switch (grade_range) {
        case 10:
        case 9:
            letter_grade = 'A';
            break;
        case 8:
            letter_grade = 'B';
            break;
        case 7:
            letter_grade = 'C';
            break;
        case 6:
            letter_grade = 'D';
            break;
        default:
            letter_grade = 'F';
            break;
    }

    std::cout << "Grade: " << letter_grade << std::endl;
}

// Number pattern generator
void number_pattern() {
    std::cout << "\n=== Number Pattern Generator ===\n";
    int size;
    char mode;

    std::cout << "Enter pattern size (1-10): ";
    std::cin >> size;

    if (size < 1 || size > 10) {
        std::cout << "Error: Size must be between 1 and 10\n";
        return;
    }

    std::cout << "Show all rows (a) or odd rows only (o)? ";
    std::cin >> mode;

    for (int i = 1; i <= size; ++i) {
        if (mode == 'o' && i % 2 == 0) {
            continue;  // Skip even rows in odd-only mode
        }

        for (int j = 1; j <= i; ++j) {
            std::cout << j;
        }
        std::cout << std::endl;
    }
}

// Range-based for loop with containers
void temperature_analysis() {
    std::cout << "\n=== Temperature Analysis ===\n";
    std::vector<double> temperatures = {68.5, 72.1, 69.8, 74.2, 71.5, 73.0, 70.2};

    // Display all temperatures
    std::cout << "Original temperatures: ";
    for (const auto& temp : temperatures) {
        std::cout << temp << " ";
    }
    std::cout << std::endl;

    // Calculate average
    double sum = 0.0;
    for (const auto& temp : temperatures) {
        sum += temp;
    }
    double average = sum / temperatures.size();
    std::cout << "Average temperature: " << average << std::endl;

    // Count temperatures above average
    int above_average = 0;
    for (const auto& temp : temperatures) {
        if (temp > average) {
            above_average++;
        }
    }
    std::cout << "Temperatures above average: " << above_average << std::endl;

    // Modify all temperatures by adding 2.0 degrees
    for (auto& temp : temperatures) {
        temp += 2.0;
    }

    // Display modified temperatures
    std::cout << "Modified temperatures (+2.0): ";
    for (const auto& temp : temperatures) {
        std::cout << temp << " ";
    }
    std::cout << std::endl;
}

// Safe division with exception handling
double safe_divide(double numerator, double denominator) {
    if (denominator == 0.0) {
        throw std::runtime_error("Division by zero is not allowed");
    }
    return numerator / denominator;
}

void calculator_demo() {
    std::cout << "\n=== Safe Calculator Demo ===\n";

    try {
        std::cout << "10 / 2 = " << safe_divide(10.0, 2.0) << std::endl;
        std::cout << "10 / 0 = " << safe_divide(10.0, 0.0) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test invalid input handling
    try {
        double a = 5.0, b = 3.0;
        std::cout << "5 / 3 = " << safe_divide(a, b) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// RAII File Processor
class FileProcessor {
private:
    std::ifstream file;
    std::string filename;

public:
    FileProcessor(const std::string& filename) : filename(filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        std::cout << "File opened: " << filename << std::endl;
    }

    ~FileProcessor() {
        if (file.is_open()) {
            file.close();
            std::cout << "File closed: " << filename << std::endl;
        }
    }

    // Delete copy constructor and assignment (RAII best practice)
    FileProcessor(const FileProcessor&) = delete;
    FileProcessor& operator=(const FileProcessor&) = delete;

    int count_lines() {
        if (!file.is_open()) return 0;

        file.seekg(0);  // Reset to beginning
        std::string line;
        int count = 0;
        while (std::getline(file, line)) {
            count++;
        }
        file.clear();  // Clear EOF flag
        return count;
    }

    int count_words() {
        if (!file.is_open()) return 0;

        file.seekg(0);
        std::string word;
        int count = 0;
        while (file >> word) {
            count++;
        }
        file.clear();
        return count;
    }

    int count_characters() {
        if (!file.is_open()) return 0;

        file.seekg(0);
        char ch;
        int count = 0;
        while (file.get(ch)) {
            count++;
        }
        file.clear();
        return count;
    }
};

// Timed operation helper
class TimedOperation {
private:
    std::chrono::steady_clock::time_point start_time;
    std::string operation_name;

public:
    TimedOperation(const std::string& name) : operation_name(name) {
        start_time = std::chrono::steady_clock::now();
        std::cout << "Starting: " << operation_name << std::endl;
    }

    ~TimedOperation() {
        auto end_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "Completed: " << operation_name << " in " << duration.count() << " ms" << std::endl;
    }

    double elapsed_ms() const {
        auto end_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        return duration.count();
    }
};

void test_raii() {
    std::cout << "\n=== RAII File Processing Demo ===\n";

    // Create a test file first
    {
        std::ofstream test_file("sample.txt");
        test_file << "This is a test file.\n";
        test_file << "It has multiple lines.\n";
        test_file << "For testing file processing.\n";
    }

    try {
        TimedOperation timer("File Processing");
        FileProcessor processor("sample.txt");

        std::cout << "Lines: " << processor.count_lines() << std::endl;
        std::cout << "Words: " << processor.count_words() << std::endl;
        std::cout << "Characters: " << processor.count_characters() << std::endl;

        // File automatically closed when processor goes out of scope
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test with non-existent file
    try {
        FileProcessor bad_processor("nonexistent.txt");
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
}

void loop_examples() {
    std::cout << "\n=== Loop Examples ===\n";

    // Traditional for loop
    std::cout << "Traditional for loop: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    // Range-based for loop
    std::vector<std::string> words = {"Hello", "World", "C++", "Programming"};
    std::cout << "Range-based for: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    // While loop with break/continue
    std::cout << "While loop with continue (odds only): ";
    int i = 0;
    while (i < 10) {
        ++i;
        if (i % 2 == 0) continue;  // Skip even numbers
        std::cout << i << " ";
        if (i >= 7) break;  // Exit early
    }
    std::cout << std::endl;
}

int main() {
    try {
        grade_calculator();
        number_pattern();
        temperature_analysis();
        calculator_demo();
        test_raii();
        loop_examples();

        std::cout << "\n=== All demos completed successfully ===\n";

    } catch (const std::exception& e) {
        std::cout << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}