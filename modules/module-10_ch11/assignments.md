# Chapter 11: Smart Pointers - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 11 "Smart Pointers"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 2.25 hours total for all three problem sets
- Test all programs thoroughly before submission

**Target Audience**: Students with Python/Java background  
**Total Time**: 2.25 hours (135 minutes)  
**Prerequisites**: Chapters 1-10 completed + Chapter 11 lesson  

## Problem Set Structure

- **Problem Set 1**: RAII and std::unique_ptr (45 minutes)
- **Problem Set 2**: std::shared_ptr and Reference Counting (60 minutes) 
- **Problem Set 3**: std::weak_ptr and Circular References (30 minutes)

---

## Problem Set 1: RAII and std::unique_ptr (45 minutes)

### Problem 1.1: Resource Management with RAII (15 minutes)

**Background**: Coming from Python's automatic garbage collection or Java's try-with-resources, learn C++ RAII principles.

**Task**: Create RAII classes that automatically manage different types of resources.

**Requirements**:
1. Implement RAII wrapper for file handles
2. Implement RAII wrapper for dynamic memory
3. Demonstrate automatic cleanup when exceptions occur
4. Show the difference between manual and RAII management

**Starter Code**:
```cpp
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>

// TODO: Implement RAII file wrapper
class FileHandle {
private:
    std::ofstream file_;
    std::string filename_;
    
public:
    FileHandle(const std::string& filename) : filename_(filename) {
        // TODO: Open file and handle errors
    }
    
    ~FileHandle() {
        // TODO: Ensure file is closed
    }
    
    // TODO: Add methods to write to file
    void write(const std::string& data) {
        // TODO: Write data and handle errors
    }
    
    bool is_open() const {
        // TODO: Check if file is open
    }
};

// TODO: Implement RAII memory wrapper (before learning about smart pointers)
template<typename T>
class RAIIArray {
private:
    T* data_;
    size_t size_;
    
public:
    RAIIArray(size_t size) : size_(size) {
        // TODO: Allocate memory
    }
    
    ~RAIIArray() {
        // TODO: Deallocate memory
    }
    
    // TODO: Disable copying to prevent double-delete
    RAIIArray(const RAIIArray&) = delete;
    RAIIArray& operator=(const RAIIArray&) = delete;
    
    T& operator[](size_t index) {
        // TODO: Provide array access with bounds checking
    }
    
    size_t size() const { return size_; }
};

void demonstrate_manual_management() {
    std::cout << "Manual resource management:\n";
    // TODO: Show manual resource management with potential leaks
}

void demonstrate_raii_management() {
    std::cout << "RAII resource management:\n";
    // TODO: Show RAII resource management with automatic cleanup
}

void demonstrate_exception_safety() {
    std::cout << "Exception safety test:\n";
    // TODO: Show how RAII handles exceptions
}

int main() {
    demonstrate_manual_management();
    std::cout << "\n";
    demonstrate_raii_management();
    std::cout << "\n";
    demonstrate_exception_safety();
    
    return 0;
}
```

**Learning Goals**:
- RAII principles and automatic resource management
- Constructor/destructor resource pairing
- Exception safety with automatic cleanup
- Understanding the problems smart pointers solve

---

### Problem 1.2: std::unique_ptr Fundamentals (20 minutes)

**Background**: Use std::unique_ptr for exclusive ownership scenarios.

**Task**: Implement various std::unique_ptr use cases and understand move semantics.

**Requirements**:
1. Create and manage objects with std::unique_ptr
2. Transfer ownership using move semantics
3. Use std::make_unique for object creation
4. Handle arrays with std::unique_ptr<T[]>

