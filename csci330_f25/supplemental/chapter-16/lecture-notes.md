# Chapter 16: Streams - Complete Guide (Supplemental)

## 🎯 Learning Objectives (5 minutes)

**This is a supplemental chapter** - master strings first (Chapter 15) before exploring streams.

By the end of this chapter, you will:
- **Understand C++ I/O streams** - Input/output with cin, cout, and file streams
- **Master stream formatting** - Control output precision, alignment, and formatting
- **Handle file I/O efficiently** - Read from and write to files safely
- **Build custom stream operators** - Create << and >> operators for your classes
- **Debug stream problems** - Handle stream errors and edge cases

**Time Commitment**: ~4 hours (supplemental - take your time)

---

## 📚 Core Concepts

### Python/Java Developers: Stream Comparison

| Concept | Python | Java | C++ |
|---------|---------|------|-----|
| **Console Output** | `print("hello")` | `System.out.println("hello")` | `std::cout << "hello" << std::endl` |
| **Console Input** | `input()` | `Scanner.nextLine()` | `std::getline(std::cin, str)` |
| **File Output** | `with open("file.txt", "w")` | `FileWriter` | `std::ofstream file("file.txt")` |
| **File Input** | `with open("file.txt", "r")` | `FileReader` | `std::ifstream file("file.txt")` |
| **Formatting** | f-strings, .format() | String.format(), printf | std::format, iomanip |

**Key Insight**: C++ streams use the `<<` (insertion) and `>>` (extraction) operators for a consistent interface.

---

## 1. Stream Fundamentals

### Stream Hierarchy

```cpp
#include <iostream>
#include <fstream>
#include <sstream>

// Basic streams
std::cout << "Standard output" << std::endl;
std::cerr << "Standard error" << std::endl;    // Unbuffered
std::clog << "Standard log" << std::endl;      // Buffered

// File streams
std::ofstream out_file("output.txt");          // Output file
std::ifstream in_file("input.txt");            // Input file
std::fstream file("data.txt", std::ios::in | std::ios::out);  // Bidirectional

// String streams
std::ostringstream oss;                        // Output string stream
std::istringstream iss("input data");          // Input string stream
std::stringstream ss;                          // Bidirectional string stream
```

### Stream States and Error Handling

```cpp
#include <iostream>
#include <fstream>

void check_stream_state(std::istream& stream) {
    if (stream.good()) {
        std::cout << "Stream is good" << std::endl;
    }
    if (stream.eof()) {
        std::cout << "End of file reached" << std::endl;
    }
    if (stream.fail()) {
        std::cout << "Operation failed" << std::endl;
    }
    if (stream.bad()) {
        std::cout << "Stream corrupted" << std::endl;
    }
}

int main() {
    std::ifstream file("nonexistent.txt");
    
    if (!file) {  // Equivalent to file.fail()
        std::cout << "Failed to open file" << std::endl;
        return 1;
    }
    
    int number;
    while (file >> number) {  // Read until failure
        std::cout << "Read: " << number << std::endl;
    }
    
    check_stream_state(file);
    return 0;
}
```

---

## 2. Formatted Output

### Basic Output Formatting

```cpp
#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.14159265;
    int value = 42;
    
    // Precision control
    std::cout << std::setprecision(3) << pi << std::endl;        // 3.14
    std::cout << std::fixed << std::setprecision(2) << pi << std::endl;  // 3.14
    
    // Width and alignment
    std::cout << std::setw(10) << value << std::endl;           // "        42"
    std::cout << std::left << std::setw(10) << value << std::endl;  // "42        "
    std::cout << std::setfill('0') << std::setw(5) << value << std::endl;  // "00042"
    
    // Number base
    std::cout << std::hex << value << std::endl;                // 2a
    std::cout << std::oct << value << std::endl;                // 52
    std::cout << std::dec << value << std::endl;                // 42
    
    return 0;
}
```

### Modern Formatting (C++20)

```cpp
#include <format>  // C++20

int main() {
    double pi = 3.14159;
    int value = 42;
    
    // Python-style formatting
    std::cout << std::format("Pi: {:.2f}\n", pi);              // Pi: 3.14
    std::cout << std::format("Value: {:05d}\n", value);        // Value: 00042
    std::cout << std::format("Hex: {:#x}\n", value);           // Hex: 0x2a
    
    return 0;
}
```

---

## 3. File I/O Operations

### Reading and Writing Files

