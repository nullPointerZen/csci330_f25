// HW_12: Utilities and Move Semantics
// Time: 2.25 hours (45 minutes per problem set)
// Topics: Move semantics, std::optional, std::variant, utilities

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <variant>
#include <any>
#include <tuple>
#include <utility>
#include <chrono>

// ============================================================================
// PROBLEM SET 1: Move Semantics Fundamentals (45 minutes)
// ============================================================================

// TODO 1: Class with move semantics
class MoveableResource {
private:
    std::string name_;
    int* data_;
    size_t size_;
    
public:
    // Constructor
    MoveableResource(const std::string& name, size_t size) 
        : name_(name), size_(size) {
        data_ = new int[size_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = static_cast<int>(i * 10);
        }
        printf("  MoveableResource '%s' constructed (%zu elements)\n", 
               name_.c_str(), size_);
    }
    
    // Destructor
    ~MoveableResource() {
        if (data_) {
            delete[] data_;
            printf("  MoveableResource '%s' destroyed\n", name_.c_str());
        }
    }
    
    // Copy constructor
    MoveableResource(const MoveableResource& other) 
        : name_(other.name_ + "_copy"), size_(other.size_) {
        data_ = new int[size_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }
        printf("  MoveableResource '%s' copied from '%s'\n", 
               name_.c_str(), other.name_.c_str());
    }
    
    // Copy assignment
    MoveableResource& operator=(const MoveableResource& other) {
        if (this != &other) {
            delete[] data_;
            
            name_ = other.name_ + "_copy_assigned";
            size_ = other.size_;
            data_ = new int[size_];
            
            for (size_t i = 0; i < size_; i++) {
                data_[i] = other.data_[i];
            }
            
            printf("  MoveableResource '%s' copy assigned from '%s'\n", 
                   name_.c_str(), other.name_.c_str());
        }
        return *this;
    }
    
    // Move constructor
    MoveableResource(MoveableResource&& other) noexcept 
        : name_(std::move(other.name_)), size_(other.size_), data_(other.data_) {
        other.data_ = nullptr;
        other.size_ = 0;
        printf("  MoveableResource '%s' moved (efficient transfer)\n", name_.c_str());
    }
    
    // Move assignment
    MoveableResource& operator=(MoveableResource&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            
            name_ = std::move(other.name_);
            size_ = other.size_;
            data_ = other.data_;
            
            other.data_ = nullptr;
            other.size_ = 0;
            
            printf("  MoveableResource '%s' move assigned (efficient)\n", name_.c_str());
        }
        return *this;
    }
    
    void display() const {
        if (data_) {
            printf("  Resource '%s' (%zu elements): ", name_.c_str(), size_);
            for (size_t i = 0; i < std::min(size_, size_t(5)); i++) {
                printf("%d ", data_[i]);
            }
            if (size_ > 5) printf("...");
            printf("\n");
        } else {
            printf("  Resource '%s' is empty (moved from)\n", name_.c_str());
        }
    }
};

void move_constructors() {
    printf("=== Move Constructors ===\n");
    
    // TODO: Demonstrate move constructor benefits
    printf("Move Constructor vs Copy Constructor:\n");
    
    MoveableResource original("Original", 5);
    original.display();
    
    printf("\nCopy construction:\n");
    MoveableResource copied = original;  // Copy constructor
    copied.display();
    original.display();  // Original still valid
    
    printf("\nMove construction:\n");
    MoveableResource moved = std::move(original);  // Move constructor
    moved.display();
    original.display();  // Original is now empty
    
    printf("\n");
}

void move_assignment() {
    printf("=== Move Assignment ===\n");
    
    // TODO: Demonstrate move assignment
    printf("Move Assignment Operations:\n");
    
    MoveableResource res1("First", 4);
    MoveableResource res2("Second", 3);
    
    printf("Before assignment:\n");
    res1.display();
    res2.display();
    
    printf("Copy assignment:\n");
    res2 = res1;  // Copy assignment
    res1.display();  // Original still valid
    res2.display();
    
    printf("Creating new resource for move:\n");
    MoveableResource res3("Third", 6);
    
    printf("Move assignment:\n");
    res2 = std::move(res3);  // Move assignment
    res2.display();
    res3.display();  // Source is now empty
    
    printf("\n");
}