**Starter Code**:
```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Resource {
private:
    std::string name_;
    int id_;
    
public:
    Resource(const std::string& name, int id) : name_(name), id_(id) {
        std::cout << "Resource '" << name_ << "' (ID: " << id_ << ") created\n";
    }
    
    ~Resource() {
        std::cout << "Resource '" << name_ << "' (ID: " << id_ << ") destroyed\n";
    }
    
    void use() const {
        std::cout << "Using resource '" << name_ << "' (ID: " << id_ << ")\n";
    }
    
    const std::string& name() const { return name_; }
    int id() const { return id_; }
};

// TODO: Factory function that returns unique_ptr
std::unique_ptr<Resource> create_resource(const std::string& name, int id) {
    // TODO: Use make_unique to create and return resource
}

// TODO: Function that takes ownership of a unique_ptr
void process_resource(std::unique_ptr<Resource> resource) {
    // TODO: Use the resource and demonstrate ownership transfer
}

// TODO: Function that borrows a resource without taking ownership
void use_resource(const Resource& resource) {
    // TODO: Use resource without affecting ownership
}

class ResourceManager {
private:
    std::vector<std::unique_ptr<Resource>> resources_;
    
public:
    // TODO: Add method to add resources
    void add_resource(std::unique_ptr<Resource> resource) {
        // TODO: Store resource in vector
    }
    
    // TODO: Add method to remove resource by id
    std::unique_ptr<Resource> remove_resource(int id) {
        // TODO: Find and remove resource, returning ownership
    }
    
    // TODO: Add method to use resource without transferring ownership
    void use_resource(int id) {
        // TODO: Find and use resource
    }
    
    void list_resources() const {
        std::cout << "Managed resources:\n";
        for (const auto& resource : resources_) {
            if (resource) {
                std::cout << "  - " << resource->name() << " (ID: " << resource->id() << ")\n";
            }
        }
    }
};

void demonstrate_array_management() {
    std::cout << "Array management with unique_ptr:\n";
    
    // TODO: Create array using unique_ptr<T[]>
    const size_t size = 10;
    // auto numbers = ???
    
    // TODO: Initialize array
    // TODO: Use array
    // TODO: Show automatic cleanup
}

int main() {
    std::cout << "=== unique_ptr Fundamentals ===\n\n";
    
    // TODO: Basic unique_ptr usage
    std::cout << "1. Basic unique_ptr creation and usage:\n";
    
    // TODO: Factory function usage
    std::cout << "\n2. Factory function with unique_ptr:\n";
    
    // TODO: Ownership transfer
    std::cout << "\n3. Ownership transfer:\n";
    
    // TODO: ResourceManager usage
    std::cout << "\n4. Resource management:\n";
    ResourceManager manager;
    
    // TODO: Array management
    std::cout << "\n5. Array management:\n";
    demonstrate_array_management();
    
    return 0;
}
```

**Learning Goals**:
- std::unique_ptr creation and usage
- Move semantics and ownership transfer
- std::make_unique vs raw new
- Array management with unique_ptr

---

### Problem 1.3: Custom Deleters (10 minutes)

**Background**: Use custom deleters for specialized cleanup requirements.

**Task**: Implement custom deleters for various resource types.

**Requirements**:
1. Create custom deleters for different resource types
2. Use custom deleters with unique_ptr
3. Handle C API resources that require specific cleanup
4. Log resource cleanup for debugging

**Starter Code**:
```cpp
#include <iostream>
#include <memory>
#include <cstdio>

// TODO: Custom deleter for FILE*
struct FileCloser {
    void operator()(FILE* file) const {
        // TODO: Close file and log
    }
};

// TODO: Custom deleter with logging
struct LoggingDeleter {
    std::string resource_name;
    
    LoggingDeleter(const std::string& name) : resource_name(name) {}
    
    void operator()(int* ptr) const {
        // TODO: Log deletion and delete
    }
};

// TODO: Generic custom deleter
template<typename T, typename DeleterFunc>
struct CustomDeleter {
    DeleterFunc deleter_func;
    
    CustomDeleter(DeleterFunc func) : deleter_func(func) {}
    
    void operator()(T* ptr) const {
        deleter_func(ptr);
    }
};

void demonstrate_file_deleter() {
    std::cout << "Custom deleter for FILE*:\n";
    
    // TODO: Use unique_ptr with custom deleter for FILE*
    std::unique_ptr<FILE, FileCloser> file(fopen("test.txt", "w"));
    
    if (file) {
        fprintf(file.get(), "Hello from custom deleter!\n");
        // File will be automatically closed by custom deleter
    }
}

void demonstrate_logging_deleter() {
    std::cout << "\nLogging deleter:\n";
    
    // TODO: Use logging deleter
    auto deleter = LoggingDeleter("TestResource");
    std::unique_ptr<int, LoggingDeleter> ptr(new int(42), deleter);
    
    std::cout << "Value: " << *ptr << "\n";
    // Destruction will be logged
}

void demonstrate_generic_deleter() {
    std::cout << "\nGeneric custom deleter:\n";
    
    // TODO: Create lambda deleter
    auto lambda_deleter = [](int* ptr) {
        std::cout << "Lambda deleter cleaning up value: " << *ptr << "\n";
        delete ptr;
    };
    
    // TODO: Use lambda deleter with unique_ptr
}

int main() {
    demonstrate_file_deleter();
    demonstrate_logging_deleter();
    demonstrate_generic_deleter();
    
    return 0;
}
```

