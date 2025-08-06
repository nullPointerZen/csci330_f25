# Chapter 9: Functions - Lesson Plan

## Course: C++ for Python/Java Programmers
## Estimated Time: 2.5 hours maximum (self-paced)

---

## Development Environment Setup
**Continue using your chosen workflow from previous chapters:**
- **Option A**: Docker + Command Line
- **Option B**: VS Code + Docker (excellent for lambda and function pointer debugging)
- **Option C**: VS Code + Local Compiler

**For Chapter 9's function concepts, debugger shows callback execution and lambda captures!**

---

## Learning Objectives

By the end of this lesson, students will be able to:

1. **Implement** function pointers and understand their use cases vs Python's function objects
2. **Create and use** lambda expressions for inline functions and callbacks
3. **Design** function objects (functors) and understand when to use them over lambdas
4. **Apply** std::function as a type-erased wrapper for callable objects
5. **Implement** higher-order functions that accept and return other functions
6. **Compare** C++ function types with Python decorators and Java functional interfaces

---

## Key Concepts with Python/Java Equivalencies

### 1. Function Pointers vs Function References

| Aspect | C++ Function Pointers | Python Functions | Java Method References |
|--------|----------------------|------------------|----------------------|
| **Declaration** | `int (*func)(int, int);` | Functions are first-class objects | `Function<Integer, Integer> func;` |
| **Assignment** | `func = &add;` or `func = add;` | `func = add` | `func = Math::max;` |
| **Invocation** | `result = func(5, 3);` | `result = func(5, 3)` | `result = func.apply(5, 3);` |
| **Null Check** | `if(func != nullptr)` | `if func:` or `if callable(func):` | `if(func != null)` |

**Key Insight**: C++ function pointers are similar to Python's function objects but require explicit type information.

### 2. Lambda Expressions

| Feature | C++ Lambdas | Python Lambdas | Java Lambdas |
|---------|-------------|----------------|--------------|
| **Basic Syntax** | `[](int x) { return x * 2; }` | `lambda x: x * 2` | `x -> x * 2` |
| **Capture** | `[x](int y) { return x + y; }` | Automatic closure | Effectively final variables |
| **Multi-line** | `[](int x) {`<br>&nbsp;&nbsp;`int result = x * 2;`<br>&nbsp;&nbsp;`return result;`<br>`}` | Use def instead | `x -> {`<br>&nbsp;&nbsp;`int result = x * 2;`<br>&nbsp;&nbsp;`return result;`<br>`}` |

### 3. Function Objects (Functors)

| Concept | C++ Functors | Python Callable Classes | Java Functional Objects |
|---------|--------------|--------------------------|-------------------------|
| **Definition** | Class with `operator()` | Class with `__call__` method | Class implementing functional interface |
| **State** | Member variables | Instance variables | Instance fields |
| **Usage** | `MyFunctor func; func(args);` | `func = MyCallable(); func(args)` | `MyFunction func = new ...; func.apply(args)` |

### 4. std::function - Type Erasure

| Aspect | C++ std::function | Python | Java |
|--------|------------------|--------|------|
| **Purpose** | Type-erased callable wrapper | Functions naturally polymorphic | Functional interfaces provide abstraction |
| **Declaration** | `std::function<int(int)> f;` | Any callable can be assigned | `Function<Integer, Integer> f;` |
| **Storage** | Can hold lambdas, functors, function pointers | Native support | Can hold lambdas, method refs, instances |

---

## Lesson Structure

### Module 1: Function Pointers - C-Style Callbacks (45 minutes)

#### Content Delivery
- **Function Pointer Basics**: Syntax, declaration, and calling
- **Use Cases**: Callbacks, configurable behavior, plugin systems
- **Comparison**: How this relates to Python's first-class functions
- **Safety**: Null pointer checks and best practices

