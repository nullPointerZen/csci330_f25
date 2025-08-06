# Chapter 11: Smart Pointers - Lesson Plan

**Target Audience**: Students with Python/Java background  
**Time Budget**: 2.5 hours maximum  
**Prerequisites**: Chapters 1-10 (basic programming, types, references, object lifecycle, polymorphism, templates, expressions, control flow, functions, and testing)

## Development Environment Setup
**Continue using your chosen workflow from previous chapters:**
- **Option A**: Docker + Command Line 
- **Option B**: VS Code + Docker (excellent for smart pointer debugging and ownership visualization)
- **Option C**: VS Code + Local Compiler

**For Chapter 11's smart pointer concepts, debugger shows ownership transfer and reference counting!**

---

## Learning Objectives
By the end of this chapter, students will be able to:
1. Explain the problems with raw pointers and manual memory management
2. Use `unique_ptr` for automatic memory management with exclusive ownership
3. Use `shared_ptr` for automatic memory management with shared ownership
4. Use `weak_ptr` to break circular references in shared ownership scenarios
5. Apply RAII principles using smart pointers
6. Convert legacy raw pointer code to use smart pointers

## Lesson Structure (2.5 hours total)

### Part 1: The Problem with Raw Pointers (25 minutes)

#### Memory Management Review (10 minutes)
- Quick review of stack vs heap memory
- Problems with manual `new`/`delete`:
  - Memory leaks
  - Double deletion
  - Dangling pointers
  - Exception safety issues

```cpp
// Example of problematic raw pointer usage
void risky_function() {
    int* data = new int[1000];
    // What if an exception is thrown here?
    process_data(data);  // Could throw!
    delete[] data;       // May never execute
}
```

#### Connecting to Student Experience (15 minutes)
- Compare to garbage collection in Python/Java
- Discuss why C++ gives manual control
- Introduce RAII (Resource Acquisition Is Initialization) concept
- Preview: Smart pointers give us "automatic memory management" within C++'s manual control paradigm

### Part 2: `unique_ptr` - Exclusive Ownership (45 minutes)

#### Basic `unique_ptr` Usage (20 minutes)
```cpp
#include <memory>

// Creating unique_ptr
std::unique_ptr<int> ptr = std::make_unique<int>(42);
std::unique_ptr<int[]> arr = std::make_unique<int[]>(100);

// Using unique_ptr
*ptr = 50;
arr[0] = 10;

// Automatic cleanup when ptr goes out of scope
```

#### Key `unique_ptr` Properties (15 minutes)
- Exclusive ownership - cannot be copied
- Move semantics for transferring ownership
- Automatic cleanup with RAII
- Zero overhead compared to raw pointers

```cpp
std::unique_ptr<int> create_resource() {
    return std::make_unique<int>(100);  // Move semantics
}

void use_resource() {
    auto resource = create_resource();  // Ownership transferred
    // resource automatically cleaned up at end of scope
}
```