**Learning Goals**:
- Custom deleter implementation
- Working with C APIs through smart pointers
- Logging and debugging resource cleanup
- Lambda deleters

---

## Problem Set 2: std::shared_ptr and Reference Counting (60 minutes)

### Problem 2.1: Shared Ownership Scenarios (20 minutes)

**Background**: Use std::shared_ptr when multiple objects need to share ownership of a resource.

**Task**: Implement scenarios where shared ownership is necessary.

**Requirements**:
1. Create shared resources with std::shared_ptr
2. Understand reference counting behavior
3. Use std::make_shared for efficiency
4. Handle shared resource lifecycle correctly

**Starter Code**:
```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>

class SharedResource {
private:
    std::string name_;
    int value_;
    
public:
    SharedResource(const std::string& name, int value) : name_(name), value_(value) {
        std::cout << "SharedResource '" << name_ << "' created with value " << value_ << "\n";
    }
    
    ~SharedResource() {
        std::cout << "SharedResource '" << name_ << "' destroyed\n";
    }
    
    void modify(int new_value) {
        value_ = new_value;
        std::cout << "SharedResource '" << name_ << "' modified to " << value_ << "\n";
    }
    
    void display() const {
        std::cout << "SharedResource '" << name_ << "' = " << value_ << "\n";
    }
    
    const std::string& name() const { return name_; }
    int value() const { return value_; }
};

class Observer {
private:
    std::string observer_name_;
    std::shared_ptr<SharedResource> resource_;
    
public:
    Observer(const std::string& name, std::shared_ptr<SharedResource> resource)
        : observer_name_(name), resource_(resource) {
        std::cout << "Observer '" << observer_name_ << "' created, resource ref count: " 
                  << resource_.use_count() << "\n";
    }
    
    ~Observer() {
        std::cout << "Observer '" << observer_name_ << "' destroyed\n";
    }
    
    void check_resource() {
        if (resource_) {
            std::cout << "Observer '" << observer_name_ << "' sees: ";
            resource_->display();
            std::cout << "  Reference count: " << resource_.use_count() << "\n";
        }
    }
    
    void modify_resource(int new_value) {
        if (resource_) {
            resource_->modify(new_value);
        }
    }
};

void demonstrate_reference_counting() {
    std::cout << "=== Reference Counting Demo ===\n";
    
    // TODO: Create shared resource
    auto resource = std::make_shared<SharedResource>("SharedData", 100);
    std::cout << "Initial ref count: " << resource.use_count() << "\n\n";
    
    {
        // TODO: Create observers that share the resource
        std::cout << "Creating observers...\n";
        Observer obs1("Observer1", resource);
        
        {
            Observer obs2("Observer2", resource);
            Observer obs3("Observer3", resource);
            
            std::cout << "\nAll observers checking resource:\n";
            obs1.check_resource();
            obs2.check_resource();
            obs3.check_resource();
            
            std::cout << "\nModifying resource through observer:\n";
            obs2.modify_resource(200);
            
            std::cout << "\nAll observers see the change:\n";
            obs1.check_resource();
            obs2.check_resource();
            obs3.check_resource();
            
            std::cout << "\nInner scope ending...\n";
        }
        
        std::cout << "\nAfter inner scope:\n";
        obs1.check_resource();
        
        std::cout << "\nOuter scope ending...\n";
    }
    
    std::cout << "\nAfter all observers destroyed:\n";
    std::cout << "Final ref count: " << resource.use_count() << "\n";
    resource->display();
    
    std::cout << "\nClearing main reference...\n";
}

int main() {
    demonstrate_reference_counting();
    std::cout << "\nAll resources should be destroyed now.\n";
    
    return 0;
}
```

**Learning Goals**:
- shared_ptr reference counting mechanics
- Shared ownership scenarios
- make_shared vs shared_ptr constructor
- Reference count monitoring

---

### Problem 2.2: Thread Safety and Performance (25 minutes)

**Background**: Understand shared_ptr thread safety characteristics and performance implications.