MoveableResource create_resource(const std::string& name, size_t size) {
    printf("  Creating resource in function...\n");
    return MoveableResource(name, size);  // Return by value (move optimized)
}

void std_move_usage() {
    printf("=== std::move Usage ===\n");
    
    // TODO: Explicit move requests
    printf("Explicit Move with std::move:\n");
    
    std::vector<MoveableResource> resources;
    
    MoveableResource temp("Temporary", 3);
    temp.display();
    
    printf("Moving into vector:\n");
    resources.push_back(std::move(temp));  // Explicit move
    temp.display();  // Now empty
    
    printf("Vector contents:\n");
    resources[0].display();
    
    // TODO: Move with function returns (automatic)
    printf("\nReturn Value Optimization and Move:\n");
    
    auto returned = create_resource("Returned", 4);  // RVO or move
    returned.display();
    
    // TODO: Move in algorithms
    printf("\nMove in STL Algorithms:\n");
    
    std::vector<MoveableResource> source;
    source.emplace_back("Source1", 2);
    source.emplace_back("Source2", 3);
    
    std::vector<MoveableResource> destination;
    
    printf("Moving elements between vectors:\n");
    for (auto& item : source) {
        destination.push_back(std::move(item));
    }
    
    printf("After move - source:\n");
    for (const auto& item : source) {
        item.display();
    }
    
    printf("After move - destination:\n");
    for (const auto& item : destination) {
        item.display();
    }
    
    printf("\n");
}

void problem_set_1_demo() {
    printf("=== Problem Set 1: Move Semantics Fundamentals ===\n\n");
    
    move_constructors();
    move_assignment();
    std_move_usage();
}

// ============================================================================
// PROBLEM SET 2: Modern Utility Types (45 minutes)
// ============================================================================

// TODO 2: std::optional for nullable types
std::optional<int> safe_divide(int numerator, int denominator) {
    if (denominator == 0) {
        return std::nullopt;  // Return empty optional
    }
    return numerator / denominator;
}

std::optional<std::string> find_user_name(int user_id) {
    // Simulate database lookup
    if (user_id == 1) return "Alice";
    if (user_id == 2) return "Bob";
    if (user_id == 3) return "Carol";
    return std::nullopt;  // User not found
}

void optional_usage() {
    printf("=== std::optional - Nullable Types ===\n");
    
    // TODO: Basic optional operations
    printf("Basic Optional Operations:\n");
    
    // Test safe division
    auto result1 = safe_divide(10, 2);
    auto result2 = safe_divide(10, 0);
    
    if (result1) {
        printf("  10 / 2 = %d\n", *result1);  // Dereference optional
    }
    
    if (result2.has_value()) {
        printf("  10 / 0 = %d\n", result2.value());
    } else {
        printf("  10 / 0 = undefined (division by zero)\n");
    }
    
    // TODO: Optional with value_or
    printf("\nOptional with Default Values:\n");
    
    int user_ids[] = {1, 2, 5, 3};
    for (int id : user_ids) {
        auto name = find_user_name(id);
        printf("  User %d: %s\n", id, 
               name.value_or("Unknown User").c_str());
    }
    
    // TODO: Optional chaining and transformation
    printf("\nOptional Transformation:\n");
    
    std::optional<int> maybe_number = 42;
    
    if (maybe_number) {
        auto doubled = maybe_number.transform([](int n) { return n * 2; });
        printf("  Original: %d, Doubled: %d\n", *maybe_number, *doubled);
    }
    
    std::optional<int> empty_number;
    if (!empty_number) {
        printf("  Empty optional remains empty after transformation\n");
    }
    
    printf("\n");
}