#### Activities
1. **Basic Function Pointer Usage** (20 minutes)
   ```cpp
   #include <cstdio>
   
   int add(int a, int b) { return a + b; }
   int multiply(int a, int b) { return a * b; }
   
   int main() {
       // Function pointer declaration and assignment
       int (*operation)(int, int) = add;
       printf("5 + 3 = %d\n", operation(5, 3));
       
       // Reassignment
       operation = multiply;
       printf("5 * 3 = %d\n", operation(5, 3));
       
       // Array of function pointers
       int (*ops[])(int, int) = {add, multiply};
       for(int i = 0; i < 2; ++i) {
           printf("Using operation %d: %d\n", i, ops[i](4, 2));
       }
       
       return 0;
   }
   ```

2. **Callback Pattern Implementation** (15 minutes)
   ```cpp
   #include <cstdio>
   
   // Callback function type
   typedef void (*ProgressCallback)(int percentage);
   
   void simple_progress(int percentage) {
       printf("Progress: %d%%\n", percentage);
   }
   
   void fancy_progress(int percentage) {
       printf("[");
       for(int i = 0; i < percentage / 5; ++i) printf("=");
       for(int i = percentage / 5; i < 20; ++i) printf(" ");
       printf("] %d%%\n", percentage);
   }
   
   void long_running_task(ProgressCallback callback) {
       for(int i = 0; i <= 100; i += 10) {
           // Simulate work
           if(callback != nullptr) {
               callback(i);
           }
       }
   }
   
   int main() {
       printf("Simple progress:\n");
       long_running_task(simple_progress);
       
       printf("\nFancy progress:\n");
       long_running_task(fancy_progress);
       
       return 0;
   }
   ```

3. **Function Pointer Pitfalls** (10 minutes)
   - Null pointer dereference
   - Type safety issues
   - Complex syntax problems

#### Check for Understanding
- Can declare and use function pointers correctly
- Understands callback pattern implementation
- Recognizes when to use function pointers vs alternatives

### Module 2: Lambda Expressions - Modern C++ Closures (50 minutes)

#### Content Delivery
- **Lambda Syntax**: Capture, parameters, return type, body
- **Capture Modes**: By value, by reference, mixed captures
- **Use Cases**: STL algorithms, event handling, local functions
- **Python Connection**: Similar to Python lambdas but more powerful

#### Activities
1. **Lambda Fundamentals** (20 minutes)
   ```cpp
   #include <iostream>
   #include <vector>
   #include <algorithm>
   
   int main() {
       std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
       
       // Basic lambda - no capture
       auto print_num = [](int n) { std::cout << n << " "; };
       
       std::cout << "Original: ";
       std::for_each(numbers.begin(), numbers.end(), print_num);
       std::cout << "\n";
       
       // Lambda with capture by value
       int threshold = 5;
       auto above_threshold = [threshold](int n) { return n > threshold; };
       
       std::cout << "Above " << threshold << ": ";
       std::copy_if(numbers.begin(), numbers.end(),
                    std::ostream_iterator<int>(std::cout, " "),
                    above_threshold);
       std::cout << "\n";
       
       // Lambda with capture by reference
       int count = 0;
       auto counter = [&count](int n) { 
           if(n % 2 == 0) ++count; 
           return n;
       };
       
       std::transform(numbers.begin(), numbers.end(), numbers.begin(), counter);
       std::cout << "Even numbers found: " << count << "\n";
       
       return 0;
   }
   ```

2. **Advanced Lambda Captures** (15 minutes)
   ```cpp
   #include <iostream>
   #include <string>
   
   class EventProcessor {
   private:
       std::string name;
       int event_count;
   
   public:
       EventProcessor(const std::string& n) : name(n), event_count(0) {}
       
       auto create_handler() {
           // Mixed capture: copy name, reference event_count
           return [name = this->name, &event_count = this->event_count]
                  (const std::string& event) {
               ++event_count;
               std::cout << name << " processed event: " << event 
                        << " (total: " << event_count << ")\n";
           };
       }
       
       int get_count() const { return event_count; }
   };
   
   int main() {
       EventProcessor processor("Logger");
       auto handler = processor.create_handler();
       
       handler("user_login");
       handler("file_upload");
       handler("data_export");
       
       std::cout << "Final count: " << processor.get_count() << "\n";
       return 0;
   }
   ```