**Task**: Explore shared_ptr behavior in concurrent scenarios and performance characteristics.

**Requirements**:
1. Understand what is and isn't thread-safe with shared_ptr
2. Compare performance of shared_ptr vs unique_ptr vs raw pointers
3. Demonstrate safe concurrent access patterns
4. Show shared_ptr overhead characteristics

**Starter Code**:
```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>

class ExpensiveResource {
private:
    std::vector<double> data_;
    std::string name_;
    
public:
    ExpensiveResource(const std::string& name, size_t size) 
        : name_(name), data_(size, 3.14159) {
        std::cout << "ExpensiveResource '" << name_ << "' created with " << size << " elements\n";
    }
    
    ~ExpensiveResource() {
        std::cout << "ExpensiveResource '" << name_ << "' destroyed\n";
    }
    
    double compute() const {
        double sum = 0.0;
        for (double value : data_) {
            sum += value * value;
        }
        return sum;
    }
    
    const std::string& name() const { return name_; }
    size_t size() const { return data_.size(); }
};

// TODO: Performance comparison function
template<typename SmartPtr>
void performance_test(const std::string& test_name, SmartPtr ptr, int iterations) {
    auto start = std::chrono::high_resolution_clock::now();
    
    // TODO: Perform operations on smart pointer
    double result = 0.0;
    for (int i = 0; i < iterations; ++i) {
        // TODO: Access object and call methods
        // TODO: Copy/assign smart pointer
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << test_name << ": " << duration.count() << " microseconds, result: " << result << "\n";
}

void demonstrate_performance_comparison() {
    std::cout << "=== Performance Comparison ===\n";
    
    const int iterations = 100000;
    const size_t data_size = 1000;
    
    // TODO: Create resources for testing
    auto shared_resource = std::make_shared<ExpensiveResource>("Shared", data_size);
    auto unique_resource = std::make_unique<ExpensiveResource>("Unique", data_size);
    auto raw_resource = new ExpensiveResource("Raw", data_size);
    
    // TODO: Test performance of different pointer types
    std::cout << "\nTesting with " << iterations << " iterations:\n";
    
    // TODO: Implement performance tests
    
    delete raw_resource; // Manual cleanup for raw pointer
}

// TODO: Thread safety demonstration
std::atomic<int> counter{0};

void worker_thread(std::shared_ptr<ExpensiveResource> resource, int thread_id, int operations) {
    for (int i = 0; i < operations; ++i) {
        // TODO: Safely use shared resource
        // TODO: Create local copies of shared_ptr
        // TODO: Show reference count changes
    }
    std::cout << "Thread " << thread_id << " completed\n";
}

void demonstrate_thread_safety() {
    std::cout << "\n=== Thread Safety Demo ===\n";
    
    auto resource = std::make_shared<ExpensiveResource>("ThreadShared", 1000);
    std::cout << "Starting with ref count: " << resource.use_count() << "\n";
    
    const int num_threads = 4;
    const int operations_per_thread = 1000;
    
    std::vector<std::thread> threads;
    
    // TODO: Launch worker threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker_thread, resource, i, operations_per_thread);
    }
    
    // TODO: Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    std::cout << "All threads completed. Final ref count: " << resource.use_count() << "\n";
}

int main() {
    demonstrate_performance_comparison();
    demonstrate_thread_safety();
    
    return 0;
}
```

**Learning Goals**:
- shared_ptr thread safety guarantees
- Performance overhead of reference counting
- Safe concurrent shared_ptr usage patterns
- When to choose shared_ptr vs alternatives

---

### Problem 2.3: std::enable_shared_from_this (15 minutes)

**Background**: Learn to safely get shared_ptr to `this` inside member functions.

**Task**: Implement classes that need to create shared_ptr to themselves.

**Requirements**:
1. Use std::enable_shared_from_this correctly
2. Understand the problem it solves
3. Implement safe async operations
4. Handle the requirements and limitations

