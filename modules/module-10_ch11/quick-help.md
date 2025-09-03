# Chapter 11: Smart Pointers - Quick Help Guide

**For students with Python/Java background learning C++ RAII and smart pointer memory management**

---

## 🚨 Most Common Mistakes

### 1. Creating Multiple shared_ptr from Raw Pointer
```cpp
// DANGER - Creates separate control blocks!
int* raw_ptr = new int(42);
std::shared_ptr<int> ptr1(raw_ptr);  // Control block 1
std::shared_ptr<int> ptr2(raw_ptr);  // Control block 2 - DOUBLE DELETE!

// SAFE - Use make_shared or copy existing shared_ptr
auto ptr1 = std::make_shared<int>(42);
auto ptr2 = ptr1;  // Same control block, safe sharing
```

### 2. Using std::move with shared_ptr When You Don't Mean It
```cpp
std::shared_ptr<Data> original = std::make_shared<Data>();
std::shared_ptr<Data> moved = std::move(original);  // original is now null!

// If you meant to share ownership, just copy:
std::shared_ptr<Data> shared = original;  // Both valid, reference count = 2
```

### 3. Circular References with shared_ptr
```cpp
// MEMORY LEAK - Circular reference prevents deletion
struct Parent {
    std::shared_ptr<Child> child;
};
struct Child {
    std::shared_ptr<Parent> parent;  // WRONG - creates cycle
};

// FIX - Use weak_ptr to break the cycle
struct Child {
    std::weak_ptr<Parent> parent;  // Breaks cycle
};
```

---

## 📋 Smart Pointer Quick Reference

### std::unique_ptr
```cpp
#include <memory>

// Creation (preferred)
auto ptr = std::make_unique<Type>(constructor_args);

// Manual creation (avoid if possible)
std::unique_ptr<Type> ptr(new Type(constructor_args));

// Array version
auto arr = std::make_unique<int[]>(size);
std::unique_ptr<int[]> manual_arr(new int[size]);

// Access
*ptr;           // Dereference
ptr->member;    // Arrow operator
ptr.get();      // Get raw pointer (use carefully)

// Transfer ownership
auto new_owner = std::move(ptr);  // ptr becomes null

// Custom deleter
auto file_ptr = std::unique_ptr<FILE, decltype(&fclose)>(
    fopen("file.txt", "r"), &fclose);
```

### std::shared_ptr
```cpp
#include <memory>

// Creation (always prefer make_shared)
auto ptr = std::make_shared<Type>(constructor_args);

// Copy = shared ownership
auto shared = ptr;  // Both point to same object

// Access
*ptr;               // Dereference
ptr->member;        // Arrow operator
ptr.get();          // Raw pointer
ptr.use_count();    // Reference count
ptr.unique();       // True if only reference

// Reset
ptr.reset();        // Release reference
ptr.reset(new Type(...)); // Replace with new object (avoid)

// Safe casting
auto derived = std::dynamic_pointer_cast<Derived>(base_ptr);
if (derived) { /* cast succeeded */ }
```

### std::weak_ptr
```cpp
#include <memory>

// Creation from shared_ptr
std::shared_ptr<Type> shared = std::make_shared<Type>();
std::weak_ptr<Type> weak = shared;

// Check if still valid
if (auto locked = weak.lock()) {
    // Use locked as shared_ptr
    locked->do_something();
} else {
    // Object was deleted
}

// Alternative check
if (!weak.expired()) {
    auto locked = weak.lock();
    // Use locked, but still check for null!
}

// Get reference count (of original shared_ptr)
weak.use_count();
```

---

## ⚡ RAII Principles Cheat Sheet

### Core RAII Rules
1. **Acquire resources in constructor**
2. **Release resources in destructor**
3. **Copy/move operations handle resource transfer correctly**
4. **No manual delete calls in modern C++**