// TODO 3: std::variant for type-safe unions
using ConfigValue = std::variant<int, double, std::string, bool>;

void process_config(const std::string& key, const ConfigValue& value) {
    printf("  Config '%s': ", key.c_str());
    
    std::visit([](const auto& v) {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, int>) {
            printf("integer = %d\n", v);
        } else if constexpr (std::is_same_v<T, double>) {
            printf("double = %.2f\n", v);
        } else if constexpr (std::is_same_v<T, std::string>) {
            printf("string = %s\n", v.c_str());
        } else if constexpr (std::is_same_v<T, bool>) {
            printf("boolean = %s\n", v ? "true" : "false");
        }
    }, value);
}

void variant_usage() {
    printf("=== std::variant - Type-Safe Unions ===\n");
    
    // TODO: Basic variant operations
    printf("Type-Safe Union with std::variant:\n");
    
    ConfigValue settings[] = {
        42,                    // int
        3.14159,              // double
        std::string("localhost"), // string
        true                   // bool
    };
    
    std::string keys[] = {"max_connections", "timeout", "hostname", "debug_mode"};
    
    for (size_t i = 0; i < 4; i++) {
        process_config(keys[i], settings[i]);
    }
    
    // TODO: Variant index and type checking
    printf("\nVariant Type Checking:\n");
    
    ConfigValue current_setting = std::string("production");
    
    printf("  Current variant holds index: %zu\n", current_setting.index());
    
    if (std::holds_alternative<std::string>(current_setting)) {
        printf("  Contains string: %s\n", 
               std::get<std::string>(current_setting).c_str());
    }
    
    // Change the variant to different type
    current_setting = 100;
    printf("  After assignment - index: %zu\n", current_setting.index());
    
    if (auto* int_ptr = std::get_if<int>(&current_setting)) {
        printf("  Contains integer: %d\n", *int_ptr);
    }
    
    printf("\n");
}

// TODO 4: std::any for type erasure
void print_any(const std::string& name, const std::any& value) {
    printf("  %s: ", name.c_str());
    
    if (value.has_value()) {
        // Try different types
        if (auto* int_val = std::any_cast<int>(&value)) {
            printf("int = %d\n", *int_val);
        } else if (auto* double_val = std::any_cast<double>(&value)) {
            printf("double = %.2f\n", *double_val);
        } else if (auto* str_val = std::any_cast<std::string>(&value)) {
            printf("string = %s\n", str_val->c_str());
        } else {
            printf("unknown type (%s)\n", value.type().name());
        }
    } else {
        printf("empty\n");
    }
}

void any_usage() {
    printf("=== std::any - Type Erasure ===\n");
    
    // TODO: Basic any operations
    printf("Type-Erased Storage with std::any:\n");
    
    std::vector<std::any> mixed_data;
    mixed_data.emplace_back(42);
    mixed_data.emplace_back(3.14159);
    mixed_data.emplace_back(std::string("Hello"));
    mixed_data.emplace_back();  // Empty any
    
    std::vector<std::string> names = {"integer", "pi", "greeting", "empty"};
    
    for (size_t i = 0; i < mixed_data.size(); i++) {
        print_any(names[i], mixed_data[i]);
    }
    
    // TODO: Any with exception handling
    printf("\nAny Type Casting with Exception Handling:\n");
    
    std::any mystery_value = std::string("surprise");
    
    try {
        int wrong_type = std::any_cast<int>(mystery_value);
        printf("  Successfully cast to int: %d\n", wrong_type);
    } catch (const std::bad_any_cast& e) {
        printf("  Failed to cast to int: %s\n", e.what());
    }
    
    try {
        std::string correct_type = std::any_cast<std::string>(mystery_value);
        printf("  Successfully cast to string: %s\n", correct_type.c_str());
    } catch (const std::bad_any_cast& e) {
        printf("  Failed to cast to string: %s\n", e.what());
    }
    
    printf("\n");
}