**Starter Code**:
```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <functional>

// TODO: Implement class that can safely share itself
class AsyncProcessor : public std::enable_shared_from_this<AsyncProcessor> {
private:
    std::string name_;
    std::vector<std::function<void()>> pending_operations_;
    
public:
    AsyncProcessor(const std::string& name) : name_(name) {
        std::cout << "AsyncProcessor '" << name_ << "' created\n";
    }
    
    ~AsyncProcessor() {
        std::cout << "AsyncProcessor '" << name_ << "' destroyed\n";
    }
    
    // TODO: Method that needs to pass 'this' to async operation
    void schedule_operation(const std::string& operation_name) {
        std::cout << "Scheduling operation: " << operation_name << "\n";
        
        // TODO: Use shared_from_this() to safely capture self
        auto self = shared_from_this();
        
        auto operation = [self, operation_name]() {
            self->execute_operation(operation_name);
        };
        
        pending_operations_.push_back(operation);
    }
    
    void execute_pending() {
        std::cout << "Executing " << pending_operations_.size() << " pending operations\n";
        
        for (auto& operation : pending_operations_) {
            operation();
        }
        
        pending_operations_.clear();
    }
    
private:
    void execute_operation(const std::string& operation_name) {
        std::cout << "AsyncProcessor '" << name_ << "' executing: " << operation_name << "\n";
    }
};

// TODO: Demonstrate the problem without enable_shared_from_this
class ProblematicProcessor {
private:
    std::string name_;
    
public:
    ProblematicProcessor(const std::string& name) : name_(name) {
        std::cout << "ProblematicProcessor '" << name_ << "' created\n";
    }
    
    ~ProblematicProcessor() {
        std::cout << "ProblematicProcessor '" << name_ << "' destroyed\n";
    }
    
    // TODO: Dangerous method that tries to create shared_ptr from this
    void dangerous_self_reference() {
        std::cout << "WARNING: Creating dangerous self-reference\n";
        // TODO: Show why this is dangerous
        // std::shared_ptr<ProblematicProcessor> self(this); // DANGER!
    }
};

void demonstrate_safe_self_reference() {
    std::cout << "=== Safe Self-Reference with enable_shared_from_this ===\n";
    
    // TODO: Create AsyncProcessor using make_shared
    auto processor = std::make_shared<AsyncProcessor>("SafeProcessor");
    std::cout << "Initial ref count: " << processor.use_count() << "\n";
    
    // TODO: Schedule operations that capture self
    processor->schedule_operation("Task1");
    processor->schedule_operation("Task2");
    processor->schedule_operation("Task3");
    
    std::cout << "After scheduling, ref count: " << processor.use_count() << "\n";
    
    // TODO: Execute operations
    processor->execute_pending();
    
    std::cout << "After execution, ref count: " << processor.use_count() << "\n";
}

void demonstrate_problematic_approach() {
    std::cout << "\n=== Problematic Approach (Commented Out) ===\n";
    
    auto processor = std::make_shared<ProblematicProcessor>("DangerousProcessor");
    
    // TODO: Show what would happen (but don't actually do it)
    std::cout << "This would be dangerous if uncommented:\n";
    std::cout << "- Creating shared_ptr from raw 'this' pointer\n";
    std::cout << "- Would cause double-delete when both shared_ptrs are destroyed\n";
    std::cout << "- enable_shared_from_this prevents this problem\n";
}

// TODO: Factory function that demonstrates proper usage
std::shared_ptr<AsyncProcessor> create_processor(const std::string& name) {
    // TODO: Create using make_shared (required for enable_shared_from_this)
    return std::make_shared<AsyncProcessor>(name);
}

int main() {
    demonstrate_safe_self_reference();
    demonstrate_problematic_approach();
    
    std::cout << "\n=== Factory Function Usage ===\n";
    auto processor = create_processor("FactoryCreated");
    processor->schedule_operation("FactoryTask");
    processor->execute_pending();
    
    return 0;
}
```

**Learning Goals**:
- enable_shared_from_this usage and requirements
- Problems with creating shared_ptr from raw this
- Safe async operation patterns
- Factory function requirements

---

## Problem Set 3: std::weak_ptr and Circular References (30 minutes)

### Problem 3.1: Breaking Circular References (20 minutes)

**Background**: Use std::weak_ptr to break circular references that would cause memory leaks.

**Task**: Implement parent-child relationships that avoid circular reference problems.

**Requirements**:
1. Create parent-child relationships without memory leaks
2. Use weak_ptr to break cycles
3. Safely access objects through weak_ptr
4. Handle expired weak_ptr correctly