3. **Generic Lambdas** (15 minutes)
   ```cpp
   #include <iostream>
   #include <vector>
   #include <string>
   
   int main() {
       // Generic lambda (C++14)
       auto generic_printer = [](const auto& item) {
           std::cout << "Item: " << item << "\n";
       };
       
       generic_printer(42);
       generic_printer(3.14);
       generic_printer(std::string("Hello"));
       
       // Generic lambda with multiple types
       auto comparator = [](const auto& a, const auto& b) {
           return a < b;
       };
       
       std::cout << "5 < 10: " << comparator(5, 10) << "\n";
       std::cout << "hello < world: " << comparator(std::string("hello"), 
                                                   std::string("world")) << "\n";
       
       return 0;
   }
   ```

#### Check for Understanding
- Can write lambdas with appropriate capture modes
- Understands when to capture by value vs reference
- Can use lambdas with STL algorithms effectively

### Module 3: Function Objects and std::function (45 minutes)

#### Content Delivery  
- **Functors**: Classes with operator() overloaded
- **State Management**: Why functors over lambdas sometimes
- **std::function**: Type erasure for any callable
- **Performance**: When to use what approach

#### Activities
1. **Custom Function Objects** (20 minutes)
   ```cpp
   #include <iostream>
   #include <vector>
   #include <algorithm>
   
   class Accumulator {
   private:
       int sum;
       
   public:
       Accumulator() : sum(0) {}
       
       // Function call operator
       int operator()(int value) {
           sum += value;
           return sum;
       }
       
       int get_sum() const { return sum; }
       void reset() { sum = 0; }
   };
   
   class Multiplier {
   private:
       int factor;
       
   public:
       explicit Multiplier(int f) : factor(f) {}
       
       int operator()(int x) const {
           return x * factor;
       }
   };
   
   int main() {
       std::vector<int> numbers = {1, 2, 3, 4, 5};
       
       // Using accumulator functor
       Accumulator acc;
       std::cout << "Accumulating: ";
       for(int n : numbers) {
           std::cout << acc(n) << " ";
       }
       std::cout << "\nFinal sum: " << acc.get_sum() << "\n";
       
       // Using with STL algorithms
       Multiplier times_3(3);
       std::cout << "Multiplied by 3: ";
       std::transform(numbers.begin(), numbers.end(),
                     std::ostream_iterator<int>(std::cout, " "),
                     times_3);
       std::cout << "\n";
       
       return 0;
   }
   ```

2. **std::function for Type Erasure** (15 minutes)
   ```cpp
   #include <iostream>
   #include <functional>
   #include <vector>
   
   // Regular function
   int double_it(int x) { return x * 2; }
   
   // Function object
   class Tripler {
   public:
       int operator()(int x) const { return x * 3; }
   };
   
   int main() {
       std::vector<std::function<int(int)>> operations;
       
       // Store different types of callables
       operations.push_back(double_it);                    // Function pointer
       operations.push_back(Tripler{});                    // Function object
       operations.push_back([](int x) { return x + 10; }); // Lambda
       
       int value = 5;
       for(size_t i = 0; i < operations.size(); ++i) {
           std::cout << "Operation " << i << ": " 
                    << operations[i](value) << "\n";
       }
       
       return 0;
   }
   ```

