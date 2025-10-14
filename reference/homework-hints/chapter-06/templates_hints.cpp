#include <iostream>
#include <string>
#include <cmath>

// =============================================================================
// PROBLEM SET 1: FUNCTION TEMPLATE FUNDAMENTALS
// =============================================================================

// Problem 1.1: Basic Function Templates
// -----------------------------------------------------------------------------
// A function template allows you to write generic code that works with any type.
// The template parameter T is a placeholder for the actual type.

template<typename T>
T absolute_value(T value) {
    // For any numeric type, if value is negative, return -value
    // Otherwise return value as-is
    return (value < 0) ? -value : value;
}

// Problem 1.2: Multiple Template Parameters
// -----------------------------------------------------------------------------
// You can have multiple template parameters with different types.
// The 'auto' return type (C++11) and trailing return type let the compiler
// deduce the return type from the expression.

template<typename T1, typename T2>
auto safe_divide(T1 numerator, T2 denominator) -> decltype(numerator/denominator) {
    // Check for zero denominator to avoid division by zero
    if (denominator == 0) {
        return 0;  // Return 0 as a safe default
    }
    return numerator / denominator;
}

// Problem 1.3: Template Argument Deduction
// -----------------------------------------------------------------------------
// The compiler can automatically deduce template arguments from function parameters.
// Using references allows us to modify the original variables.