**Starter Code**:
```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Forward declarations
class Parent;
class Child;

class Child {
private:
    std::string name_;
    std::weak_ptr<Parent> parent_;  // Use weak_ptr to break cycle
    int id_;
    
public:
    Child(const std::string& name, int id) : name_(name), id_(id) {
        std::cout << "Child '" << name_ << "' (ID: " << id_ << ") created\n";
    }
    
    ~Child() {
        std::cout << "Child '" << name_ << "' (ID: " << id_ << ") destroyed\n";
    }
    
    // TODO: Set parent using weak_ptr
    void set_parent(std::shared_ptr<Parent> parent) {
        parent_ = parent;
        std::cout << "Child '" << name_ << "' linked to parent\n";
    }
    
    // TODO: Safely access parent
    void visit_parent() {
        // TODO: Use lock() to safely access parent
        if (auto parent = parent_.lock()) {
            std::cout << "Child '" << name_ << "' visiting parent\n";
            // TODO: Call parent method safely
        } else {
            std::cout << "Child '" << name_ << "' - parent no longer exists\n";
        }
    }
    
    // TODO: Check if parent still exists
    bool has_parent() const {
        return !parent_.expired();
    }
    
    const std::string& name() const { return name_; }
    int id() const { return id_; }
};

class Parent {
private:
    std::string name_;
    std::vector<std::shared_ptr<Child>> children_;  // Strong references to children
    
public:
    Parent(const std::string& name) : name_(name) {
        std::cout << "Parent '" << name_ << "' created\n";
    }
    
    ~Parent() {
        std::cout << "Parent '" << name_ << "' destroyed\n";
    }
    
    // TODO: Add child with proper linking
    void add_child(const std::string& child_name) {
        static int next_id = 1;
        
        auto child = std::make_shared<Child>(child_name, next_id++);
        child->set_parent(shared_from_this());
        children_.push_back(child);
        
        std::cout << "Parent '" << name_ << "' adopted child '" << child_name << "'\n";
    }
    
    // TODO: Method called by children
    void interact_with_child(const std::string& child_name) {
        std::cout << "Parent '" << name_ << "' interacting with child '" << child_name << "'\n";
    }
    
    void list_children() const {
        std::cout << "Parent '" << name_ << "' has " << children_.size() << " children:\n";
        for (const auto& child : children_) {
            std::cout << "  - " << child->name() << " (ID: " << child->id() << ")\n";
        }
    }
    
    // TODO: Remove child by name
    void remove_child(const std::string& child_name) {
        auto it = std::find_if(children_.begin(), children_.end(),
            [&child_name](const std::shared_ptr<Child>& child) {
                return child->name() == child_name;
            });
            
        if (it != children_.end()) {
            std::cout << "Parent '" << name_ << "' removing child '" << child_name << "'\n";
            children_.erase(it);
        }
    }
    
    const std::string& name() const { return name_; }
};

// TODO: Make Parent inherit from enable_shared_from_this
class FullParent : public std::enable_shared_from_this<FullParent> {
private:
    std::string name_;
    std::vector<std::shared_ptr<Child>> children_;
    
public:
    FullParent(const std::string& name) : name_(name) {
        std::cout << "FullParent '" << name_ << "' created\n";
    }
    
    ~FullParent() {
        std::cout << "FullParent '" << name_ << "' destroyed\n";
    }
    
    void add_child(const std::string& child_name) {
        static int next_id = 100;
        
        auto child = std::make_shared<Child>(child_name, next_id++);
        child->set_parent(shared_from_this());  // Now this works!
        children_.push_back(child);
        
        std::cout << "FullParent '" << name_ << "' adopted child '" << child_name << "'\n";
    }
    
    void interact_with_child(const std::string& child_name) {
        std::cout << "FullParent '" << name_ << "' interacting with child '" << child_name << "'\n";
    }
    
    void list_children() const {
        std::cout << "FullParent '" << name_ << "' has " << children_.size() << " children:\n";
        for (const auto& child : children_) {
            std::cout << "  - " << child->name() << " (ID: " << child->id() << ")\n";
        }
    }
    
    const std::string& name() const { return name_; }
};

void demonstrate_circular_reference_solution() {
    std::cout << "=== Circular Reference Solution ===\n";
    
    // TODO: Create parent and children
    auto parent = std::make_shared<FullParent>("MainParent");
    
    parent->add_child("Alice");
    parent->add_child("Bob"); 
    parent->add_child("Charlie");
    
    parent->list_children();
    
    // TODO: Have children visit parent
    std::cout << "\nChildren visiting parent:\n";
    // Note: In a real scenario, you'd store child references to call visit_parent()
    
    std::cout << "\nParent going out of scope...\n";
}

void demonstrate_weak_ptr_expiration() {
    std::cout << "\n=== Weak Pointer Expiration Demo ===\n";
    
    std::shared_ptr<Child> child_ptr;
    
    {
        auto parent = std::make_shared<FullParent>("TemporaryParent");
        
        auto child = std::make_shared<Child>("OrphanChild", 999);
        child->set_parent(parent);
        child_ptr = child;
        
        std::cout << "Child has parent: " << child->has_parent() << "\n";
        child->visit_parent();
        
        std::cout << "Parent scope ending...\n";
    }
    
    std::cout << "\nAfter parent destroyed:\n";
    std::cout << "Child has parent: " << child_ptr->has_parent() << "\n";
    child_ptr->visit_parent();
}

int main() {
    demonstrate_circular_reference_solution();
    demonstrate_weak_ptr_expiration();
    
    std::cout << "\nAll objects should be properly cleaned up!\n";
    
    return 0;
}
```

