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
- **Time expectation**: 1.5 hours total for both problem sets
- Test all programs thoroughly before submission

**Target Audience**: Students with Python/Java background  
**Total Time**: 1.5 hours (90 minutes)  
**Prerequisites**: Chapters 1-10 completed + Chapter 11 lesson  

## Problem Set Structure

- **Problem Set 1**: RAII and Smart Pointer Fundamentals (45 minutes)
- **Problem Set 2**: Advanced Smart Pointers and Real-World Applications (45 minutes)

---

## Problem Set 1: RAII and Smart Pointer Fundamentals (45 minutes)

### Problem 1.1: RAII Principles and std::unique_ptr (25 minutes)

**Background**: Coming from Python's automatic garbage collection or Java's try-with-resources, learn C++ RAII principles and std::unique_ptr.

**Task**: Create RAII classes and use std::unique_ptr for automatic resource management.

**Requirements**:
1. Implement RAII wrapper for file handles
2. Use std::unique_ptr for dynamic memory management
3. Demonstrate ownership transfer with move semantics
4. Show automatic cleanup and exception safety

**Complete Template**:
```cpp
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <memory>
#include <string>

// RAII file wrapper
class FileHandle {
private:
    std::ofstream file_;
    std::string filename_;
    
public:
    FileHandle(const std::string& filename) : filename_(filename) {
        file_.open(filename);
        if (!file_.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::cout << "File '" << filename_ << "' opened\n";
    }
    
    ~FileHandle() {
        if (file_.is_open()) {
            file_.close();
            std::cout << "File '" << filename_ << "' closed\n";
        }
    }
    
    void write(const std::string& data) {
        if (file_.is_open()) {
            file_ << data;
        }
    }
    
    bool is_open() const {
        return file_.is_open();
    }
};

// Resource class for unique_ptr demonstration
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
};

// TODO: Factory function that returns unique_ptr
std::unique_ptr<Resource> create_resource(const std::string& name, int id) {
    // Use make_unique to create and return resource
    return std::make_unique<Resource>(name, id);
}

// TODO: Function that demonstrates ownership transfer
void process_resource(std::unique_ptr<Resource> resource) {
    if (resource) {
        std::cout << "Processing ";
        resource->use();
        // Resource will be automatically destroyed when function ends
    }
}

void demonstrate_raii_and_unique_ptr() {
    std::cout << "=== RAII File Management ===\n";
    
    try {
        FileHandle file("test_output.txt");
        file.write("Hello from RAII!\n");
        file.write("This file will be automatically closed.\n");
        // File automatically closed when file goes out of scope
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    
    std::cout << "\n=== unique_ptr Fundamentals ===\n";
    
    // Create resource using factory
    auto resource1 = create_resource("Resource1", 100);
    resource1->use();
    
    // Demonstrate ownership transfer
    std::cout << "\nTransferring ownership...\n";
    process_resource(std::move(resource1));
    
    // resource1 is now nullptr
    if (!resource1) {
        std::cout << "resource1 is now nullptr after move\n";
    }
    
    // Create array with unique_ptr
    std::cout << "\n=== unique_ptr Array Management ===\n";
    auto numbers = std::make_unique<int[]>(5);
    for (int i = 0; i < 5; ++i) {
        numbers[i] = i * 10;
    }
    
    for (int i = 0; i < 5; ++i) {
        std::cout << "numbers[" << i << "] = " << numbers[i] << "\n";
    }
    // Array automatically deleted when numbers goes out of scope
}

int main() {
    demonstrate_raii_and_unique_ptr();
    
    std::cout << "\nAll resources automatically cleaned up!\n";
    return 0;
}
```

### Problem 1.2: Custom Deleters and C API Integration (20 minutes)

**Background**: Use custom deleters for specialized cleanup and C API integration.

**Task**: Implement custom deleters for different resource types including C APIs.

**Requirements**:
1. Create custom deleters for C API resources (like FILE*)
2. Use logging deleters for debugging
3. Handle specialized cleanup scenarios
4. Integrate C APIs safely with smart pointers

**Complete Template**:
```cpp
#include <iostream>
#include <memory>
#include <cstdio>

// Custom deleter for FILE*
struct FileCloser {
    void operator()(FILE* file) const {
        if (file) {
            fclose(file);
            std::cout << "FILE* closed by custom deleter\n";
        }
    }
};

// Custom deleter with logging
struct LoggingDeleter {
    std::string resource_name;
    
    LoggingDeleter(const std::string& name) : resource_name(name) {}
    
    void operator()(int* ptr) const {
        if (ptr) {
            std::cout << "LoggingDeleter: Destroying " << resource_name 
                      << " with value " << *ptr << "\n";
            delete ptr;
        }
    }
};

void demonstrate_custom_deleters() {
    std::cout << "=== Custom Deleter for FILE* ===\n";
    
    // Use unique_ptr with custom deleter for FILE*
    std::unique_ptr<FILE, FileCloser> file(fopen("test_custom.txt", "w"));
    
    if (file) {
        fprintf(file.get(), "Hello from custom deleter!\n");
        std::cout << "File written successfully\n";
        // File will be automatically closed by custom deleter
    } else {
        std::cout << "Failed to open file\n";
    }
    
    std::cout << "\n=== Logging Deleter ===\n";
    
    // Use logging deleter
    auto deleter = LoggingDeleter("TestResource");
    std::unique_ptr<int, LoggingDeleter> ptr(new int(42), deleter);
    
    std::cout << "Value: " << *ptr << "\n";
    // Destruction will be logged
    
    std::cout << "\n=== Lambda Deleter ===\n";
    
    // Create lambda deleter
    auto lambda_deleter = [](int* ptr) {
        std::cout << "Lambda deleter cleaning up value: " << *ptr << "\n";
        delete ptr;
    };
    
    // Use lambda deleter with unique_ptr
    std::unique_ptr<int, decltype(lambda_deleter)> lambda_ptr(
        new int(99), lambda_deleter);
    
    std::cout << "Lambda ptr value: " << *lambda_ptr << "\n";
    
    std::cout << "\n=== C API Integration Example ===\n";
    
    // Simulate C API that allocates memory
    auto c_api_resource = std::unique_ptr<char[], void(*)(void*)>(
        static_cast<char*>(malloc(100)),
        [](void* ptr) {
            std::cout << "Freeing C API resource with custom deleter\n";
            free(ptr);
        }
    );
    
    if (c_api_resource) {
        strcpy(c_api_resource.get(), "C API resource managed by smart pointer");
        std::cout << "C API resource: " << c_api_resource.get() << "\n";
    }
}

int main() {
    demonstrate_custom_deleters();
    
    std::cout << "\nAll resources cleaned up automatically!\n";
    return 0;
}
```

