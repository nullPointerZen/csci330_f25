// HW_06: Compile-Time Polymorphism (Templates)
// Time: 2.25 hours (45 minutes per problem set)
// Topics: Function templates, class templates, specialization, type traits

#include <cstdio>
#include <iostream>
#include <typeinfo>
#include <string>
#include <cstring>

// ============================================================================
// PROBLEM SET 1: Function Templates (45 minutes)
// ============================================================================

// TODO 1: Generic min/max functions
template<typename T>
T minimum(T a, T b) {
    // TODO: Return the smaller of a and b
    return (a < b) ? a : b;
}

template<typename T>
T maximum(T a, T b) {
    // TODO: Return the larger of a and b
    return (a > b) ? a : b;
}

// TODO 2: Generic array operations
template<typename T>
T array_sum(T array[], int size) {
    T sum = T{};  // Zero-initialize using T's default constructor
    // TODO: Sum all elements in the array
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

template<typename T>
double array_average(T array[], int size) {
    if (size == 0) return 0.0;
    // TODO: Calculate average using array_sum
    return static_cast<double>(array_sum(array, size)) / size;
}

template<typename T>
int find_element(T array[], int size, T target) {
    // TODO: Find index of target element, return -1 if not found
    for (int i = 0; i < size; i++) {
        if (array[i] == target) return i;
    }
    return -1;
}

void problem_set_1_demo() {
    printf("=== Problem Set 1: Function Templates ===\n\n");
    
    // Test with different types
    printf("Generic Min/Max Functions:\n");
    
    // TODO 3: Test with integers
    int x = 10, y = 20;
    printf("  min(%d, %d) = %d\n", x, y, minimum(x, y));
    printf("  max(%d, %d) = %d\n", x, y, maximum(x, y));
    
    // TODO 4: Test with doubles
    double a = 3.14, b = 2.71;
    printf("  min(%.2f, %.2f) = %.2f\n", a, b, minimum(a, b));
    printf("  max(%.2f, %.2f) = %.2f\n", a, b, maximum(a, b));
    
    // TODO 5: Test with characters
    char c1 = 'A', c2 = 'Z';
    printf("  min('%c', '%c') = '%c'\n", c1, c2, minimum(c1, c2));
    printf("  max('%c', '%c') = '%c'\n", c1, c2, maximum(c1, c2));
    
    // Array operations
    printf("\nGeneric Array Operations:\n");
    
    int int_array[] = {1, 2, 3, 4, 5};
    int int_size = sizeof(int_array) / sizeof(int_array[0]);
    
    printf("  Integer array: ");
    for (int i = 0; i < int_size; i++) {
        printf("%d ", int_array[i]);
    }
    printf("\n");
    printf("  Sum: %d\n", array_sum(int_array, int_size));
    printf("  Average: %.2f\n", array_average(int_array, int_size));
    printf("  Find 3: index %d\n", find_element(int_array, int_size, 3));
    printf("  Find 99: index %d\n", find_element(int_array, int_size, 99));
    
    // TODO 6: Test with double array
    double double_array[] = {1.1, 2.2, 3.3, 4.4};
    int double_size = sizeof(double_array) / sizeof(double_array[0]);
    
    printf("\n  Double array: ");
    for (int i = 0; i < double_size; i++) {
        printf("%.1f ", double_array[i]);
    }
    printf("\n");
    printf("  Sum: %.2f\n", array_sum(double_array, double_size));
    printf("  Average: %.2f\n", array_average(double_array, double_size));
    
    printf("\n");
}

// ============================================================================
// PROBLEM SET 2: Class Templates (45 minutes)
// ============================================================================

// TODO 7: Generic Pair template
template<typename T1, typename T2>
class Pair {
private:
    T1 first;
    T2 second;
    
public:
    // TODO: Constructor
    Pair(T1 f, T2 s) : first(f), second(s) {}
    
    // TODO: Getters
    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }
    
    // TODO: Setters
    void setFirst(T1 f) { first = f; }
    void setSecond(T2 s) { second = s; }
    
    void display() const {
        std::cout << "Pair(" << first << ", " << second << ")\n";
    }
};

// TODO 8: Generic Stack template
template<typename T>
class Stack {
private:
    static const int MAX_SIZE = 100;
    T data[MAX_SIZE];
    int top_index;
    
public:
    // TODO: Constructor
    Stack() : top_index(-1) {}
    
    // TODO: Push operation
    bool push(T item) {
        if (top_index >= MAX_SIZE - 1) return false;  // Stack full
        data[++top_index] = item;
        return true;
    }
    
    // TODO: Pop operation
    bool pop(T& item) {
        if (top_index < 0) return false;  // Stack empty
        item = data[top_index--];
        return true;
    }
    
    // TODO: Peek operation
    bool peek(T& item) const {
        if (top_index < 0) return false;
        item = data[top_index];
        return true;
    }
    
    // TODO: Size and empty checks
    int size() const { return top_index + 1; }
    bool empty() const { return top_index < 0; }
};