```cpp
#include <fstream>
#include <iostream>
#include <string>

// Writing to file
void write_data() {
    std::ofstream file("data.txt");
    
    if (!file) {
        std::cerr << "Cannot create file" << std::endl;
        return;
    }
    
    file << "Hello, World!" << std::endl;
    file << "Number: " << 42 << std::endl;
    file << "Pi: " << 3.14159 << std::endl;
    
    // File automatically closed when ofstream destructor runs
}

// Reading from file
void read_data() {
    std::ifstream file("data.txt");
    
    if (!file) {
        std::cerr << "Cannot open file" << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::cout << "Read: " << line << std::endl;
    }
}

// Reading structured data
void read_structured() {
    std::ifstream file("numbers.txt");
    
    int number;
    while (file >> number) {
        std::cout << "Number: " << number << std::endl;
    }
}
```

### Binary File I/O

```cpp
#include <fstream>
#include <iostream>

struct Person {
    char name[50];
    int age;
    double salary;
};

void write_binary() {
    std::ofstream file("people.bin", std::ios::binary);
    
    Person person = {"Alice", 30, 75000.50};
    file.write(reinterpret_cast<const char*>(&person), sizeof(person));
}

void read_binary() {
    std::ifstream file("people.bin", std::ios::binary);
    
    Person person;
    if (file.read(reinterpret_cast<char*>(&person), sizeof(person))) {
        std::cout << "Name: " << person.name << std::endl;
        std::cout << "Age: " << person.age << std::endl;
        std::cout << "Salary: " << person.salary << std::endl;
    }
}
```

---

## 4. String Streams

### Using String Streams for Parsing

```cpp
#include <sstream>
#include <iostream>
#include <vector>

// Parse CSV line
std::vector<std::string> parse_csv(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream stream(line);
    std::string token;
    
    while (std::getline(stream, token, ',')) {
        tokens.push_back(token);
    }
    
    return tokens;
}

// Build formatted string
std::string format_person(const std::string& name, int age, double salary) {
    std::ostringstream oss;
    oss << "Person { name: \"" << name << "\", age: " << age 
        << ", salary: $" << std::fixed << std::setprecision(2) << salary << " }";
    return oss.str();
}

int main() {
    // Parsing example
    std::string csv = "Alice,30,75000.50";
    auto fields = parse_csv(csv);
    for (const auto& field : fields) {
        std::cout << "Field: '" << field << "'" << std::endl;
    }
    
    // Formatting example
    std::string formatted = format_person("Bob", 25, 60000.0);
    std::cout << formatted << std::endl;
    
    return 0;
}
```

---

## 5. Custom Stream Operators

### Implementing << and >> for Custom Types

```cpp
#include <iostream>
#include <string>

class Person {
    std::string name;
    int age;
    
public:
    Person(const std::string& n = "", int a = 0) : name(n), age(a) {}
    
    // Getter methods
    const std::string& getName() const { return name; }
    int getAge() const { return age; }
    
    // Setter methods
    void setName(const std::string& n) { name = n; }
    void setAge(int a) { age = a; }
    
    // Friend functions for stream operators
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
    friend std::istream& operator>>(std::istream& is, Person& person);
};

// Output operator
std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.name << " (" << person.age << " years old)";
    return os;
}

// Input operator
std::istream& operator>>(std::istream& is, Person& person) {
    is >> person.name >> person.age;
    return is;
}

int main() {
    Person alice("Alice", 30);
    std::cout << "Person: " << alice << std::endl;
    
    Person bob;
    std::cout << "Enter name and age: ";
    std::cin >> bob;
    std::cout << "You entered: " << bob << std::endl;
    
    return 0;
}
```

---

## 🧩 Quick Problems

### Problem 1: Log File Analyzer
Create a program that reads a log file and counts error messages.

### Problem 2: CSV Processor
Build a CSV reader that can handle quoted fields and different delimiters.

### Problem 3: Configuration File Parser
Parse a simple INI-style configuration file.

See [chapter_16_problems.md](chapter_16_problems.md) for detailed problems.

---

## 🔧 Quick Reference

See [chapter_16_quick_help.md](chapter_16_quick_help.md) for common stream errors.

---

## ✅ Success Checklist

- [ ] Understand stream hierarchy and error states
- [ ] Can format output with precision and alignment
- [ ] Successfully read from and write to files
- [ ] Handle file errors gracefully
- [ ] Use string streams for parsing and formatting
- [ ] Implement custom stream operators

---

## 🚀 What's Next

**Streams are powerful tools** for I/O operations in C++. This knowledge is essential for file processing, data parsing, and formatted output.

**Continue with**: Chapter 17 (Filesystems) or Chapter 18 (Algorithms) for more advanced topics.

---

*This is a supplemental chapter - master core concepts first, then return to explore streams in depth.*