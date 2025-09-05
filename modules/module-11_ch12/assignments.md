# Chapter 12: Utilities - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 12 "Utilities"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 1.5 hours total for both problem sets
- Test all programs thoroughly before submission

**Target Audience**: Students with Python/Java background  
**Total Time**: 1.5 hours (90 minutes)  
**Prerequisites**: Chapters 1-11 completed + Chapter 12 lesson  

## Problem Set Structure

- **Problem Set 1**: Move Semantics and std::optional (45 minutes)
- **Problem Set 2**: std::variant and Type-Safe Programming (60 minutes) 
- **Problem Set 3**: std::any and Advanced Utilities (30 minutes)

---

## Problem Set 1: Move Semantics and std::optional (45 minutes)

### Problem 1.1: Move Semantics Fundamentals (20 minutes)

**Background**: Coming from Python's reference semantics or Java's object references, learn C++ move semantics for performance optimization.

**Task**: Implement classes with proper move semantics and understand when moves occur.

**Requirements**:
1. Create a class with move constructor and move assignment
2. Demonstrate the difference between copy and move operations
3. Use std::move explicitly when needed
4. Understand return value optimization and when moves happen automatically

**Starter Code**:
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <chrono>

class ResourceManager {
private:
    std::vector<int> data_;
    std::string name_;
    std::unique_ptr<int[]> buffer_;
    size_t buffer_size_;
    
public:
    // TODO: Regular constructor
    ResourceManager(const std::string& name, size_t size) 
        : name_(name), buffer_size_(size) {
        std::cout << "ResourceManager '" << name_ << "' constructed with " << size << " elements\n";
        
        // TODO: Initialize data and buffer
        data_.resize(size);
        for (size_t i = 0; i < size; ++i) {
            data_[i] = static_cast<int>(i);
        }
        
        buffer_ = std::make_unique<int[]>(buffer_size_);
        for (size_t i = 0; i < buffer_size_; ++i) {
            buffer_[i] = static_cast<int>(i * 2);
        }
    }
    
    // TODO: Copy constructor
    ResourceManager(const ResourceManager& other) 
        : name_(other.name_ + "_copy"), data_(other.data_), buffer_size_(other.buffer_size_) {
        std::cout << "ResourceManager '" << name_ << "' COPY constructed from '" << other.name_ << "'\n";
        
        // TODO: Deep copy the buffer
        buffer_ = std::make_unique<int[]>(buffer_size_);
        for (size_t i = 0; i < buffer_size_; ++i) {
            buffer_[i] = other.buffer_[i];
        }
    }
    
    // TODO: Move constructor
    ResourceManager(ResourceManager&& other) noexcept
        : name_(std::move(other.name_)), data_(std::move(other.data_)), 
          buffer_(std::move(other.buffer_)), buffer_size_(other.buffer_size_) {
        std::cout << "ResourceManager '" << name_ << "' MOVE constructed\n";
        
        // TODO: Reset other object to valid but unspecified state
        other.buffer_size_ = 0;
        other.name_ += "_moved";
    }
    
    // TODO: Copy assignment operator
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            std::cout << "ResourceManager '" << name_ << "' COPY assigned from '" << other.name_ << "'\n";
            
            // TODO: Copy all data
            name_ = other.name_ + "_copy_assigned";
            data_ = other.data_;
            buffer_size_ = other.buffer_size_;
            
            buffer_ = std::make_unique<int[]>(buffer_size_);
            for (size_t i = 0; i < buffer_size_; ++i) {
                buffer_[i] = other.buffer_[i];
            }
        }
        return *this;
    }
    
    // TODO: Move assignment operator
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            std::cout << "ResourceManager '" << name_ << "' MOVE assigned\n";
            
            // TODO: Move all resources
            name_ = std::move(other.name_);
            data_ = std::move(other.data_);
            buffer_ = std::move(other.buffer_);
            buffer_size_ = other.buffer_size_;
            
            // Reset other
            other.buffer_size_ = 0;
            other.name_ += "_moved";
        }
        return *this;
    }
    
    ~ResourceManager() {
        std::cout << "ResourceManager '" << name_ << "' destroyed\n";
    }
    
    void display_info() const {
        std::cout << "ResourceManager '" << name_ << "' - data size: " << data_.size() 
                  << ", buffer size: " << buffer_size_ << "\n";
        if (buffer_ && buffer_size_ > 0) {
            std::cout << "  First 3 buffer elements: " << buffer_[0] << ", " 
                      << buffer_[1] << ", " << buffer_[2] << "\n";
        }
    }
    
    const std::string& name() const { return name_; }
};

// TODO: Function that returns by value (demonstrates RVO and move)
ResourceManager create_resource(const std::string& name, size_t size) {
    std::cout << "Creating resource in factory function\n";
    ResourceManager resource(name, size);
    std::cout << "Returning resource from factory function\n";
    return resource;  // RVO or move will be used
}

// TODO: Function that demonstrates explicit std::move
void demonstrate_explicit_move() {
    std::cout << "=== Explicit std::move Demo ===\n";
    
    ResourceManager resource1("Original", 5);
    resource1.display_info();
    
    std::cout << "\nUsing std::move to transfer ownership:\n";
    ResourceManager resource2 = std::move(resource1);
    
    std::cout << "\nAfter move:\n";
    resource1.display_info();  // Should show moved-from state
    resource2.display_info();  // Should have the original data
}

void demonstrate_container_moves() {
    std::cout << "\n=== Container Move Demo ===\n";
    
    std::vector<ResourceManager> resources;
    
    std::cout << "Adding resources to vector (moves will occur):\n";
    resources.push_back(create_resource("Resource1", 3));
    resources.push_back(create_resource("Resource2", 4));
    
    std::cout << "\nResources in vector:\n";
    for (const auto& resource : resources) {
        resource.display_info();
    }
}