---

## Problem Set 2: Advanced Smart Pointers and Real-World Applications (45 minutes)

### Problem 2.1: Shared Ownership and Reference Counting (25 minutes)

**Background**: Use std::shared_ptr for shared ownership and understand reference counting behavior.

**Task**: Implement shared ownership scenarios with observers and reference counting.

**Requirements**:
1. Create shared resources with multiple owners
2. Monitor reference counting behavior
3. Use std::make_shared for efficiency
4. Implement observer pattern with shared ownership

**Complete Template**:
```cpp
#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Shared resource class
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

// Observer class that shares ownership
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

void demonstrate_shared_ownership() {
    std::cout << "=== Shared Ownership Demo ===\n";
    
    // Create shared resource
    auto resource = std::make_shared<SharedResource>("SharedData", 100);
    std::cout << "Initial ref count: " << resource.use_count() << "\n\n";
    
    {
        // Create observers that share the resource
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
    demonstrate_shared_ownership();
    std::cout << "\nAll resources should be destroyed now.\n";
    
    return 0;
}
```

### Problem 2.2: Circular References and weak_ptr (20 minutes)

**Background**: Use std::weak_ptr to break circular references that cause memory leaks.

**Task**: Implement parent-child relationships avoiding circular reference problems.

**Requirements**:
1. Create parent-child relationships without memory leaks
2. Use weak_ptr to break cycles
3. Safely access objects through weak_ptr
4. Handle expired weak_ptr correctly

**Complete Template**:
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
    
    void set_parent(std::shared_ptr<Parent> parent) {
        parent_ = parent;
        std::cout << "Child '" << name_ << "' linked to parent\n";
    }
    
    void visit_parent() {
        // Use lock() to safely access parent
        if (auto parent = parent_.lock()) {
            std::cout << "Child '" << name_ << "' visiting parent\n";
            // TODO: Call parent method safely
        } else {
            std::cout << "Child '" << name_ << "' - parent no longer exists\n";
        }
    }
    
    bool has_parent() const {
        return !parent_.expired();
    }
    
    const std::string& name() const { return name_; }
    int id() const { return id_; }
};

class Parent : public std::enable_shared_from_this<Parent> {
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
    
    void add_child(const std::string& child_name) {
        static int next_id = 1;
        
        auto child = std::make_shared<Child>(child_name, next_id++);
        child->set_parent(shared_from_this());
        children_.push_back(child);
        
        std::cout << "Parent '" << name_ << "' adopted child '" << child_name << "'\n";
    }
    
    void interact_with_child(const std::string& child_name) {
        std::cout << "Parent '" << name_ << "' interacting with child '" << child_name << "'\n";
    }
    
    void list_children() const {
        std::cout << "Parent '" << name_ << "' has " << children_.size() << " children:\n";
        for (const auto& child : children_) {
            std::cout << "  - " << child->name() << " (ID: " << child->id() << ")\n";
        }
    }
    
    const std::string& name() const { return name_; }
};

void demonstrate_circular_reference_solution() {
    std::cout << "=== Circular Reference Solution ===\n";
    
    auto parent = std::make_shared<Parent>("MainParent");
    
    parent->add_child("Alice");
    parent->add_child("Bob"); 
    parent->add_child("Charlie");
    
    parent->list_children();
    
    std::cout << "\nParent going out of scope...\n";
}

void demonstrate_weak_ptr_expiration() {
    std::cout << "\n=== Weak Pointer Expiration Demo ===\n";
    
    std::shared_ptr<Child> child_ptr;
    
    {
        auto parent = std::make_shared<Parent>("TemporaryParent");
        
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
    
    std::cout << "\nAll objects properly cleaned up!\n";
    
    return 0;
}
```

---

## Time Distribution Summary
- **Problem Set 1** (45 min): RAII principles and smart pointer fundamentals
- **Problem Set 2** (45 min): Advanced shared ownership and circular reference handling
- **Total: 1.5 hours**

## Learning Progression
1. **Set 1**: Students master RAII principles, unique_ptr, and custom deleters
2. **Set 2**: Students learn shared ownership, reference counting, and circular reference solutions

## Success Criteria
Students successfully complete when they can:
- Implement RAII patterns that prevent resource leaks
- Choose appropriate smart pointer types for different ownership scenarios
- Use shared_ptr and weak_ptr correctly to avoid circular references
- Integrate C APIs safely with smart pointers
- Understand the performance and safety trade-offs of different smart pointer types

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