3. **Callback System with std::function** (10 minutes)
   ```cpp
   #include <iostream>
   #include <functional>
   #include <vector>
   #include <string>
   
   class EventSystem {
   private:
       std::vector<std::function<void(const std::string&)>> listeners;
       
   public:
       void add_listener(std::function<void(const std::string&)> listener) {
           listeners.push_back(listener);
       }
       
       void fire_event(const std::string& event) {
           for(auto& listener : listeners) {
               listener(event);
           }
       }
   };
   
   void log_event(const std::string& event) {
       std::cout << "[LOG] " << event << "\n";
   }
   
   class AlertSystem {
   public:
       void handle_alert(const std::string& event) {
           std::cout << "[ALERT] Critical: " << event << "\n";
       }
   };
   
   int main() {
       EventSystem events;
       AlertSystem alerts;
       
       // Add different types of listeners
       events.add_listener(log_event);  // Function pointer
       events.add_listener([](const std::string& e) {  // Lambda
           std::cout << "[DEBUG] Processing: " << e << "\n";
       });
       events.add_listener(std::bind(&AlertSystem::handle_alert, &alerts, std::placeholders::_1));  // Member function
       
       events.fire_event("System startup");
       events.fire_event("User login");
       
       return 0;
   }
   ```

#### Check for Understanding
- Can implement custom function objects when appropriate
- Understands std::function for storing different callable types
- Can design flexible callback systems

### Module 4: Higher-Order Functions and Practical Applications (30 minutes)

#### Content Delivery
- **Higher-Order Functions**: Functions that take/return other functions
- **Practical Patterns**: Strategy pattern, configurable algorithms
- **Performance Considerations**: When to use which approach
- **Modern C++ Style**: Preference for lambdas and std::function

#### Activities
1. **Strategy Pattern with Functions** (15 minutes)
   ```cpp
   #include <iostream>
   #include <functional>
   #include <vector>
   #include <algorithm>
   
   class DataProcessor {
   private:
       std::function<bool(int, int)> comparison_strategy;
       
   public:
       void set_strategy(std::function<bool(int, int)> strategy) {
           comparison_strategy = strategy;
       }
       
       void process(std::vector<int>& data) {
           if(comparison_strategy) {
               std::sort(data.begin(), data.end(), comparison_strategy);
           }
       }
   };
   
   int main() {
       std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};
       DataProcessor processor;
       
       std::cout << "Original: ";
       for(int n : data) std::cout << n << " ";
       std::cout << "\n";
       
       // Ascending sort
       processor.set_strategy([](int a, int b) { return a < b; });
       processor.process(data);
       std::cout << "Ascending: ";
       for(int n : data) std::cout << n << " ";
       std::cout << "\n";
       
       // Descending sort
       processor.set_strategy([](int a, int b) { return a > b; });
       processor.process(data);
       std::cout << "Descending: ";
       for(int n : data) std::cout << n << " ";
       std::cout << "\n";
       
       return 0;
   }
   ```

2. **Function Composition** (15 minutes)
   ```cpp
   #include <iostream>
   #include <functional>
   
   // Higher-order function that composes two functions
   template<typename F, typename G>
   auto compose(F f, G g) {
       return [f, g](auto x) { return f(g(x)); };
   }
   
   // Currying example
   auto add = [](int x) {
       return [x](int y) { return x + y; };
   };
   
   auto multiply = [](int x) {
       return [x](int y) { return x * y; };
   };
   
   int main() {
       // Function composition
       auto square = [](int x) { return x * x; };
       auto increment = [](int x) { return x + 1; };
       
       auto square_then_increment = compose(increment, square);
       auto increment_then_square = compose(square, increment);
       
       int value = 5;
       std::cout << "Value: " << value << "\n";
       std::cout << "Square then increment: " << square_then_increment(value) << "\n";
       std::cout << "Increment then square: " << increment_then_square(value) << "\n";
       
       // Currying demonstration
       auto add_5 = add(5);
       auto multiply_3 = multiply(3);
       
       std::cout << "Add 5 to 10: " << add_5(10) << "\n";
       std::cout << "Multiply 7 by 3: " << multiply_3(7) << "\n";
       
       return 0;
   }
   ```