### RAII Pattern Template
```cpp
class RAIIResource {
private:
    ResourceType* resource_;
    
public:
    // Constructor acquires resource
    RAIIResource(args...) {
        resource_ = acquire_resource(args...);
    }
    
    // Destructor releases resource
    ~RAIIResource() {
        if (resource_) {
            release_resource(resource_);
        }
    }
    
    // Copy constructor (deep copy if needed)
    RAIIResource(const RAIIResource& other) {
        resource_ = copy_resource(other.resource_);
    }
    
    // Move constructor (transfer ownership)
    RAIIResource(RAIIResource&& other) noexcept 
        : resource_(std::exchange(other.resource_, nullptr)) {
    }
    
    // Copy assignment
    RAIIResource& operator=(const RAIIResource& other) {
        if (this != &other) {
            // Release current resource
            if (resource_) release_resource(resource_);
            // Copy new resource
            resource_ = copy_resource(other.resource_);
        }
        return *this;
    }
    
    // Move assignment
    RAIIResource& operator=(RAIIResource&& other) noexcept {
        if (this != &other) {
            // Release current resource
            if (resource_) release_resource(resource_);
            // Take other's resource
            resource_ = std::exchange(other.resource_, nullptr);
        }
        return *this;
    }
};
```

---

## 🔧 When to Use Which Smart Pointer

### Use std::unique_ptr When:
- **Single ownership** - Only one owner at a time
- **Replacing raw pointers** in legacy code
- **RAII** - Automatic cleanup needed
- **Performance critical** - Zero overhead
- **Polymorphism** - Base pointer to derived objects

```cpp
// Good unique_ptr use cases
std::unique_ptr<Shape> create_shape(ShapeType type);
std::vector<std::unique_ptr<Task>> task_queue;
class Widget {
    std::unique_ptr<Impl> pimpl_;  // PIMPL idiom
};
```

### Use std::shared_ptr When:
- **Multiple owners** - Object needs to be shared
- **Callbacks** - Object lifetime uncertain
- **Caches** - Multiple places might hold references
- **Thread safety** - Multiple threads accessing

```cpp
// Good shared_ptr use cases  
std::shared_ptr<Texture> load_texture(const std::string& path);
class Observer {
    std::shared_ptr<Subject> subject_;  // Shared ownership
};
std::vector<std::shared_ptr<Node>> graph_nodes;
```

### Use std::weak_ptr When:
- **Breaking cycles** - Parent-child relationships
- **Observer patterns** - Temporary observation
- **Caching** - Cache entries shouldn't keep objects alive
- **Optional references** - Might be null

```cpp
// Good weak_ptr use cases
class Child {
    std::weak_ptr<Parent> parent_;  // Break parent->child->parent cycle
};
class Cache {
    std::map<Key, std::weak_ptr<Value>> cache_;  // Don't keep values alive
};
```

### Use Raw Pointers When:
- **Non-owning parameters** - Function doesn't take ownership
- **Observing** - Temporary access guaranteed by caller
- **Optional parameters** - Can be nullptr
- **C interop** - Interfacing with C libraries

```cpp
// Good raw pointer use cases
void process(const Data* data);  // Non-owning, can be null
void callback(Widget* widget);   // Caller guarantees lifetime
```

---

## 🔍 Common Debugging Issues

### 1. "Use after free" with unique_ptr
```cpp
// Problem: Using after move
auto ptr = std::make_unique<Data>();
auto moved = std::move(ptr);
ptr->use();  // CRASH: ptr is null after move

// Solution: Check for null or don't use after move
if (ptr) ptr->use();  // Safe
// Or just don't use ptr after move
```

### 2. Circular reference memory leaks
```cpp
// Problem: Objects never deleted due to cycle
auto parent = std::make_shared<Parent>();
auto child = std::make_shared<Child>();
parent->child = child;
child->parent = parent;  // Cycle - memory leak!

// Debug: Check reference counts
std::cout << "Parent refs: " << parent.use_count() << "\n";  // Will be 2
std::cout << "Child refs: " << child.use_count() << "\n";    // Will be 2
// When main ends, both still have count 1, never deleted

// Solution: Use weak_ptr for back-references
child->parent = std::weak_ptr<Parent>(parent);
```