// TODO 9: Generic Container template (simple vector-like)
template<typename T>
class SimpleVector {
private:
    T* data;
    int capacity;
    int current_size;
    
public:
    // TODO: Constructor
    SimpleVector(int cap = 10) : capacity(cap), current_size(0) {
        data = new T[capacity];
    }
    
    // TODO: Destructor
    ~SimpleVector() {
        delete[] data;
    }
    
    // TODO: Add element
    void push_back(T item) {
        if (current_size < capacity) {
            data[current_size++] = item;
        }
    }
    
    // TODO: Get element
    T& operator[](int index) {
        return data[index];  // Note: No bounds checking for simplicity
    }
    
    int size() const { return current_size; }
};

void problem_set_2_demo() {
    printf("=== Problem Set 2: Class Templates ===\n\n");
    
    // Test Pair template
    printf("Generic Pair Template:\n");
    
    // TODO 10: Create different types of pairs
    Pair<int, double> int_double_pair(42, 3.14159);
    Pair<std::string, int> string_int_pair(std::string("Hello"), 100);
    
    printf("  ");
    int_double_pair.display();
    printf("  ");
    string_int_pair.display();
    
    // Test Stack template
    printf("\nGeneric Stack Template:\n");
    
    Stack<int> int_stack;
    
    // TODO 11: Test stack operations
    printf("  Pushing: 10, 20, 30\n");
    int_stack.push(10);
    int_stack.push(20);
    int_stack.push(30);
    
    printf("  Stack size: %d\n", int_stack.size());
    
    int value;
    while (!int_stack.empty()) {
        int_stack.pop(value);
        printf("  Popped: %d\n", value);
    }
    
    // TODO 12: Test with different type
    Stack<std::string> string_stack;
    string_stack.push(std::string("First"));
    string_stack.push(std::string("Second"));
    
    std::string str_value;
    printf("  String stack: ");
    while (!string_stack.empty()) {
        string_stack.pop(str_value);
        std::cout << str_value << " ";
    }
    printf("\n");
    
    // Test SimpleVector template
    printf("\nGeneric Vector Template:\n");
    
    SimpleVector<double> double_vector(5);
    
    // TODO 13: Add elements and display
    double_vector.push_back(1.1);
    double_vector.push_back(2.2);
    double_vector.push_back(3.3);
    
    printf("  Vector contents: ");
    for (int i = 0; i < double_vector.size(); i++) {
        printf("%.1f ", double_vector[i]);
    }
    printf("\n");
    
    printf("\n");
}

// ============================================================================
// PROBLEM SET 3: Advanced Templates (45 minutes)
// ============================================================================

// TODO 14: Template specialization for strings
template<typename T>
void print_info(T value) {
    std::cout << "Generic: " << value << " (size: " << sizeof(T) << " bytes)\n";
}

// TODO 15: Specialization for const char*
template<>
void print_info<const char*>(const char* value) {
    std::cout << "String specialization: \"" << value << "\" (length: " << strlen(value) << ")\n";
}

// TODO 16: Simple variadic template (C++11)
template<typename T>
void print_values(T value) {
    // Base case: single value
    std::cout << value << " ";
}

template<typename T, typename... Args>
void print_values(T first, Args... args) {
    // Recursive case: print first, then rest
    std::cout << first << " ";
    print_values(args...);  // Recursively call with remaining arguments
}

// TODO 17: Type trait example
template<typename T>
struct is_pointer {
    static const bool value = false;
};

template<typename T>
struct is_pointer<T*> {
    static const bool value = true;
};

template<typename T>
void analyze_type() {
    printf("Type analysis:\n");
    printf("  Size: %zu bytes\n", sizeof(T));
    printf("  Is pointer: %s\n", is_pointer<T>::value ? "yes" : "no");
    
    // Try to show type name (compiler-dependent)
    printf("  Type info: %s\n", typeid(T).name());
}

void problem_set_3_demo() {
    printf("=== Problem Set 3: Advanced Templates ===\n\n");
    
    // Template specialization
    printf("Template Specialization:\n");
    
    // TODO 18: Test generic template
    print_info(42);
    print_info(3.14159);
    
    // TODO 19: Test specialized template
    print_info("Hello, Templates!");
    
    // Variadic templates
    printf("\nVariadic Templates:\n");
    printf("  Mixed types: ");
    print_values(1, 2.5, "hello", 'X', 99);
    printf("\n");
    
    printf("  Just integers: ");
    print_values(10, 20, 30, 40);
    printf("\n");
    
    // Type traits
    printf("\nType Traits:\n");
    
    // TODO 20: Analyze different types
    printf("int:\n");
    analyze_type<int>();
    
    printf("int*:\n");
    analyze_type<int*>();
    
    printf("double:\n");
    analyze_type<double>();
    
    printf("\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("  HW_06: Compile-Time Polymorphism\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: Function Templates (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: Class Templates (45 min)  
    problem_set_2_demo();
    
    // Problem Set 3: Advanced Templates (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("         Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}