int main() {
    demonstrate_explicit_move();
    demonstrate_container_moves();
    
    std::cout << "\nAll resources going out of scope...\n";
    return 0;
}
```

**Learning Goals**:
- Move constructor and assignment implementation
- Understanding when moves happen automatically
- Explicit std::move usage
- Performance benefits of move semantics

---

### Problem 1.2: std::optional Fundamentals (15 minutes)

**Background**: Use std::optional for type-safe nullable values, similar to Python's None or Java's Optional.

**Task**: Implement functions that return optional values and handle them safely.

**Requirements**:
1. Create functions that return std::optional
2. Use different ways to check and extract values
3. Provide default values safely
4. Chain optional operations

**Starter Code**:
```cpp
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <map>

// TODO: Function that returns optional based on condition
std::optional<int> safe_divide(int numerator, int denominator) {
    // TODO: Return nullopt for division by zero, otherwise return result
}

// TODO: Function that searches and returns optional
std::optional<std::string> find_student_name(int student_id) {
    static std::map<int, std::string> students = {
        {101, "Alice Johnson"},
        {102, "Bob Smith"},
        {103, "Charlie Brown"},
        {104, "Diana Prince"}
    };
    
    // TODO: Return student name if found, nullopt otherwise
}

// TODO: Function that parses string to optional int
std::optional<int> parse_int(const std::string& str) {
    try {
        // TODO: Attempt to parse string to int
        size_t pos;
        int value = std::stoi(str, &pos);
        
        // TODO: Check if entire string was consumed
        if (pos == str.length()) {
            return value;
        }
        return std::nullopt;
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

// TODO: Function that validates and returns optional
std::optional<double> calculate_grade_average(const std::vector<int>& grades) {
    if (grades.empty()) {
        return std::nullopt;
    }
    
    // TODO: Check for invalid grades
    for (int grade : grades) {
        if (grade < 0 || grade > 100) {
            return std::nullopt;
        }
    }
    
    // TODO: Calculate average
    double sum = 0.0;
    for (int grade : grades) {
        sum += grade;
    }
    
    return sum / grades.size();
}

class Student {
private:
    std::string name_;
    std::optional<int> student_id_;
    std::optional<double> gpa_;
    
public:
    Student(const std::string& name) : name_(name) {}
    
    // TODO: Optional setter methods
    void set_student_id(int id) {
        if (id > 0) {
            student_id_ = id;
        }
    }
    
    void set_gpa(double gpa) {
        if (gpa >= 0.0 && gpa <= 4.0) {
            gpa_ = gpa;
        }
    }
    
    // TODO: Optional getter methods
    std::optional<int> get_student_id() const { return student_id_; }
    std::optional<double> get_gpa() const { return gpa_; }
    
    void display_info() const {
        std::cout << "Student: " << name_ << "\n";
        
        // TODO: Display optional values safely
        if (student_id_.has_value()) {
            std::cout << "  ID: " << student_id_.value() << "\n";
        } else {
            std::cout << "  ID: Not assigned\n";
        }
        
        // TODO: Use value_or for default display
        std::cout << "  GPA: " << gpa_.value_or(-1.0);
        if (!gpa_.has_value()) {
            std::cout << " (Not calculated)";
        }
        std::cout << "\n";
    }
    
    const std::string& name() const { return name_; }
};

void demonstrate_optional_basics() {
    std::cout << "=== Optional Basics Demo ===\n";
    
    // TODO: Test safe_divide function
    std::cout << "Safe division tests:\n";
    auto result1 = safe_divide(10, 2);
    auto result2 = safe_divide(10, 0);
    
    // TODO: Check and display results
    if (result1.has_value()) {
        std::cout << "10 / 2 = " << result1.value() << "\n";
    }
    
    if (result2.has_value()) {
        std::cout << "10 / 0 = " << result2.value() << "\n";
    } else {
        std::cout << "10 / 0 = Division by zero!\n";
    }
    
    // TODO: Test student lookup
    std::cout << "\nStudent lookup tests:\n";
    auto student1 = find_student_name(102);
    auto student2 = find_student_name(999);
    
    std::cout << "Student 102: " << student1.value_or("Not found") << "\n";
    std::cout << "Student 999: " << student2.value_or("Not found") << "\n";
}

void demonstrate_optional_chaining() {
    std::cout << "\n=== Optional Chaining Demo ===\n";
    
    std::vector<std::string> inputs = {"42", "not_a_number", "100", "-5"};
    
    for (const auto& input : inputs) {
        std::cout << "Parsing '" << input << "': ";
        
        auto parsed = parse_int(input);
        if (parsed.has_value()) {
            std::cout << "Success! Value = " << parsed.value();
            
            // TODO: Chain another operation
            if (parsed.value() >= 0) {
                std::cout << " (positive)";
            }
        } else {
            std::cout << "Failed to parse";
        }
        std::cout << "\n";
    }
}

void demonstrate_student_optionals() {
    std::cout << "\n=== Student Optional Fields Demo ===\n";
    
    Student student1("Alice");
    Student student2("Bob");
    
    // TODO: Set some optional fields
    student1.set_student_id(12345);
    student1.set_gpa(3.75);
    
    student2.set_student_id(-1);  // Invalid, won't be set
    student2.set_gpa(5.0);        // Invalid, won't be set
    
    std::cout << "\nStudent information:\n";
    student1.display_info();
    std::cout << "\n";
    student2.display_info();
}

int main() {
    demonstrate_optional_basics();
    demonstrate_optional_chaining();
    demonstrate_student_optionals();
    
    return 0;
}
```

**Learning Goals**:
- std::optional creation and checking
- Safe value extraction methods
- Using value_or for defaults
- Optional in class design

---

### Problem 1.3: Perfect Forwarding (10 minutes)

**Background**: Use std::forward to preserve value categories in template functions.

**Task**: Implement generic functions that perfectly forward arguments.

**Requirements**:
1. Create wrapper functions using perfect forwarding
2. Understand universal references
3. Preserve lvalue/rvalue categories
4. Use std::forward correctly in templates

**Starter Code**:
```cpp
#include <iostream>
#include <utility>
#include <memory>
#include <string>

class LoggedResource {
private:
    std::string name_;
    int value_;
    
public:
    // TODO: Constructor that can be called with various argument types
    LoggedResource(const std::string& name, int value) : name_(name), value_(value) {
        std::cout << "LoggedResource(const string&, int) - LVALUE name\n";
    }
    
    LoggedResource(std::string&& name, int value) : name_(std::move(name)), value_(value) {
        std::cout << "LoggedResource(string&&, int) - RVALUE name\n";
    }
    
    LoggedResource(const LoggedResource& other) : name_(other.name_ + "_copied"), value_(other.value_) {
        std::cout << "LoggedResource COPY constructor\n";
    }
    
    LoggedResource(LoggedResource&& other) noexcept : name_(std::move(other.name_)), value_(other.value_) {
        std::cout << "LoggedResource MOVE constructor\n";
        other.value_ = 0;
    }
    
    void display() const {
        std::cout << "LoggedResource: " << name_ << " = " << value_ << "\n";
    }
};

// TODO: Perfect forwarding factory function
template<typename... Args>
std::unique_ptr<LoggedResource> make_logged_resource(Args&&... args) {
    std::cout << "make_logged_resource called with " << sizeof...(args) << " arguments\n";
    
    // TODO: Use perfect forwarding to construct the resource
    return std::make_unique<LoggedResource>(std::forward<Args>(args)...);
}

// TODO: Generic wrapper function
template<typename Func, typename... Args>
auto call_and_log(Func&& func, Args&&... args) -> decltype(func(std::forward<Args>(args)...)) {
    std::cout << "call_and_log: Calling function with " << sizeof...(args) << " arguments\n";
    
    // TODO: Perfect forward to the actual function
    auto result = func(std::forward<Args>(args)...);
    
    std::cout << "call_and_log: Function call completed\n";
    return result;
}

// TODO: Test functions to call through wrapper
int add_numbers(int a, int b) {
    std::cout << "add_numbers(" << a << ", " << b << ") called\n";
    return a + b;
}

std::string concatenate_strings(const std::string& a, const std::string& b) {
    std::cout << "concatenate_strings called\n";
    return a + b;
}

void demonstrate_perfect_forwarding() {
    std::cout << "=== Perfect Forwarding Demo ===\n";
    
    // TODO: Test with different argument types
    std::string name1 = "Resource1";
    
    std::cout << "\n1. Forwarding lvalue string:\n";
    auto resource1 = make_logged_resource(name1, 42);
    resource1->display();
    
    std::cout << "\n2. Forwarding rvalue string:\n";
    auto resource2 = make_logged_resource(std::string("Resource2"), 84);
    resource2->display();
    
    std::cout << "\n3. Forwarding string literal:\n";
    auto resource3 = make_logged_resource("Resource3", 126);
    resource3->display();
}

void demonstrate_function_forwarding() {
    std::cout << "\n=== Function Forwarding Demo ===\n";
    
    // TODO: Use wrapper with different functions
    std::cout << "\n1. Forwarding to add_numbers:\n";
    int sum = call_and_log(add_numbers, 10, 20);
    std::cout << "Result: " << sum << "\n";
    
    std::cout << "\n2. Forwarding to concatenate_strings:\n";
    std::string str1 = "Hello";
    std::string result = call_and_log(concatenate_strings, str1, std::string(" World"));
    std::cout << "Result: " << result << "\n";
    
    std::cout << "\n3. Forwarding to lambda:\n";
    auto lambda = [](int x, int y) {
        std::cout << "Lambda called with " << x << ", " << y << "\n";
        return x * y;
    };
    
    int product = call_and_log(lambda, 5, 6);
    std::cout << "Result: " << product << "\n";
}

int main() {
    demonstrate_perfect_forwarding();
    demonstrate_function_forwarding();
    
    return 0;
}
```

**Learning Goals**:
- Universal reference syntax (T&&)
- std::forward usage
- Preserving value categories
- Perfect forwarding in factory functions

---

## Problem Set 2: std::variant and Type-Safe Programming (60 minutes)

### Problem 2.1: Basic std::variant Usage (20 minutes)

**Background**: Use std::variant for type-safe discriminated unions, similar to Python's Union types or algebraic data types.

**Task**: Create and manipulate variant types with different alternatives.

**Requirements**:
1. Create variants with different types
2. Check which type is currently stored
3. Access values safely using std::get and std::get_if
4. Handle variant exceptions

**Starter Code**:
```cpp
#include <iostream>
#include <variant>
#include <string>
#include <vector>

// TODO: Define a variant type for different data formats
using DataValue = std::variant<int, double, std::string>;

// TODO: Define a variant for different message types
struct TextMessage {
    std::string content;
    std::string sender;
};

struct ImageMessage {
    std::string filename;
    size_t file_size;
};

struct AudioMessage {
    std::string filename;
    double duration_seconds;
};

using Message = std::variant<TextMessage, ImageMessage, AudioMessage>;

class DataProcessor {
private:
    std::vector<DataValue> data_;
    
public:
    void add_data(const DataValue& value) {
        data_.push_back(value);
    }
    
    // TODO: Process data based on type
    void process_all_data() {
        std::cout << "Processing " << data_.size() << " data items:\n";
        
        for (size_t i = 0; i < data_.size(); ++i) {
            std::cout << "Item " << i << ": ";
            process_single_item(data_[i]);
        }
    }
    
private:
    void process_single_item(const DataValue& value) {
        // TODO: Check which type is stored using index()
        std::cout << "Type index: " << value.index() << ", ";
        
        // TODO: Use std::get_if for safe access
        if (auto* int_ptr = std::get_if<int>(&value)) {
            std::cout << "Integer: " << *int_ptr << " (squared: " << (*int_ptr * *int_ptr) << ")";
        } else if (auto* double_ptr = std::get_if<double>(&value)) {
            std::cout << "Double: " << *double_ptr << " (sqrt: " << std::sqrt(*double_ptr) << ")";
        } else if (auto* string_ptr = std::get_if<std::string>(&value)) {
            std::cout << "String: \"" << *string_ptr << "\" (length: " << string_ptr->length() << ")";
        }
        std::cout << "\n";
    }
};

void demonstrate_basic_variant_usage() {
    std::cout << "=== Basic Variant Usage ===\n";
    
    DataProcessor processor;
    
    // TODO: Add different types of data
    processor.add_data(42);
    processor.add_data(3.14159);
    processor.add_data(std::string("Hello, Variant!"));
    processor.add_data(-17);
    processor.add_data(2.71828);
    
    processor.process_all_data();
}

void demonstrate_variant_exceptions() {
    std::cout << "\n=== Variant Exception Handling ===\n";
    
    DataValue value = 42;
    
    try {
        // TODO: Safe access using std::get
        int int_value = std::get<int>(value);
        std::cout << "Successfully got int: " << int_value << "\n";
        
        // TODO: This will throw std::bad_variant_access
        double double_value = std::get<double>(value);
        std::cout << "Got double: " << double_value << "\n";
        
    } catch (const std::bad_variant_access& e) {
        std::cout << "Caught bad_variant_access: " << e.what() << "\n";
    }
    
    // TODO: Safe alternative using std::get_if
    std::cout << "Using std::get_if:\n";
    if (auto* int_ptr = std::get_if<int>(&value)) {
        std::cout << "Contains int: " << *int_ptr << "\n";
    }
    if (auto* double_ptr = std::get_if<double>(&value)) {
        std::cout << "Contains double: " << *double_ptr << "\n";
    } else {
        std::cout << "Does not contain double\n";
    }
}

void demonstrate_message_variants() {
    std::cout << "\n=== Message Variant Demo ===\n";
    
    std::vector<Message> messages;
    
    // TODO: Create different message types
    messages.emplace_back(TextMessage{"Hello, World!", "Alice"});
    messages.emplace_back(ImageMessage{"photo.jpg", 1024768});
    messages.emplace_back(AudioMessage{"song.mp3", 180.5});
    messages.emplace_back(TextMessage{"How are you?", "Bob"});
    
    // TODO: Process messages based on type
    for (size_t i = 0; i < messages.size(); ++i) {
        std::cout << "Message " << i << ": ";
        
        if (auto* text = std::get_if<TextMessage>(&messages[i])) {
            std::cout << "Text from " << text->sender << ": \"" << text->content << "\"";
        } else if (auto* image = std::get_if<ImageMessage>(&messages[i])) {
            std::cout << "Image: " << image->filename << " (" << image->file_size << " bytes)";
        } else if (auto* audio = std::get_if<AudioMessage>(&messages[i])) {
            std::cout << "Audio: " << audio->filename << " (" << audio->duration_seconds << " seconds)";
        }
        std::cout << "\n";
    }
}

int main() {
    demonstrate_basic_variant_usage();
    demonstrate_variant_exceptions();
    demonstrate_message_variants();
    
    return 0;
}
```

**Learning Goals**:
- variant type definition and initialization
- Type checking with index() and holds_alternative()
- Safe access with std::get_if vs std::get
- Exception handling with variants

---

### Problem 2.2: std::visit and Pattern Matching (25 minutes)

**Background**: Use std::visit for type-safe pattern matching on variants, similar to match statements in functional languages.

**Task**: Implement visitors that handle all variant alternatives.

**Requirements**:
1. Create function object visitors
2. Use lambda visitors with std::visit
3. Implement generic visitors using if constexpr
4. Handle return values from visitors

**Starter Code**:
```cpp
#include <iostream>
#include <variant>
#include <string>
#include <vector>
#include <type_traits>

// TODO: Define variant types for mathematical expressions
struct Number {
    double value;
};

struct Addition {
    std::variant<Number, Addition, Multiplication>* left;
    std::variant<Number, Addition, Multiplication>* right;
};

struct Multiplication {
    std::variant<Number, Addition, Multiplication>* left; 
    std::variant<Number, Addition, Multiplication>* right;
};

using Expression = std::variant<Number, Addition, Multiplication>;

// TODO: Visitor function object for printing
struct PrintVisitor {
    void operator()(const Number& n) const {
        std::cout << n.value;
    }
    
    void operator()(const Addition& add) const {
        std::cout << "(";
        std::visit(*this, *add.left);
        std::cout << " + ";
        std::visit(*this, *add.right);
        std::cout << ")";
    }
    
    void operator()(const Multiplication& mul) const {
        std::cout << "(";
        std::visit(*this, *mul.left);
        std::cout << " * ";
        std::visit(*this, *mul.right);
        std::cout << ")";
    }
};

// TODO: Visitor function object for evaluation
struct EvalVisitor {
    double operator()(const Number& n) const {
        return n.value;
    }
    
    double operator()(const Addition& add) const {
        return std::visit(*this, *add.left) + std::visit(*this, *add.right);
    }
    
    double operator()(const Multiplication& mul) const {
        return std::visit(*this, *mul.left) * std::visit(*this, *mul.right);
    }
};

// TODO: Define simpler variant for demonstration
using Value = std::variant<int, double, std::string, bool>;

void demonstrate_lambda_visitors() {
    std::cout << "=== Lambda Visitors Demo ===\n";
    
    std::vector<Value> values = {42, 3.14, std::string("hello"), true, false, -17};
    
    // TODO: Simple lambda visitor
    auto print_visitor = [](const auto& value) {
        std::cout << "Value: " << value << "\n";
    };
    
    std::cout << "Using generic lambda visitor:\n";
    for (const auto& value : values) {
        std::visit(print_visitor, value);
    }
    
    // TODO: Type-specific lambda visitor
    auto type_specific_visitor = [](const auto& value) {
        using T = std::decay_t<decltype(value)>;
        
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "Integer: " << value << " (hex: 0x" << std::hex << value << std::dec << ")\n";
        } else if constexpr (std::is_same_v<T, double>) {
            std::cout << "Double: " << value << " (scientific: " << std::scientific << value << std::fixed << ")\n";
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "String: \"" << value << "\" (reversed: ";
            for (auto it = value.rbegin(); it != value.rend(); ++it) {
                std::cout << *it;
            }
            std::cout << "\")\n";
        } else if constexpr (std::is_same_v<T, bool>) {
            std::cout << "Boolean: " << (value ? "true" : "false") << "\n";
        }
    };
    
    std::cout << "\nUsing type-specific lambda visitor:\n";
    for (const auto& value : values) {
        std::visit(type_specific_visitor, value);
    }
}

void demonstrate_returning_visitors() {
    std::cout << "\n=== Returning Visitors Demo ===\n";
    
    std::vector<Value> values = {42, 3.14, std::string("test"), true};
    
    // TODO: Visitor that returns a string representation
    auto to_string_visitor = [](const auto& value) -> std::string {
        using T = std::decay_t<decltype(value)>;
        
        if constexpr (std::is_same_v<T, int>) {
            return "int(" + std::to_string(value) + ")";
        } else if constexpr (std::is_same_v<T, double>) {
            return "double(" + std::to_string(value) + ")";
        } else if constexpr (std::is_same_v<T, std::string>) {
            return "string(\"" + value + "\")";
        } else if constexpr (std::is_same_v<T, bool>) {
            return "bool(" + (value ? std::string("true") : std::string("false")) + ")";
        }
    };
    
    std::cout << "Converting variants to strings:\n";
    for (const auto& value : values) {
        std::string result = std::visit(to_string_visitor, value);
        std::cout << "  " << result << "\n";
    }
    
    // TODO: Visitor that returns size/count
    auto size_visitor = [](const auto& value) -> size_t {
        using T = std::decay_t<decltype(value)>;
        
        if constexpr (std::is_arithmetic_v<T>) {
            return sizeof(T);  // Size in bytes for numeric types
        } else if constexpr (std::is_same_v<T, std::string>) {
            return value.length();  // Character count for strings
        } else if constexpr (std::is_same_v<T, bool>) {
            return value ? 1 : 0;  // 1 for true, 0 for false
        }
    };
    
    std::cout << "\nGetting size/count from variants:\n";
    for (const auto& value : values) {
        size_t result = std::visit(size_visitor, value);
        std::cout << "  Size/count: " << result << "\n";
    }
}

// TODO: Complex visitor example with multiple variants
void demonstrate_multi_variant_visit() {
    std::cout << "\n=== Multi-Variant Visit Demo ===\n";
    
    using LeftType = std::variant<int, double>;
    using RightType = std::variant<std::string, bool>;
    
    std::vector<LeftType> left_values = {42, 3.14};
    std::vector<RightType> right_values = {std::string("test"), true};
    
    // TODO: Visitor that handles combinations of two variants
    auto combine_visitor = [](const auto& left, const auto& right) -> std::string {
        using LeftT = std::decay_t<decltype(left)>;
        using RightT = std::decay_t<decltype(right)>;
        
        std::string result = "Combining ";
        
        if constexpr (std::is_same_v<LeftT, int>) {
            result += "int(" + std::to_string(left) + ")";
        } else if constexpr (std::is_same_v<LeftT, double>) {
            result += "double(" + std::to_string(left) + ")";
        }
        
        result += " with ";
        
        if constexpr (std::is_same_v<RightT, std::string>) {
            result += "string(\"" + right + "\")";
        } else if constexpr (std::is_same_v<RightT, bool>) {
            result += "bool(" + (right ? std::string("true") : std::string("false")) + ")";
        }
        
        return result;
    };
    
    std::cout << "Combining variants:\n";
    for (const auto& left : left_values) {
        for (const auto& right : right_values) {
            std::string result = std::visit(combine_visitor, left, right);
            std::cout << "  " << result << "\n";
        }
    }
}

int main() {
    demonstrate_lambda_visitors();
    demonstrate_returning_visitors();
    demonstrate_multi_variant_visit();
    
    return 0;
}
```

**Learning Goals**:
- Function object visitors vs lambda visitors
- Generic visitors with if constexpr
- Returning values from visitors
- Multi-variant std::visit

---

### Problem 2.3: Advanced Variant Patterns (15 minutes)

**Background**: Implement advanced patterns using variants for state machines and error handling.

**Task**: Create a simple state machine and error handling system using variants.

**Requirements**:
1. Implement a state machine using variants
2. Create a Result<T, E> type for error handling
3. Use variants for event-driven programming
4. Handle variant assignment and modification

**Starter Code**:
```cpp
#include <iostream>
#include <variant>
#include <string>
#include <vector>

// TODO: Define states for a simple traffic light state machine
struct RedLight {
    double remaining_time;
};

struct YellowLight {
    double remaining_time;
};

struct GreenLight {
    double remaining_time;
};

using TrafficLightState = std::variant<RedLight, YellowLight, GreenLight>;

// TODO: Define events
struct TimerExpired {};
struct EmergencyStop {};
struct Reset {};

using Event = std::variant<TimerExpired, EmergencyStop, Reset>;

class TrafficLight {
private:
    TrafficLightState current_state_;
    
public:
    TrafficLight() : current_state_(RedLight{30.0}) {}
    
    // TODO: Handle events and transition states
    void handle_event(const Event& event) {
        std::cout << "Current state: ";
        print_current_state();
        
        std::cout << "Processing event: ";
        std::visit([](const auto& e) {
            using T = std::decay_t<decltype(e)>;
            if constexpr (std::is_same_v<T, TimerExpired>) {
                std::cout << "TimerExpired";
            } else if constexpr (std::is_same_v<T, EmergencyStop>) {
                std::cout << "EmergencyStop";
            } else if constexpr (std::is_same_v<T, Reset>) {
                std::cout << "Reset";
            }
        }, event);
        std::cout << "\n";
        
        // TODO: Transition based on current state and event
        std::visit([this](const auto& current_state, const auto& event) {
            this->transition(current_state, event);
        }, current_state_, event);
        
        std::cout << "New state: ";
        print_current_state();
        std::cout << "\n";
    }
    
private:
    template<typename State, typename Event>
    void transition(const State& state, const Event& event) {
        using StateT = std::decay_t<decltype(state)>;
        using EventT = std::decay_t<decltype(event)>;
        
        // TODO: Handle emergency stop from any state
        if constexpr (std::is_same_v<EventT, EmergencyStop>) {
            current_state_ = RedLight{999.0}; // Long red for emergency
            return;
        }
        
        // TODO: Handle reset from any state
        if constexpr (std::is_same_v<EventT, Reset>) {
            current_state_ = RedLight{30.0};
            return;
        }
        
        // TODO: Handle timer expiration based on current state
        if constexpr (std::is_same_v<EventT, TimerExpired>) {
            if constexpr (std::is_same_v<StateT, RedLight>) {
                current_state_ = GreenLight{45.0};
            } else if constexpr (std::is_same_v<StateT, GreenLight>) {
                current_state_ = YellowLight{5.0};
            } else if constexpr (std::is_same_v<StateT, YellowLight>) {
                current_state_ = RedLight{30.0};
            }
        }
    }
    
    void print_current_state() const {
        std::visit([](const auto& state) {
            using T = std::decay_t<decltype(state)>;
            if constexpr (std::is_same_v<T, RedLight>) {
                std::cout << "RED (" << state.remaining_time << "s)";
            } else if constexpr (std::is_same_v<T, GreenLight>) {
                std::cout << "GREEN (" << state.remaining_time << "s)";
            } else if constexpr (std::is_same_v<T, YellowLight>) {
                std::cout << "YELLOW (" << state.remaining_time << "s)";
            }
        }, current_state_);
    }
};

// TODO: Result type for error handling
template<typename T, typename E>
using Result = std::variant<T, E>;

struct Success {
    double value;
};

struct Error {
    std::string message;
    int code;
};

// TODO: Functions that return Result types
Result<Success, Error> safe_divide(double a, double b) {
    if (b == 0.0) {
        return Error{"Division by zero", 1001};
    }
    return Success{a / b};
}

Result<Success, Error> safe_sqrt(double value) {
    if (value < 0.0) {
        return Error{"Cannot take square root of negative number", 1002};
    }
    return Success{std::sqrt(value)};
}

void demonstrate_state_machine() {
    std::cout << "=== State Machine Demo ===\n";
    
    TrafficLight light;
    
    std::vector<Event> events = {
        TimerExpired{},
        TimerExpired{},
        EmergencyStop{},
        Reset{},
        TimerExpired{}
    };
    
    for (const auto& event : events) {
        light.handle_event(event);
    }
}

void demonstrate_result_pattern() {
    std::cout << "\n=== Result Pattern Demo ===\n";
    
    std::vector<std::pair<double, double>> test_cases = {
        {10.0, 2.0},
        {15.0, 0.0},  // Division by zero
        {25.0, 5.0}
    };
    
    for (const auto& [a, b] : test_cases) {
        std::cout << "safe_divide(" << a << ", " << b << "): ";
        
        auto result = safe_divide(a, b);
        
        std::visit([](const auto& value) {
            using T = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<T, Success>) {
                std::cout << "Success: " << value.value;
            } else if constexpr (std::is_same_v<T, Error>) {
                std::cout << "Error: " << value.message << " (code: " << value.code << ")";
            }
        }, result);
        
        std::cout << "\n";
    }
    
    // TODO: Chain operations
    std::cout << "\nChaining operations:\n";
    std::vector<double> sqrt_inputs = {16.0, -4.0, 25.0};
    
    for (double input : sqrt_inputs) {
        std::cout << "safe_sqrt(" << input << "): ";
        
        auto result = safe_sqrt(input);
        std::visit([](const auto& value) {
            using T = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<T, Success>) {
                std::cout << "Success: " << value.value;
            } else if constexpr (std::is_same_v<T, Error>) {
                std::cout << "Error: " << value.message << " (code: " << value.code << ")";
            }
        }, result);
        
        std::cout << "\n";
    }
}