**Learning Goals**:
- Identifying and solving circular reference problems
- weak_ptr usage for breaking cycles
- Safe access patterns with lock()
- Understanding when weak_ptr expires

---

### Problem 3.2: Observer Pattern with weak_ptr (10 minutes)

**Background**: Implement the observer pattern using weak_ptr to avoid keeping observers alive unnecessarily.

**Task**: Create an observer pattern that allows observers to be automatically removed when destroyed.

**Requirements**:
1. Implement subject-observer pattern with weak_ptr
2. Automatically handle observer cleanup
3. Safely notify observers that may have been destroyed
4. Show the benefits over raw pointer observers

**Starter Code**:
```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

// Forward declaration
class EventObserver;

class EventSubject {
private:
    std::vector<std::weak_ptr<EventObserver>> observers_;
    std::string subject_name_;
    
public:
    EventSubject(const std::string& name) : subject_name_(name) {
        std::cout << "EventSubject '" << name << "' created\n";
    }
    
    ~EventSubject() {
        std::cout << "EventSubject '" << subject_name_ << "' destroyed\n";
    }
    
    // TODO: Add observer using weak_ptr
    void add_observer(std::shared_ptr<EventObserver> observer) {
        observers_.push_back(observer);
        std::cout << "Observer added to '" << subject_name_ << "'\n";
        cleanup_expired_observers();
    }
    
    // TODO: Notify all observers, skipping expired ones
    void notify_observers(const std::string& event) {
        std::cout << "Subject '" << subject_name_ << "' notifying observers of event: " << event << "\n";
        
        int notified = 0;
        int expired = 0;
        
        for (auto& weak_observer : observers_) {
            if (auto observer = weak_observer.lock()) {
                // TODO: Notify observer
                notified++;
            } else {
                expired++;
            }
        }
        
        std::cout << "  Notified: " << notified << " observers, " << expired << " were expired\n";
        
        if (expired > 0) {
            cleanup_expired_observers();
        }
    }
    
    // TODO: Clean up expired weak_ptr references
    void cleanup_expired_observers() {
        auto old_size = observers_.size();
        
        observers_.erase(
            std::remove_if(observers_.begin(), observers_.end(),
                [](const std::weak_ptr<EventObserver>& weak_ptr) {
                    return weak_ptr.expired();
                }),
            observers_.end()
        );
        
        auto removed = old_size - observers_.size();
        if (removed > 0) {
            std::cout << "  Cleaned up " << removed << " expired observer references\n";
        }
    }
    
    size_t observer_count() const {
        return observers_.size();
    }
    
    const std::string& name() const { return subject_name_; }
};

class EventObserver {
private:
    std::string observer_name_;
    
public:
    EventObserver(const std::string& name) : observer_name_(name) {
        std::cout << "EventObserver '" << name << "' created\n";
    }
    
    ~EventObserver() {
        std::cout << "EventObserver '" << observer_name_ << "' destroyed\n";
    }
    
    // TODO: Handle event notification
    void on_event(const std::string& event, const std::string& subject_name) {
        std::cout << "  Observer '" << observer_name_ << "' received event '" 
                  << event << "' from '" << subject_name << "'\n";
    }
    
    const std::string& name() const { return observer_name_; }
};

void demonstrate_observer_pattern() {
    std::cout << "=== Observer Pattern with weak_ptr ===\n";
    
    auto subject = std::make_shared<EventSubject>("NewsPublisher");
    
    // TODO: Create observers
    auto observer1 = std::make_shared<EventObserver>("Reader1");
    auto observer2 = std::make_shared<EventObserver>("Reader2");
    auto observer3 = std::make_shared<EventObserver>("Reader3");
    
    // TODO: Register observers
    subject->add_observer(observer1);
    subject->add_observer(observer2);
    subject->add_observer(observer3);
    
    std::cout << "\nSubject has " << subject->observer_count() << " observers\n";
    
    // TODO: Notify observers
    subject->notify_observers("Breaking News!");
    
    std::cout << "\nDestroying observer2...\n";
    observer2.reset();
    
    subject->notify_observers("Update News");
    
    std::cout << "\nObserver count: " << subject->observer_count() << "\n";
    
    {
        std::cout << "\nCreating temporary observer...\n";
        auto temp_observer = std::make_shared<EventObserver>("TempReader");
        subject->add_observer(temp_observer);
        
        subject->notify_observers("Temporary Update");
        std::cout << "\nTemporary observer going out of scope...\n";
    }
    
    std::cout << "\nAfter temporary observer destroyed:\n";
    subject->notify_observers("Final Update");
}

int main() {
    demonstrate_observer_pattern();
    
    std::cout << "\nPattern demonstration complete.\n";
    
    return 0;
}
```