#### Common `unique_ptr` Operations (10 minutes)
- `get()` - access raw pointer (use sparingly)
- `reset()` - replace managed object
- `release()` - release ownership
- Custom deleters (mention but don't implement)

### Part 3: `shared_ptr` - Shared Ownership (45 minutes)

#### When Shared Ownership is Needed (10 minutes)
- Multiple objects need access to same resource
- Resource lifetime unclear at compile time
- Compare to reference counting in Python

#### Basic `shared_ptr` Usage (20 minutes)
```cpp
// Creating shared_ptr
std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
std::shared_ptr<int> ptr2 = ptr1;  // Both share ownership

// Reference counting
std::cout << "Reference count: " << ptr1.use_count() << std::endl;

// Last shared_ptr cleans up automatically
```

#### `shared_ptr` in Practice (15 minutes)
```cpp
class Document {
    std::string content;
public:
    Document(std::string text) : content(std::move(text)) {}
    const std::string& get_content() const { return content; }
};

class Editor {
    std::shared_ptr<Document> doc;
public:
    Editor(std::shared_ptr<Document> d) : doc(std::move(d)) {}
    void edit() { /* modify document */ }
};

class Viewer {
    std::shared_ptr<Document> doc;
public:
    Viewer(std::shared_ptr<Document> d) : doc(std::move(d)) {}
    void display() { /* show document */ }
};
```

### Part 4: `weak_ptr` - Breaking Cycles (30 minutes)

#### The Circular Reference Problem (10 minutes)
```cpp
struct Parent;
struct Child;

struct Parent {
    std::shared_ptr<Child> child;
    ~Parent() { std::cout << "Parent destroyed\n"; }
};

struct Child {
    std::shared_ptr<Parent> parent;  // Creates cycle!
    ~Child() { std::cout << "Child destroyed\n"; }
};
// Neither destructor ever called - memory leak!
```

#### `weak_ptr` Solution (15 minutes)
```cpp
struct Parent {
    std::shared_ptr<Child> child;
    ~Parent() { std::cout << "Parent destroyed\n"; }
};

struct Child {
    std::weak_ptr<Parent> parent;  // Breaks the cycle
    ~Child() { std::cout << "Child destroyed\n"; }
    
    void use_parent() {
        if (auto p = parent.lock()) {  // Convert to shared_ptr
            // Use p safely
        }
    }
};
```

#### `weak_ptr` Operations (5 minutes)
- `lock()` - get `shared_ptr` if object still exists
- `expired()` - check if object has been destroyed
- No direct access to managed object

### Part 5: Practical Guidelines and Best Practices (35 minutes)

#### Choosing the Right Smart Pointer (10 minutes)
- Use `unique_ptr` by default
- Use `shared_ptr` when multiple owners needed
- Use `weak_ptr` to break cycles or observe without owning
- Avoid `shared_ptr` unless truly necessary (performance cost)

#### Migration Strategies (15 minutes)
- Converting legacy code step by step
- Using smart pointers with C APIs
- Factory functions returning smart pointers

```cpp
// Factory pattern with smart pointers
class ResourceFactory {
public:
    static std::unique_ptr<Resource> create_resource(int type) {
        switch(type) {
            case 1: return std::make_unique<ResourceA>();
            case 2: return std::make_unique<ResourceB>();
            default: return nullptr;
        }
    }
};
```

#### Common Pitfalls to Avoid (10 minutes)
- Don't mix raw pointers and smart pointers for same object
- Don't use `get()` to create new smart pointers
- Prefer `make_unique` and `make_shared` over `new`
- Be careful with circular references

### Part 6: Hands-on Exercise and Wrap-up (10 minutes)

#### Quick Exercise
Students convert a simple raw pointer class to use smart pointers:

```cpp
// Before: Raw pointers
class ResourceManager {
    Resource* resource;
public:
    ResourceManager() : resource(new Resource()) {}
    ~ResourceManager() { delete resource; }
    // Copy constructor and assignment needed!
};

// After: Smart pointers
class ResourceManager {
    std::unique_ptr<Resource> resource;
public:
    ResourceManager() : resource(std::make_unique<Resource>()) {}
    // Rule of zero - compiler handles everything!
};
```

#### Summary (5 minutes)
- Smart pointers provide automatic memory management
- `unique_ptr` for exclusive ownership (most common)
- `shared_ptr` for shared ownership (when needed)
- `weak_ptr` to break circular references
- RAII ensures resources are cleaned up automatically
- Smart pointers make C++ code safer and easier to reason about

## Assessment Checkpoints

### Quick Understanding Checks
1. "What happens to memory when a `unique_ptr` goes out of scope?"
2. "How does `shared_ptr` know when to delete the managed object?"
3. "Why can't we copy a `unique_ptr`?"
4. "What problem does `weak_ptr` solve?"

### Code Reading Exercise
Present students with code using different smart pointer types and ask them to predict the output or identify problems.

### Practical Application
Students should be able to:
- Replace raw pointers with appropriate smart pointers
- Explain their choice of smart pointer type
- Identify and fix circular reference problems

## Materials Needed
- Compiler with C++14 support (for `make_unique`)
- Example programs demonstrating each smart pointer type
- Code samples showing common pitfalls
- Reference sheets for smart pointer operations

## Extension Topics (For Advanced Students)
- Custom deleters for `unique_ptr` and `shared_ptr`
- `enable_shared_from_this` pattern
- Performance considerations of smart pointers
- Smart pointers in multithreaded environments
- `std::unique_ptr` with arrays vs `std::vector`

## Connection to Previous Chapters
- Builds on RAII concepts from object lifecycle (Chapter 4)
- Uses templates extensively (Chapter 6)
- Applies exception safety principles
- Integrates with function design patterns (Chapter 9)

## Preparation for Next Chapter
Smart pointers provide foundation for:
- STL containers that manage memory automatically
- Exception-safe resource management
- Modern C++ design patterns
- Thread-safe programming concepts

---

**Note for Instructors**: 
- Emphasize practical benefits over technical details
- Use analogies to garbage collection familiar from Python/Java
- Focus on "which smart pointer to use when" rather than implementation details
- Encourage students to think of smart pointers as "automatic memory management tools"
- Students coming from garbage-collected languages may initially resist manual memory concepts - emphasize that smart pointers give them familiar automatic behavior within C++'s performance-oriented design