int main() {
    demonstrate_state_machine();
    demonstrate_result_pattern();
    
    return 0;
}
```

**Learning Goals**:
- State machine implementation with variants
- Event-driven programming patterns
- Error handling with Result types
- Complex variant transitions

---

## Problem Set 3: std::any and Advanced Utilities (30 minutes)

### Problem 3.1: std::any Fundamentals (15 minutes)

**Background**: Use std::any for type-erased storage when types are not known at compile time.

**Task**: Implement a heterogeneous container using std::any.

**Requirements**:
1. Store different types in std::any
2. Use any_cast for type-safe retrieval
3. Handle any_cast exceptions
4. Implement type checking with type()

**Starter Code**:
```cpp
#include <iostream>
#include <any>
#include <vector>
#include <string>
#include <typeinfo>
#include <map>

class AnyContainer {
private:
    std::vector<std::any> items_;
    
public:
    // TODO: Add method to store any type
    template<typename T>
    void add_item(T&& value) {
        items_.emplace_back(std::forward<T>(value));
        std::cout << "Added item of type: " << typeid(T).name() << "\n";
    }
    
    // TODO: Get item by index with type checking
    template<typename T>
    std::optional<T> get_item(size_t index) const {
        if (index >= items_.size()) {
            return std::nullopt;
        }
        
        try {
            return std::any_cast<T>(items_[index]);
        } catch (const std::bad_any_cast&) {
            return std::nullopt;
        }
    }
    
