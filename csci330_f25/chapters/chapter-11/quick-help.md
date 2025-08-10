# Chapter 11: Smart Pointers - Quick Help Guide

## Quick Reference Cards

### 🎯 Which Smart Pointer Should I Use?

```
┌─────────────────────┬──────────────────┬─────────────────────┐
│ Situation           │ Smart Pointer    │ Example             │
├─────────────────────┼──────────────────┼─────────────────────┤
│ Single owner        │ unique_ptr       │ File handle         │
│ Multiple owners     │ shared_ptr       │ Shared document     │
│ Observer (no owner) │ weak_ptr         │ Cache entry         │
│ Breaking cycles     │ weak_ptr         │ Parent-child refs   │
└─────────────────────┴──────────────────┴─────────────────────┘
```

**Rule of Thumb**: Start with `unique_ptr`, upgrade to `shared_ptr` only when you need multiple owners.

---

## Essential Syntax Cheat Sheet

### `unique_ptr` - Exclusive Ownership
```cpp
#include <memory>

// Creation
auto ptr = std::make_unique<int>(42);
auto arr = std::make_unique<int[]>(10);

// Usage
*ptr = 50;
arr[0] = 1;

// Transfer ownership
auto ptr2 = std::move(ptr);  // ptr is now nullptr

// Key methods
ptr.get()      // Get raw pointer (avoid if possible)
ptr.reset()    // Delete current object, optionally assign new one
ptr.release()  // Release ownership, return raw pointer
```

### `shared_ptr` - Shared Ownership
```cpp
// Creation (preferred)
auto ptr1 = std::make_shared<int>(42);

// Sharing
auto ptr2 = ptr1;  // Both now own the object

// Check reference count
std::cout << ptr1.use_count() << std::endl;

// Key methods
ptr.reset()      // Decrease ref count, assign new object
ptr.unique()     // True if ref count == 1
ptr.use_count()  // Current reference count
```

### `weak_ptr` - Non-owning Observer
```cpp
std::shared_ptr<int> shared = std::make_shared<int>(42);
std::weak_ptr<int> weak = shared;

// Safe access
if (auto locked = weak.lock()) {
    // Use 'locked' as shared_ptr
    *locked = 50;
}

// Check if still valid
if (!weak.expired()) {
    // Object still exists
}
```

---

## Common Patterns & Solutions

### Pattern 1: Factory Functions
```cpp
class ShapeFactory {
public:
    static std::unique_ptr<Shape> create(const std::string& type) {
        if (type == "circle") return std::make_unique<Circle>();
        if (type == "square") return std::make_unique<Square>();
        return nullptr;  // Unknown type
    }
};

// Usage
auto shape = ShapeFactory::create("circle");
if (shape) {
    shape->draw();
}
```

### Pattern 2: Pimpl Idiom
```cpp
// header.h
class MyClass {
    struct Impl;
    std::unique_ptr<Impl> pimpl;
public:
    MyClass();
    ~MyClass();  // Must be declared even if = default
    // ... other methods
};

// source.cpp
struct MyClass::Impl {
    // Private implementation details
};

MyClass::MyClass() : pimpl(std::make_unique<Impl>()) {}
MyClass::~MyClass() = default;  // Destructor in .cpp file
```

### Pattern 3: Observer/Subject with weak_ptr
```cpp
class Subject {
    std::vector<std::weak_ptr<Observer>> observers;
public:
    void add_observer(std::shared_ptr<Observer> obs) {
        observers.push_back(obs);
    }
    
    void notify() {
        // Remove expired observers while notifying
        observers.erase(
            std::remove_if(observers.begin(), observers.end(),
                [](const std::weak_ptr<Observer>& w) {
                    if (auto obs = w.lock()) {
                        obs->update();
                        return false;  // Keep this observer
                    }
                    return true;  // Remove expired observer
                }),
            observers.end());
    }
};
```

### Pattern 4: Custom Deleters
```cpp
// For C APIs
auto file = std::unique_ptr<FILE, decltype(&std::fclose)>(
    std::fopen("file.txt", "r"), &std::fclose);

// Lambda deleter
auto ptr = std::unique_ptr<int, std::function<void(int*)>>(
    new int(42),
    [](int* p) { 
        std::cout << "Deleting: " << *p << std::endl;
        delete p; 
    });
```

---

## Troubleshooting Guide

### 🚨 Common Errors & Solutions

#### Error: "Circular reference - objects never destroyed"
```cpp
// ❌ Problem
struct Parent {
    std::shared_ptr<Child> child;
};
struct Child {
    std::shared_ptr<Parent> parent;  // Creates cycle!
};

// ✅ Solution
struct Child {
    std::weak_ptr<Parent> parent;  // Breaks cycle
    
    void use_parent() {
        if (auto p = parent.lock()) {
            // Safely use parent
        }
    }
};
```