### 3. enable_shared_from_this errors
```cpp
// Problem: Creating shared_ptr in constructor
class Bad : public std::enable_shared_from_this<Bad> {
public:
    Bad() {
        auto self = shared_from_this();  // CRASH: No existing shared_ptr
    }
};

// Solution: Use factory function or init after construction
auto obj = std::make_shared<Bad>();  // Create first
// Now obj->shared_from_this() works
```

---

## 🎯 Best Practices

### Smart Pointer Guidelines
```cpp
// PREFER make_shared/make_unique
auto good = std::make_shared<Type>(args);  // Single allocation
auto bad = std::shared_ptr<Type>(new Type(args));  // Two allocations

// PREFER returning by value (uses move)
std::unique_ptr<Type> create_object() {
    return std::make_unique<Type>();  // Move, not copy
}

// PREFER taking raw pointers as parameters
void process(const Type* obj) {  // Non-owning
    if (obj) obj->do_something();
}

// AVOID unnecessary shared_ptr copying
void inefficient(std::shared_ptr<Type> ptr);  // Copies, increments ref count
void efficient(const std::shared_ptr<Type>& ptr);  // No copy
void even_better(const Type& obj);  // Best if not null
```

### Exception Safety
```cpp
// DANGEROUS: Potential leak if exception thrown
process(std::shared_ptr<Type>(new Type()), 
        std::shared_ptr<Other>(new Other()));  // If second new throws...

// SAFE: Use make_shared
process(std::make_shared<Type>(),
        std::make_shared<Other>());

// SAFE: Create separately
auto ptr1 = std::make_shared<Type>();
auto ptr2 = std::make_shared<Other>();
process(ptr1, ptr2);
```

---

## ⚠️ Performance Considerations

### Smart Pointer Overhead
1. **unique_ptr**: Zero overhead when optimized
2. **shared_ptr**: 
   - 16 bytes (pointer + control block pointer)
   - Atomic reference counting
   - Two allocations if not using make_shared
3. **weak_ptr**: 16 bytes, minimal overhead

### Optimization Tips
```cpp
// FAST: Direct unique_ptr operations
std::unique_ptr<Type> ptr = std::make_unique<Type>();
ptr->fast_operation();

// SLOWER: shared_ptr reference counting
std::shared_ptr<Type> ptr = std::make_shared<Type>();
auto copy = ptr;  // Atomic increment
// auto goes out of scope: atomic decrement

// FASTEST: Raw pointer for short-term use
void process_data(const Type* data) {  // No ref count overhead
    data->process();
}

// Call with: process_data(shared_ptr.get());
```

---

## 🆘 Emergency Syntax Reference

### Quick Creation Patterns
```cpp
// unique_ptr
auto ptr = std::make_unique<Type>(args);
auto arr = std::make_unique<Type[]>(size);

// shared_ptr  
auto ptr = std::make_shared<Type>(args);
auto copy = ptr;  // Shared ownership

// weak_ptr
std::weak_ptr<Type> weak = shared_ptr;
if (auto lock = weak.lock()) { /* use lock */ }

// Custom deleter
auto ptr = std::unique_ptr<Type, Deleter>(new Type, custom_deleter);
```

### Common Conversions
```cpp
// unique_ptr to shared_ptr (transfer ownership)
std::shared_ptr<Type> shared = std::move(unique);

// shared_ptr to weak_ptr (observe)  
std::weak_ptr<Type> weak = shared;

// weak_ptr to shared_ptr (if still alive)
if (auto locked = weak.lock()) { /* use locked */ }

// Get raw pointer (use carefully)
Type* raw = smart_ptr.get();
```

**Remember**: Modern C++ prefers smart pointers over raw `new`/`delete`. When in doubt, start with `unique_ptr` and upgrade to `shared_ptr` only when you need shared ownership!