void problem_set_2_demo() {
    printf("=== Problem Set 2: Modern Utility Types ===\n\n");
    
    optional_usage();
    variant_usage();
    any_usage();
}

// ============================================================================
// PROBLEM SET 3: Advanced Utilities (45 minutes)
// ============================================================================

// TODO 5: Perfect forwarding with std::forward
template<typename T>
void process_value(T&& value) {
    printf("  Processing: ");
    
    if constexpr (std::is_lvalue_reference_v<T>) {
        printf("lvalue reference\n");
    } else {
        printf("rvalue reference\n");
    }
}

template<typename T>
void forward_to_processor(T&& value) {
    printf("  Forwarding ");
    process_value(std::forward<T>(value));
}

class ForwardingExample {
public:
    ForwardingExample(const std::string& name) : name_(name) {
        printf("  ForwardingExample '%s' constructed\n", name_.c_str());
    }
    
    ForwardingExample(const ForwardingExample& other) : name_(other.name_ + "_copy") {
        printf("  ForwardingExample '%s' copy constructed\n", name_.c_str());
    }
    
    ForwardingExample(ForwardingExample&& other) noexcept 
        : name_(std::move(other.name_)) {
        printf("  ForwardingExample '%s' move constructed\n", name_.c_str());
    }
    
    const std::string& get_name() const { return name_; }

private:
    std::string name_;
};

template<typename... Args>
std::unique_ptr<ForwardingExample> make_forwarding_example(Args&&... args) {
    printf("  Factory function called\n");
    return std::make_unique<ForwardingExample>(std::forward<Args>(args)...);
}

void perfect_forwarding() {
    printf("=== Perfect Forwarding with std::forward ===\n");
    
    // TODO: Demonstrate perfect forwarding
    printf("Perfect Forwarding Demonstration:\n");
    
    int lvalue = 42;
    
    printf("Forwarding lvalue:\n");
    forward_to_processor(lvalue);
    
    printf("Forwarding rvalue:\n");
    forward_to_processor(100);
    
    // TODO: Perfect forwarding in factory functions
    printf("\nPerfect Forwarding in Factory Functions:\n");
    
    printf("Creating with lvalue:\n");
    std::string name = "FromLValue";
    auto obj1 = make_forwarding_example(name);
    printf("  Result: %s\n", obj1->get_name().c_str());
    
    printf("Creating with rvalue:\n");
    auto obj2 = make_forwarding_example(std::string("FromRValue"));
    printf("  Result: %s\n", obj2->get_name().c_str());
    
    printf("Creating with string literal:\n");
    auto obj3 = make_forwarding_example("FromLiteral");
    printf("  Result: %s\n", obj3->get_name().c_str());
    
    printf("\n");
}

// TODO 6: std::tuple for multi-value containers
std::tuple<int, std::string, double> get_student_info(int id) {
    // Simulate database lookup
    if (id == 1) return std::make_tuple(85, "Alice", 3.2);
    if (id == 2) return std::make_tuple(92, "Bob", 3.8);
    if (id == 3) return std::make_tuple(78, "Carol", 2.9);
    return std::make_tuple(0, "Unknown", 0.0);
}

