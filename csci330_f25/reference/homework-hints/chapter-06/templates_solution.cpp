#include <iostream>
#include <string>
#include <memory>

// Basic function template
template<typename T>
T absolute_value(T value) {
    return value < 0 ? -value : value;
}

// Multiple template parameters
template<typename T1, typename T2>
auto safe_divide(T1 numerator, T2 denominator) -> decltype(numerator/denominator) {
    if (denominator == 0) {
        return 0;
    }
    return numerator / denominator;
}

// Template swap function
template<typename T>
void swap_values(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Template class: Pair
template<typename T>
class Pair {
private:
    T first_value;
    T second_value;

public:
    Pair(T first, T second) : first_value(first), second_value(second) {}

    T first() const { return first_value; }
    T second() const { return second_value; }

    void set_first(const T& value) { first_value = value; }
    void set_second(const T& value) { second_value = value; }

    void swap() {
        T temp = first_value;
        first_value = second_value;
        second_value = temp;
    }
};

// Template class with dynamic storage
template<typename T>
class SimpleArray {
private:
    std::unique_ptr<T[]> data;
    size_t array_size;

public:
    SimpleArray(size_t size) : array_size(size) {
        data = std::make_unique<T[]>(size);
    }

    void set(size_t index, const T& value) {
        if (index < array_size) {
            data[index] = value;
        } else {
            std::cout << "Error: Index " << index << " out of bounds\n";
        }
    }

    T get(size_t index) const {
        if (index < array_size) {
            return data[index];
        } else {
            std::cout << "Error: Index " << index << " out of bounds\n";
            return T{}; // Default value
        }
    }

    size_t size() const { return array_size; }
};

// Template specialization example
template<typename T>
class Printer {
public:
    static void print(const T& value) {
        std::cout << "Value: " << value << std::endl;
    }
};

// Specialization for bool
template<>
class Printer<bool> {
public:
    static void print(const bool& value) {
        std::cout << "Boolean: " << (value ? "true" : "false") << std::endl;
    }
};

// Specialization for string
template<>
class Printer<std::string> {
public:
    static void print(const std::string& value) {
        std::cout << "Text: " << value << std::endl;
    }
};

// Fixed template example
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

    T getValue() const {
        return value;
    }
};

int main() {
    std::cout << "=== Function Template Examples ===\n";

    // Test absolute_value
    std::cout << "absolute_value(-5) = " << absolute_value(-5) << std::endl;
    std::cout << "absolute_value(-3.14) = " << absolute_value(-3.14) << std::endl;
    std::cout << "absolute_value(42) = " << absolute_value(42) << std::endl;

    // Test safe_divide
    std::cout << "10 / 2 = " << safe_divide(10, 2) << std::endl;
    std::cout << "10.5 / 2 = " << safe_divide(10.5, 2) << std::endl;
    std::cout << "10 / 0 = " << safe_divide(10, 0) << " (division by zero)" << std::endl;

    // Test swap
    int a = 5, b = 10;
    std::cout << "Before swap: a=" << a << ", b=" << b << std::endl;
    swap_values(a, b);
    std::cout << "After swap: a=" << a << ", b=" << b << std::endl;

    std::cout << "\n=== Template Class Examples ===\n";

    // Test Pair
    Pair<int> numbers(10, 20);
    std::cout << "First: " << numbers.first() << ", Second: " << numbers.second() << std::endl;
    numbers.swap();
    std::cout << "After swap - First: " << numbers.first() << ", Second: " << numbers.second() << std::endl;

    Pair<std::string> words("hello", "world");
    std::cout << words.first() << " " << words.second() << std::endl;

    // Test SimpleArray
    SimpleArray<int> int_array(5);
    int_array.set(0, 100);
    int_array.set(1, 200);
    std::cout << "int_array[0] = " << int_array.get(0) << std::endl;
    std::cout << "Size: " << int_array.size() << std::endl;

    SimpleArray<std::string> string_array(3);
    string_array.set(0, "apple");
    string_array.set(1, "banana");
    std::cout << "string_array[0] = " << string_array.get(0) << std::endl;

    std::cout << "\n=== Template Specialization Examples ===\n";

    // Test template specialization
    Printer<int>::print(42);
    Printer<bool>::print(true);
    Printer<std::string>::print("hello world");
    Printer<double>::print(3.14);

    std::cout << "\n=== Fixed Template Example ===\n";

    // Test fixed Calculator
    Calculator<int> calc(10);
    calc.add(5);
    calc.print();
    std::cout << "Final value: " << calc.getValue() << std::endl;

    return 0;
}