    // TODO: Check if item at index is of specific type
    template<typename T>
    bool is_type(size_t index) const {
        if (index >= items_.size()) {
            return false;
        }
        
        return items_[index].type() == typeid(T);
    }
    
    // TODO: Get type information for item
    std::string get_type_name(size_t index) const {
        if (index >= items_.size()) {
            return "invalid_index";
        }
        
        if (!items_[index].has_value()) {
            return "empty";
        }
        
        return items_[index].type().name();
    }
    
    size_t size() const { return items_.size(); }
    
    // TODO: Print all items (requires knowing possible types)
    void print_all() const {
        std::cout << "Container contents (" << items_.size() << " items):\n";
        
        for (size_t i = 0; i < items_.size(); ++i) {
            std::cout << "  [" << i << "] Type: " << get_type_name(i) << ", Value: ";
            
            // TODO: Try common types
            if (auto value = get_item<int>(i)) {
                std::cout << *value;
            } else if (auto value = get_item<double>(i)) {
                std::cout << *value;
            } else if (auto value = get_item<std::string>(i)) {
                std::cout << "\"" << *value << "\"";
            } else if (auto value = get_item<bool>(i)) {
                std::cout << (*value ? "true" : "false");
            } else {
                std::cout << "<unknown type>";
            }
            
            std::cout << "\n";
        }
    }
};