void tuple_usage() {
    printf("=== std::tuple - Multi-Value Containers ===\n");
    
    // TODO: Basic tuple operations
    printf("Basic Tuple Operations:\n");
    
    auto student = get_student_info(1);
    
    printf("  Student info: Grade=%d, Name=%s, GPA=%.1f\n",
           std::get<0>(student),
           std::get<1>(student).c_str(),
           std::get<2>(student));
    
    // TODO: Structured bindings (C++17)
    printf("\nStructured Bindings (C++17):\n");
    
    int student_ids[] = {1, 2, 3, 4};
    
    for (int id : student_ids) {
        auto [grade, name, gpa] = get_student_info(id);
        printf("  Student %d: %s (Grade: %d, GPA: %.1f)\n", 
               id, name.c_str(), grade, gpa);
    }
    
    // TODO: Tuple operations
    printf("\nTuple Manipulation:\n");
    
    std::tuple<int, double, std::string> data = {100, 2.5, "test"};
    
    printf("  Original tuple size: %zu\n", std::tuple_size_v<decltype(data)>);
    
    // Modify tuple elements
    std::get<0>(data) = 200;
    std::get<1>(data) = 5.0;
    std::get<2>(data) = "modified";
    
    auto [num, decimal, text] = data;
    printf("  Modified: num=%d, decimal=%.1f, text=%s\n", 
           num, decimal, text.c_str());
    
    // Tuple comparison
    auto tuple1 = std::make_tuple(1, 2.0, std::string("abc"));
    auto tuple2 = std::make_tuple(1, 2.0, std::string("abc"));
    auto tuple3 = std::make_tuple(1, 2.0, std::string("def"));
    
    printf("  tuple1 == tuple2: %s\n", (tuple1 == tuple2) ? "true" : "false");
    printf("  tuple1 == tuple3: %s\n", (tuple1 == tuple3) ? "true" : "false");
    
    printf("\n");
}

// TODO 7: Utility functions
void utility_functions() {
    printf("=== Utility Functions ===\n");
    
    // TODO: std::swap
    printf("std::swap:\n");
    
    int a = 10, b = 20;
    printf("  Before swap: a=%d, b=%d\n", a, b);
    std::swap(a, b);
    printf("  After swap: a=%d, b=%d\n", a, b);
    
    std::string str1 = "Hello", str2 = "World";
    printf("  Before swap: str1=%s, str2=%s\n", str1.c_str(), str2.c_str());
    std::swap(str1, str2);
    printf("  After swap: str1=%s, str2=%s\n", str1.c_str(), str2.c_str());
    
    // TODO: std::exchange
    printf("\nstd::exchange:\n");
    
    int original = 42;
    int old_value = std::exchange(original, 100);
    printf("  exchange(42, 100): old_value=%d, new_value=%d\n", 
           old_value, original);
    
    std::string text = "original";
    std::string old_text = std::exchange(text, "new");
    printf("  exchange('original', 'new'): old='%s', new='%s'\n", 
           old_text.c_str(), text.c_str());
    
    // TODO: std::pair utilities
    printf("\nstd::pair Utilities:\n");
    
    std::pair<int, std::string> pair1 = {1, "first"};
    std::pair<int, std::string> pair2 = {2, "second"};
    
    printf("  pair1: (%d, %s)\n", pair1.first, pair1.second.c_str());
    printf("  pair2: (%d, %s)\n", pair2.first, pair2.second.c_str());
    
    std::swap(pair1, pair2);
    printf("  After swap:\n");
    printf("  pair1: (%d, %s)\n", pair1.first, pair1.second.c_str());
    printf("  pair2: (%d, %s)\n", pair2.first, pair2.second.c_str());
    
    // std::make_pair
    auto made_pair = std::make_pair(42, std::string("created"));
    printf("  make_pair result: (%d, %s)\n", 
           made_pair.first, made_pair.second.c_str());
    
    printf("\n");
}

void problem_set_3_demo() {
    printf("=== Problem Set 3: Advanced Utilities ===\n\n");
    
    perfect_forwarding();
    tuple_usage();
    utility_functions();
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    printf("==========================================\n");
    printf("     HW_12: Utilities and Move Semantics\n");
    printf("==========================================\n\n");
    
    // Problem Set 1: Move Semantics Fundamentals (45 min)
    problem_set_1_demo();
    
    // Problem Set 2: Modern Utility Types (45 min)
    problem_set_2_demo();
    
    // Problem Set 3: Advanced Utilities (45 min)
    problem_set_3_demo();
    
    printf("==========================================\n");
    printf("           Program Complete!\n");
    printf("==========================================\n");
    
    return 0;
}