#### Check for Understanding
- Can implement higher-order functions effectively
- Understands function composition and currying concepts
- Can choose appropriate function abstraction for given problems

---

## Assessment Strategy

### Formative Assessment (Throughout)
- **Quick Checks**: Identify correct lambda capture modes
- **Code Review**: Students explain function pointer vs lambda trade-offs
- **Debugging**: Fix common capture and type issues

### Summative Assessment
**Function-Based Calculator System** (45 minutes):

#### Requirements
1. Create a calculator that supports pluggable operations
2. Use function pointers for basic operations (+, -, *, /)
3. Use lambdas for complex operations (power, factorial)  
4. Use std::function to store mixed operation types
5. Implement a history system using function objects
6. Create a higher-order function for operation chaining

#### Starter Template Provided
```cpp
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <string>

// Function pointer type for basic operations
typedef double (*BasicOperation)(double, double);

// TODO: Implement basic operations as regular functions
double add(double a, double b) { /* implement */ }
// ... other operations

// TODO: Create HistoryTracker function object
class HistoryTracker {
    // Track operation history with operator()
};

class Calculator {
private:
    std::map<std::string, std::function<double(double, double)>> operations;
    HistoryTracker history;
    
public:
    // TODO: Implement methods to register operations
    // TODO: Implement calculate method
    // TODO: Implement operation chaining
};

int main() {
    Calculator calc;
    // TODO: Register operations and test
    return 0;
}
```

#### Rubric (Pass/Fail)
| Criteria | Pass Requirement |
|----------|------------------|
| **Function Pointers** | Correctly implements and uses function pointers for basic operations |
| **Lambda Usage** | Uses lambdas appropriately with correct capture modes |
| **Function Objects** | Implements stateful function object for history tracking |
| **std::function** | Uses std::function for type-erased operation storage |
| **Higher-Order Functions** | Implements operation chaining or composition |

---

## Additional Resources

### Required Reading
- Chapter 9: "Functions" from C++ Crash Course

### Supplementary Materials
- [cppreference.com std::function](https://en.cppreference.com/w/cpp/utility/functional/function) - Reference
- [Lambda Expressions Tutorial](https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp) - Microsoft docs
- [Functional Programming in C++](https://www.manning.com/books/functional-programming-in-c-plus-plus) - Advanced reading

### Quick Reference Card
```cpp
// Function Pointers
int (*func_ptr)(int, int) = &add;
result = func_ptr(5, 3);

// Basic Lambda
auto lambda = [](int x) { return x * 2; };

// Lambda with Capture
int multiplier = 3;
auto multiply_by = [multiplier](int x) { return x * multiplier; };  // by value
auto multiply_ref = [&multiplier](int x) { return x * multiplier; }; // by reference

// Function Object
class Adder {
    int offset;
public:
    Adder(int o) : offset(o) {}
    int operator()(int x) const { return x + offset; }
};

// std::function
std::function<int(int)> f = [](int x) { return x * 2; };
f = Adder(5);  // Can store different callable types
```

---

## Teaching Notes

### Common Challenges
1. **Lambda Capture Confusion**: Students mix up capture by value vs reference
2. **Function Pointer Syntax**: Complex syntax can be intimidating
3. **When to Use What**: Choosing between lambdas, functors, and function pointers
4. **std::function Overhead**: Understanding performance implications

### Differentiation
- **For Advanced Students**: Explore template metaprogramming with function types, perfect forwarding
- **For Struggling Students**: Focus on practical examples, provide more scaffolded exercises

### Time Management
- Spend extra time on lambda captures - this is where most confusion occurs
- Function pointers are familiar to students with C background
- Connect everything back to Python/Java equivalents students already know

### Python/Java Connections to Emphasize
- **Python**: "C++ lambdas are like Python lambdas but with explicit types and powerful capture"
- **Java**: "std::function is like Java's functional interfaces but can hold any callable"
- **Both**: "Function pointers are like function variables in Python or method references in Java"