**Learning Goals**:
- Observer pattern with automatic cleanup
- Safe observer notification with weak_ptr
- Expired weak_ptr handling
- Memory-safe observer patterns

---

## Submission Guidelines

### What to Submit

1. **Source code files** for all problems with clear comments
2. **Compilation and execution output** showing your programs working
3. **Brief reflection** (2-3 paragraphs) on RAII principles and smart pointer benefits

### File Organization
```
chapter11_solutions/
├── problem_set_1/
│   ├── problem_1_1_raii_principles.cpp
│   ├── problem_1_2_unique_ptr_fundamentals.cpp
│   └── problem_1_3_custom_deleters.cpp
├── problem_set_2/
│   ├── problem_2_1_shared_ownership.cpp
│   ├── problem_2_2_thread_safety_performance.cpp
│   └── problem_2_3_shared_from_this.cpp
├── problem_set_3/
│   ├── problem_3_1_circular_references.cpp
│   └── problem_3_2_observer_pattern.cpp
└── README.md (with compilation notes and reflection)
```

### Evaluation Criteria

1. **Correctness** (40%): Programs compile and work as specified
2. **RAII Usage** (25%): Proper resource management and smart pointer usage
3. **Code Quality** (20%): Clean, readable, well-organized code  
4. **Best Practices** (15%): Following modern C++ memory management idioms

### Time Management Tips

- **Problem Set 1**: Focus on understanding RAII principles first
- **Problem Set 2**: Pay attention to reference counting behavior
- **Problem Set 3**: Understand why weak_ptr is needed and when to use it

### Common Pitfalls to Avoid

1. **Double Delete**: Never create multiple shared_ptr from the same raw pointer
2. **Circular References**: Always consider object lifetime relationships
3. **Premature Optimization**: Don't use shared_ptr when unique_ptr suffices
4. **enable_shared_from_this**: Remember to create objects with make_shared
5. **Thread Safety**: Understand what is and isn't thread-safe with smart pointers

### Getting Help

- Refer to `quick-help.md` for syntax reminders
- Check solution files if completely stuck on smart pointer syntax
- Focus on understanding ownership semantics

---

## Extension Challenges (Optional)

For students who finish early:

1. **Custom Smart Pointer**: Implement your own simple smart pointer class
2. **Intrusive Pointers**: Research and implement reference counting within objects
3. **Memory Pool**: Combine smart pointers with custom memory allocation
4. **Async Safe**: Design async-safe shared resource access patterns

## Success Criteria

You've mastered Chapter 11 smart pointer concepts when you can:
- Choose the appropriate smart pointer type for different ownership scenarios
- Implement RAII patterns that prevent resource leaks
- Design object relationships that avoid circular references
- Use smart pointers safely in concurrent environments
- Understand the performance characteristics of each smart pointer type

Remember: Smart pointers are about expressing ownership semantics clearly. The compiler handles the mechanics, but you must design the ownership relationships correctly!