template<typename T>
void swap_values(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// =============================================================================
// PROBLEM SET 2: TEMPLATE CLASSES
// =============================================================================

// Problem 2.1: Simple Template Container - Pair Class
// -----------------------------------------------------------------------------
// A template class that holds two values of the same type.
// This is similar to std::pair but simpler for learning purposes.

template<typename T>
class Pair {
private:
    T first_value;
    T second_value;

public:
    // Constructor initializes both values
    Pair(T first, T second) : first_value(first), second_value(second) {}

    // Getter methods
    T first() const {
        return first_value;
    }

    T second() const {
        return second_value;
    }

    // Setter methods
    void set_first(T value) {
        first_value = value;
    }

    void set_second(T value) {
        second_value = value;
    }

    // Swap the two values
    void swap() {
        T temp = first_value;
        first_value = second_value;
        second_value = temp;
    }

    // Display both values (works if T supports << operator)
    void display() const {
        std::cout << "(" << first_value << ", " << second_value << ")";
    }
};

// Problem 2.2: Template Container with Dynamic Storage
// -----------------------------------------------------------------------------
// A template class that manages a dynamic array of any type.
// This demonstrates memory management with templates.

template<typename T>
class SimpleArray {
private:
    T* data;              // Pointer to dynamically allocated array
    size_t array_size;    // Size of the array

public:
    // Constructor allocates memory
    SimpleArray(size_t size) : array_size(size) {
        data = new T[size];  // Allocate array on heap
        std::cout << "[SimpleArray] Created array of size " << size << "\n";
    }

    // Destructor frees memory - CRITICAL to prevent memory leaks!
    ~SimpleArray() {
        delete[] data;  // Use delete[] for arrays
        std::cout << "[SimpleArray] Destroyed array of size " << array_size << "\n";
    }

    // Get value at index (with bounds checking)
    T get(size_t index) const {
        if (index >= array_size) {
            std::cout << "[Error] Index " << index << " out of bounds!\n";
            return T();  // Return default-constructed value
        }
        return data[index];
    }

    // Set value at index (with bounds checking)
    void set(size_t index, const T& value) {
        if (index >= array_size) {
            std::cout << "[Error] Index " << index << " out of bounds!\n";
            return;
        }
        data[index] = value;
    }

    // Get the size of the array
    size_t size() const {
        return array_size;
    }

    // Display all elements (works if T supports << operator)
    void display() const {
        std::cout << "[";
        for (size_t i = 0; i < array_size; ++i) {
            std::cout << data[i];
            if (i < array_size - 1) std::cout << ", ";
        }
        std::cout << "]";
    }
};

// =============================================================================
// PROBLEM SET 3: TEMPLATE SPECIALIZATION AND DEBUGGING
// =============================================================================

// Problem 3.1: Template Specialization
// -----------------------------------------------------------------------------
// General template - works for most types
template<typename T>
class Printer {
public:
    static void print(const T& value) {
        std::cout << "Value: " << value << std::endl;
    }
};

// Template specialization for bool
// This version is used specifically when T is bool
template<>
class Printer<bool> {
public:
    static void print(const bool& value) {
        std::cout << "Boolean: " << (value ? "true" : "false") << std::endl;
    }
};

// Template specialization for string
// This version is used specifically when T is std::string
template<>
class Printer<std::string> {
public:
    static void print(const std::string& value) {
        std::cout << "Text: " << value << std::endl;
    }
};

// Problem 3.2: Debugging Template Errors
// -----------------------------------------------------------------------------
// CORRECTED VERSION - Shows how to properly define template methods outside class

template<typename T>
class Calculator {
private:
    T value;

public:
    Calculator(T initial) : value(initial) {}

    void add(T amount) {
        value += amount;
    }

    void print() const {
        std::cout << "Result: " << value << std::endl;
    }

    // Method declaration inside class
    T getValue() const;
};

// CORRECT: Template method definition outside class needs full template syntax
// This is the proper way to define a template member function outside the class
template<typename T>
T Calculator<T>::getValue() const {
    return value;
}

// =============================================================================
// ADVANCED EXAMPLES: Additional Useful Templates
// =============================================================================

// Example: Function template with constrained operations
// This function only works with types that support arithmetic operations
template<typename T>
T average(T a, T b) {
    return (a + b) / 2;  // Only works if T supports + and /
}

// Example: Template class with multiple type parameters
template<typename KeyType, typename ValueType>
class KeyValuePair {
private:
    KeyType key;
    ValueType value;

public:
    KeyValuePair(KeyType k, ValueType v) : key(k), value(v) {}

    KeyType getKey() const { return key; }
    ValueType getValue() const { return value; }

    void display() const {
        std::cout << key << " => " << value;
    }
};

// Example: Template function that works with arrays
template<typename T, size_t N>
void print_array(const T (&arr)[N]) {
    std::cout << "[";
    for (size_t i = 0; i < N; ++i) {
        std::cout << arr[i];
        if (i < N - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

// =============================================================================
// DEMONSTRATION FUNCTIONS
// =============================================================================

void demo_function_templates() {
    std::cout << "=== FUNCTION TEMPLATES DEMO ===\n\n";

    // Problem 1.1: absolute_value
    std::cout << "1.1 Basic Function Templates:\n";
    std::cout << "absolute_value(-5) = " << absolute_value(-5) << "\n";
    std::cout << "absolute_value(-3.14) = " << absolute_value(-3.14) << "\n";
    std::cout << "absolute_value(42) = " << absolute_value(42) << "\n\n";

    // Problem 1.2: safe_divide
    std::cout << "1.2 Multiple Template Parameters:\n";
    std::cout << "10 / 2 = " << safe_divide(10, 2) << "\n";
    std::cout << "10.5 / 2 = " << safe_divide(10.5, 2) << "\n";
    std::cout << "10 / 0 = " << safe_divide(10, 0) << " (division by zero)\n";
    std::cout << "15.5 / 3.1 = " << safe_divide(15.5, 3.1) << "\n\n";

    // Problem 1.3: swap_values
    std::cout << "1.3 Template Argument Deduction:\n";
    int a = 10, b = 20;
    std::cout << "Before swap: a = " << a << ", b = " << b << "\n";
    swap_values(a, b);  // Compiler deduces T = int
    std::cout << "After swap: a = " << a << ", b = " << b << "\n";

    double x = 3.14, y = 2.71;
    std::cout << "Before swap: x = " << x << ", y = " << y << "\n";
    swap_values<double>(x, y);  // Explicit template argument (optional)
    std::cout << "After swap: x = " << x << ", y = " << y << "\n\n";
}

void demo_template_classes() {
    std::cout << "=== TEMPLATE CLASSES DEMO ===\n\n";

    // Problem 2.1: Pair class
    std::cout << "2.1 Simple Template Container (Pair):\n";
    Pair<int> numbers(10, 20);
    std::cout << "Created Pair<int>: ";
    numbers.display();
    std::cout << "\n";
    std::cout << "First: " << numbers.first() << ", Second: " << numbers.second() << "\n";

    numbers.swap();
    std::cout << "After swap: ";
    numbers.display();
    std::cout << "\n";

    Pair<std::string> words("hello", "world");
    std::cout << "Created Pair<string>: ";
    words.display();
    std::cout << "\n";

    Pair<double> coordinates(3.14, 2.71);
    std::cout << "Created Pair<double>: ";
    coordinates.display();
    std::cout << "\n\n";

    // Problem 2.2: SimpleArray class
    std::cout << "2.2 Template Container with Dynamic Storage:\n";
    {
        SimpleArray<int> numbers(5);
        numbers.set(0, 100);
        numbers.set(1, 200);
        numbers.set(2, 300);
        std::cout << "numbers[0] = " << numbers.get(0) << "\n";
        std::cout << "numbers[1] = " << numbers.get(1) << "\n";
        std::cout << "Size: " << numbers.size() << "\n";
        std::cout << "All elements: ";
        numbers.display();
        std::cout << "\n\n";

        SimpleArray<std::string> words(3);
        words.set(0, "apple");
        words.set(1, "banana");
        words.set(2, "cherry");
        std::cout << "words[0] = " << words.get(0) << "\n";
        std::cout << "All words: ";
        words.display();
        std::cout << "\n";

        // Test bounds checking
        std::cout << "Attempting out-of-bounds access:\n";
        words.get(10);  // Should print error
        words.set(10, "invalid");  // Should print error

        std::cout << "\n";
    } // Arrays destroyed here - watch destructor messages
    std::cout << "\n";
}

void demo_specialization() {
    std::cout << "=== TEMPLATE SPECIALIZATION DEMO ===\n\n";

    std::cout << "3.1 Template Specialization:\n";
    Printer<int>::print(42);
    Printer<bool>::print(true);
    Printer<bool>::print(false);
    Printer<std::string>::print("hello world");
    Printer<double>::print(3.14159);
    std::cout << "\n";
}

void demo_calculator() {
    std::cout << "=== CALCULATOR TEMPLATE DEMO ===\n\n";

    std::cout << "3.2 Corrected Template Method Definition:\n";
    Calculator<int> calc(10);
    std::cout << "Initial value: " << calc.getValue() << "\n";
    calc.add(5);
    std::cout << "After add(5): " << calc.getValue() << "\n";
    calc.print();

    Calculator<double> calc_double(3.5);
    std::cout << "Initial value: " << calc_double.getValue() << "\n";
    calc_double.add(2.5);
    std::cout << "After add(2.5): " << calc_double.getValue() << "\n";
    calc_double.print();
    std::cout << "\n";
}

void demo_advanced_templates() {
    std::cout << "=== ADVANCED TEMPLATE EXAMPLES ===\n\n";

    // Multiple type parameters
    std::cout << "KeyValuePair with different types:\n";
    KeyValuePair<std::string, int> age("Alice", 25);
    std::cout << "  ";
    age.display();
    std::cout << "\n";

    KeyValuePair<int, std::string> name(1001, "Bob Smith");
    std::cout << "  ";
    name.display();
    std::cout << "\n\n";

    // Array template with size parameter
    std::cout << "Array template with size parameter:\n";
    int numbers[] = {1, 2, 3, 4, 5};
    std::cout << "  ";
    print_array(numbers);

    double values[] = {3.14, 2.71, 1.41};
    std::cout << "  ";
    print_array(values);
    std::cout << "\n";

    // Average function
    std::cout << "Generic average function:\n";
    std::cout << "  average(10, 20) = " << average(10, 20) << "\n";
    std::cout << "  average(3.5, 6.5) = " << average(3.5, 6.5) << "\n";
    std::cout << "\n";
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  Chapter 6: Compile-Time Polymorphism - Template Hints    ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════╝\n";
    std::cout << "\n";

    demo_function_templates();
    demo_template_classes();
    demo_specialization();
    demo_calculator();
    demo_advanced_templates();

    std::cout << "═══════════════════════════════════════════════════════════\n";
    std::cout << "All demonstrations complete!\n";
    std::cout << "═══════════════════════════════════════════════════════════\n\n";

    return 0;
}

/*
=============================================================================
KEY LEARNING POINTS FOR CHAPTER 6: TEMPLATES
=============================================================================

1. FUNCTION TEMPLATES:
   - Use 'template<typename T>' or 'template<class T>' (equivalent)
   - Compiler generates specific versions for each type used
   - Template argument deduction: compiler figures out T from parameters
   - Can have multiple template parameters: template<typename T1, typename T2>

2. TEMPLATE CLASSES:
   - Entire class becomes generic and reusable
   - Must specify type when creating instances: Pair<int>, SimpleArray<string>
   - All member functions are implicitly templates
   - Great for containers and data structures

3. TEMPLATE METHOD DEFINITIONS:
   - Methods defined inside class: no special syntax needed
   - Methods defined outside class: MUST use full template syntax
     template<typename T>
     ReturnType ClassName<T>::methodName() { ... }

4. TEMPLATE SPECIALIZATION:
   - Provide different implementation for specific types
   - Syntax: template<> class ClassName<SpecificType> { ... };
   - Used when certain types need special handling
   - Example: different behavior for bool vs. other types

5. COMMON PITFALLS:
   - Forgetting template<typename T> before out-of-class definitions
   - Trying to use operations not supported by all types
   - Template code must be in header files (usually)
   - Error messages can be very long and cryptic

6. WHEN TO USE TEMPLATES:
   - When you need the same logic for multiple types
   - Building reusable containers (vector, array, pair, etc.)
   - Writing generic algorithms (sort, search, etc.)
   - Type-safe alternatives to void* pointers

7. COMPILE-TIME VS RUN-TIME:
   - Templates are resolved at COMPILE time
   - No runtime overhead (unlike virtual functions)
   - Different from runtime polymorphism (Chapter 5)
   - Code is generated for each type you use

8. BEST PRACTICES:
   - Keep templates simple and focused
   - Provide clear error messages with static_assert (advanced)
   - Document what operations T must support
   - Test with multiple types (int, double, string, custom classes)

=============================================================================
DEBUGGING TIPS:
=============================================================================

1. Template compilation errors are LONG - read from the top
2. Look for "candidate template" messages to see what went wrong
3. Check that your type T supports all operations you use (==, <, +, etc.)
4. Remember: template code must be visible to compiler (header files)
5. Use explicit template instantiation to test compilation
6. Start simple - get basic version working before adding complexity

=============================================================================
EXAMPLE COMPILATION AND TESTING:
=============================================================================

To compile this file:
  g++ -std=c++11 templates_hints.cpp -o templates_hints

Or with more warnings:
  g++ -std=c++11 -Wall -Wextra templates_hints.cpp -o templates_hints

To run:
  ./templates_hints

Expected output: Demonstrations of all template concepts with clear
explanations showing how templates work with different types.

=============================================================================
*/