void demonstrate_any_basics() {
    std::cout << "=== std::any Basics Demo ===\n";
    
    AnyContainer container;
    
    // TODO: Add various types
    container.add_item(42);
    container.add_item(3.14159);
    container.add_item(std::string("Hello, any!"));
    container.add_item(true);
    container.add_item(std::vector<int>{1, 2, 3, 4, 5});
    
    container.print_all();
    
    // TODO: Test type checking
    std::cout << "\nType checking:\n";
    std::cout << "Item 0 is int: " << container.is_type<int>(0) << "\n";
    std::cout << "Item 0 is double: " << container.is_type<double>(0) << "\n";
    std::cout << "Item 1 is double: " << container.is_type<double>(1) << "\n";
    
    // TODO: Test safe retrieval
    std::cout << "\nSafe retrieval:\n";
    if (auto value = container.get_item<int>(0)) {
        std::cout << "Got int from index 0: " << *value << "\n";
    }
    
    if (auto value = container.get_item<std::string>(0)) {
        std::cout << "Got string from index 0: " << *value << "\n";
    } else {
        std::cout << "Index 0 does not contain a string\n";
    }
}

void demonstrate_any_exceptions() {
    std::cout << "\n=== std::any Exception Handling ===\n";
    
    std::any value = 42;
    
    try {
        // TODO: Successful cast
        int int_value = std::any_cast<int>(value);
        std::cout << "Successfully cast to int: " << int_value << "\n";
        
        // TODO: This will throw
        double double_value = std::any_cast<double>(value);
        std::cout << "Successfully cast to double: " << double_value << "\n";
        
    } catch (const std::bad_any_cast& e) {
        std::cout << "Caught bad_any_cast: " << e.what() << "\n";
    }
    
    // TODO: Safe alternative using pointers
    std::cout << "Using pointer-based any_cast:\n";
    if (int* int_ptr = std::any_cast<int>(&value)) {
        std::cout << "Contains int: " << *int_ptr << "\n";
    }
    if (double* double_ptr = std::any_cast<double>(&value)) {
        std::cout << "Contains double: " << *double_ptr << "\n";
    } else {
        std::cout << "Does not contain double\n";
    }
}