#### Error: "Attempting to copy unique_ptr"
```cpp
// ❌ Problem
std::unique_ptr<int> ptr1 = std::make_unique<int>(42);
std::unique_ptr<int> ptr2 = ptr1;  // Compile error!

// ✅ Solution
std::unique_ptr<int> ptr2 = std::move(ptr1);  // Transfer ownership
```

#### Error: "Double free or corruption"
```cpp
// ❌ Problem
int* raw = new int(42);
std::unique_ptr<int> ptr1(raw);
std::unique_ptr<int> ptr2(raw);  // Both will try to delete!

// ✅ Solution
auto ptr1 = std::make_unique<int>(42);
// Share ownership if needed:
std::shared_ptr<int> shared1 = std::make_shared<int>(42);
std::shared_ptr<int> shared2 = shared1;  // Safe sharing
```

#### Error: "Using expired weak_ptr"
```cpp
// ❌ Problem
std::weak_ptr<int> weak;
{
    auto shared = std::make_shared<int>(42);
    weak = shared;
}
*weak.lock() = 50;  // Undefined behavior if object destroyed!

// ✅ Solution
if (auto locked = weak.lock()) {
    *locked = 50;  // Safe - object guaranteed to exist
} else {
    // Handle case where object was destroyed
}
```

---

## Performance Tips

### Memory Allocation Efficiency
```cpp
// ❌ Less efficient (2 allocations)
std::shared_ptr<int> ptr(new int(42));

// ✅ More efficient (1 allocation)
auto ptr = std::make_shared<int>(42);
```

### Choose the Right Tool
```cpp
// For single ownership - fastest
std::unique_ptr<Object> single_owner;

// For shared ownership - some overhead
std::shared_ptr<Object> shared_owner;

// For observation without ownership - minimal overhead
std::weak_ptr<Object> observer;
```

---

## Migration Checklist

### Converting Legacy Code
1. **Identify ownership patterns**
   - Single owner → `unique_ptr`
   - Multiple owners → `shared_ptr`
   - Observers → `weak_ptr`

2. **Replace new/delete**
   ```cpp
   // Old
   Object* obj = new Object();
   // ... use obj
   delete obj;
   
   // New
   auto obj = std::make_unique<Object>();
   // ... use obj
   // Automatic cleanup
   ```

3. **Update function signatures**
   ```cpp
   // Ownership transfer
   void process(std::unique_ptr<Object> obj);
   
   // Shared access
   void use(std::shared_ptr<Object> obj);
   
   // Non-owning access (prefer this for most functions)
   void examine(const Object& obj);
   void examine(Object* obj);  // nullable
   ```

---

## Testing Smart Pointers

### Unit Test Helpers
```cpp
// Check object destruction
class TestObject {
    static int count;
public:
    TestObject() { ++count; }
    ~TestObject() { --count; }
    static int get_count() { return count; }
};

// Test
TEST_CASE("unique_ptr cleanup") {
    int initial_count = TestObject::get_count();
    {
        auto ptr = std::make_unique<TestObject>();
        REQUIRE(TestObject::get_count() == initial_count + 1);
    }
    REQUIRE(TestObject::get_count() == initial_count);  // Cleaned up
}
```

### Mock Objects with Smart Pointers
```cpp
class MockDatabase {
public:
    virtual ~MockDatabase() = default;
    virtual void save(const Data& data) = 0;
};

std::unique_ptr<MockDatabase> create_mock() {
    return std::make_unique<MockDatabaseImpl>();
}
```

---

## Quick Debugging Commands

### GDB/LLDB Commands
```bash
# Print reference count
(gdb) p ptr.use_count()

# Check if weak_ptr is expired
(gdb) p weak_ptr.expired()

# Print managed object
(gdb) p *ptr.get()
```

### Useful Compiler Flags
```bash
# Address sanitizer (detects memory errors)
g++ -fsanitize=address -g your_file.cpp

# Memory sanitizer (detects uninitialized memory)
g++ -fsanitize=memory -g your_file.cpp
```

---

## Remember: The Smart Pointer Mantra

1. **`unique_ptr` by default** - most common case
2. **`shared_ptr` when sharing needed** - multiple owners
3. **`weak_ptr` to break cycles** - observer relationships
4. **Always use `make_unique` and `make_shared`** - safer and more efficient
5. **Avoid mixing raw and smart pointers** - for the same object
6. **Let destructors do the work** - RAII handles cleanup automatically

**"Smart pointers make C++ memory management as automatic as garbage collection, but with deterministic cleanup timing!"**