int main() {
    demonstrate_any_basics();
    demonstrate_any_exceptions();
    
    return 0;
}
```

**Learning Goals**:
- std::any storage and retrieval
- Type checking with type() and typeid
- Safe casting with pointer-based any_cast
- Exception handling with bad_any_cast

---

### Problem 3.2: Utility Functions Integration (15 minutes)

**Background**: Use various C++ utility functions like std::exchange, std::swap, and structured bindings.

**Task**: Implement examples using these utility functions effectively.

**Requirements**:
1. Use std::exchange for atomic value replacement
2. Demonstrate std::swap with custom types
3. Use structured bindings with various types
4. Combine utilities in practical scenarios

**Starter Code**:
```cpp
#include <iostream>
#include <utility>
#include <string>
#include <map>
#include <tuple>
#include <vector>

class Resource {
private:
    std::string name_;
    std::vector<int> data_;
    
public:
    Resource(const std::string& name, std::vector<int> data) 
        : name_(name), data_(std::move(data)) {
        std::cout << "Resource '" << name_ << "' created with " << data_.size() << " elements\n";
    }
    
    Resource(const Resource& other) : name_(other.name_ + "_copy"), data_(other.data_) {
        std::cout << "Resource '" << name_ << "' copied\n";
    }
    
    Resource(Resource&& other) noexcept 
        : name_(std::exchange(other.name_, "moved")), 
          data_(std::exchange(other.data_, {})) {
        std::cout << "Resource '" << name_ << "' moved\n";
    }
    
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            name_ = other.name_ + "_assigned";
            data_ = other.data_;
            std::cout << "Resource '" << name_ << "' copy assigned\n";
        }
        return *this;
    }
    
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            name_ = std::exchange(other.name_, "moved");
            data_ = std::exchange(other.data_, {});
            std::cout << "Resource '" << name_ << "' move assigned\n";
        }
        return *this;
    }
    
    ~Resource() {
        std::cout << "Resource '" << name_ << "' destroyed\n";
    }
    
    const std::string& name() const { return name_; }
    size_t data_size() const { return data_.size(); }
    
    void display() const {
        std::cout << "Resource '" << name_ << "' has " << data_.size() << " elements";
        if (!data_.empty()) {
            std::cout << " [" << data_[0] << "..." << data_.back() << "]";
        }
        std::cout << "\n";
    }
};

// TODO: Custom swap for Resource (if needed for optimization)
void swap(Resource& a, Resource& b) noexcept {
    std::cout << "Custom swap between '" << a.name() << "' and '" << b.name() << "'\n";
    
    using std::swap;  // Enable ADL
    swap(a.name_, b.name_);
    swap(a.data_, b.data_);
}

void demonstrate_std_exchange() {
    std::cout << "=== std::exchange Demo ===\n";
    
    std::string original = "Hello";
    std::string replacement = "World";
    
    std::cout << "Before exchange - original: '" << original << "', replacement: '" << replacement << "'\n";
    
    // TODO: Use std::exchange to atomically replace and get old value
    std::string old_value = std::exchange(original, replacement);
    
    std::cout << "After exchange - original: '" << original << "', old_value: '" << old_value << "'\n";
    
    // TODO: Common pattern in move operations
    Resource resource1("Original", {1, 2, 3, 4, 5});
    resource1.display();
    
    std::cout << "\nUsing std::exchange in move constructor pattern:\n";
    Resource resource2 = std::move(resource1);
    
    std::cout << "After move:\n";
    resource1.display();  // Should show moved-from state
    resource2.display();  // Should have original data
}

void demonstrate_structured_bindings() {
    std::cout << "\n=== Structured Bindings Demo ===\n";
    
    // TODO: With std::pair
    std::pair<std::string, int> name_age = {"Alice", 25};
    auto [name, age] = name_age;
    std::cout << "Name: " << name << ", Age: " << age << "\n";
    
    // TODO: With std::tuple
    std::tuple<std::string, double, bool> student_data = {"Bob", 3.75, true};
    auto [student_name, gpa, is_enrolled] = student_data;
    std::cout << "Student: " << student_name << ", GPA: " << gpa 
              << ", Enrolled: " << (is_enrolled ? "Yes" : "No") << "\n";
    
    // TODO: With map iteration
    std::map<std::string, int> scores = {
        {"Alice", 95},
        {"Bob", 87},
        {"Charlie", 92}
    };
    
    std::cout << "\nScores using structured bindings:\n";
    for (const auto& [student, score] : scores) {
        std::cout << "  " << student << ": " << score << "\n";
    }
    
    // TODO: With arrays
    int coordinates[3] = {10, 20, 30};
    auto [x, y, z] = coordinates;
    std::cout << "\nCoordinates: x=" << x << ", y=" << y << ", z=" << z << "\n";
}

// TODO: Function returning multiple values
std::tuple<bool, std::string, int> process_data(const std::string& input) {
    if (input.empty()) {
        return {false, "Empty input", -1};
    }
    
    if (input.length() < 3) {
        return {false, "Too short", static_cast<int>(input.length())};
    }
    
    return {true, "Processed: " + input, static_cast<int>(input.length())};
}

void demonstrate_multiple_return_values() {
    std::cout << "\n=== Multiple Return Values Demo ===\n";
    
    std::vector<std::string> test_inputs = {"", "Hi", "Hello, World!"};
    
    for (const auto& input : test_inputs) {
        std::cout << "Processing input: \"" << input << "\"\n";
        
        // TODO: Use structured bindings with function return
        auto [success, message, length] = process_data(input);
        
        std::cout << "  Success: " << (success ? "Yes" : "No") 
                  << ", Message: \"" << message << "\", Length: " << length << "\n\n";
    }
}

void demonstrate_swap_operations() {
    std::cout << "=== Swap Operations Demo ===\n";
    
    Resource res1("FirstResource", {1, 2, 3});
    Resource res2("SecondResource", {4, 5, 6, 7, 8});
    
    std::cout << "Before swap:\n";
    res1.display();
    res2.display();
    
    std::cout << "\nPerforming swap:\n";
    std::swap(res1, res2);  // Will use our custom swap if available
    
    std::cout << "\nAfter swap:\n";
    res1.display();
    res2.display();
}

int main() {
    demonstrate_std_exchange();
    demonstrate_structured_bindings();
    demonstrate_multiple_return_values();
    demonstrate_swap_operations();
    
    return 0;
}
```

**Learning Goals**:
- std::exchange for atomic replacement
- Structured bindings with various types
- Custom swap implementations
- Multiple return values with tuples

---

## Submission Guidelines

### What to Submit

1. **Source code files** for all problems with clear comments
2. **Compilation and execution output** showing your programs working
3. **Brief reflection** (2-3 paragraphs) on modern C++ utility features and their benefits

### File Organization
```
chapter12_solutions/
├── problem_set_1/
│   ├── problem_1_1_move_semantics.cpp
│   ├── problem_1_2_optional_fundamentals.cpp
│   └── problem_1_3_perfect_forwarding.cpp
├── problem_set_2/
│   ├── problem_2_1_variant_basics.cpp
│   ├── problem_2_2_visit_pattern_matching.cpp
│   └── problem_2_3_advanced_variant_patterns.cpp
├── problem_set_3/
│   ├── problem_3_1_any_fundamentals.cpp
│   └── problem_3_2_utility_functions.cpp
└── README.md (with compilation notes and reflection)
```

### Evaluation Criteria

1. **Correctness** (40%): Programs compile and work as specified
2. **Modern C++ Usage** (25%): Proper use of utilities, move semantics, and type safety
3. **Code Quality** (20%): Clean, readable, well-organized code  
4. **Best Practices** (15%): Following modern C++ idioms and performance practices

### Time Management Tips

- **Problem Set 1**: Focus on understanding when moves happen automatically vs explicitly
- **Problem Set 2**: Practice with std::visit patterns - they're very powerful
- **Problem Set 3**: Understand when std::any is appropriate vs alternatives

### Common Pitfalls to Avoid

1. **Move Semantics**: Don't use std::move unnecessarily or on return values
2. **Optional**: Remember to check has_value() before calling value()
3. **Variant**: Handle all alternatives in std::visit to avoid compilation errors
4. **Any**: Understand the performance cost of type erasure
5. **Perfect Forwarding**: Use std::forward only in templates with universal references

### Getting Help

- Refer to `quick-help.md` for syntax reminders
- Check solution files if stuck on template syntax
- Focus on understanding when each utility is most appropriate

---

## Extension Challenges (Optional)

For students who finish early:

1. **Monadic Operations**: Implement monadic operations for std::optional
2. **Recursive Variants**: Create recursive data structures with std::variant
3. **Custom Utilities**: Implement your own utility functions similar to std::exchange
4. **Performance Analysis**: Compare std::any vs std::variant vs templates

## Success Criteria

You've mastered Chapter 12 utility concepts when you can:
- Use move semantics appropriately for performance optimization
- Choose between std::optional, std::variant, and std::any based on use case
- Implement type-safe patterns using modern C++ utilities
- Apply perfect forwarding in generic code
- Use std::visit effectively for variant pattern matching

Remember: These utilities enable expressive, type-safe code while maintaining performance. Choose the right tool for each scenario!