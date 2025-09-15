# Chapter 5: Quick Help Guide

## Top 5 Virtual Function Errors (Fix These First!)

| Error Message | Likely Cause | Quick Fix |
|--------------|--------------|-----------|
| `cannot instantiate abstract class` | Missing pure virtual function implementation | Implement all `= 0` functions in derived class |
| `no matching function for call` | Forgot `override` keyword or wrong signature | Add `override` and check function signature exactly matches base |
| `invalid use of incomplete type` | Missing virtual destructor | Add `virtual ~BaseClass() = default;` to base class |
| `call of overloaded function is ambiguous` | Multiple inheritance confusion | Use scope resolution: `Base::function()` |
| `object slicing` | Passing by value instead of reference/pointer | Use `Base&` or `Base*` for polymorphic parameters |

## Virtual Function Quick Reference

```cpp
// Abstract base class (interface)
struct Logger {
    virtual ~Logger() = default;                    // Virtual destructor (REQUIRED!)
    virtual void log(const std::string& msg) = 0;  // Pure virtual (= 0)
    virtual void flush() { /* default impl */ }    // Virtual with default
};

// Concrete derived class
struct ConsoleLogger : Logger {
    void log(const std::string& msg) override {    // override keyword (RECOMMENDED!)
        std::cout << msg << "\n";
    }
    // flush() inherited automatically
};

// Usage - polymorphic behavior
Logger* logger = new ConsoleLogger();
logger->log("Hello!");  // Calls ConsoleLogger::log()
delete logger;          // Calls virtual destructor safely
```

## C++ vs Python/Java Quick Comparison

| Need | C++ | Python | Java |
|------|-----|--------|------|
| **Virtual Method** | `virtual void func()` | `def func(self):` (all virtual) | `void func()` (all virtual) |
| **Override** | `void func() override` | `def func(self):` | `@Override void func()` |
| **Abstract Class** | `virtual void func() = 0` | `@abstractmethod def func()` | `abstract void func()` |
| **Inheritance** | `class Child : Parent` | `class Child(Parent):` | `class Child extends Parent` |

## Stuck? Try This!

**Program won't compile?**
1. Check for missing `virtual` keyword in base class
2. Verify all pure virtual functions are implemented
3. Make sure derived class has `override` keyword
4. Add virtual destructor to base class

**Polymorphism not working?**
1. Use pointers or references, not objects by value
2. Make sure function is declared `virtual` in base class
3. Check function signatures match exactly (const, parameters, return type)
4. Verify you're calling through base class pointer/reference

**Memory issues?**
1. Always use virtual destructor in polymorphic base classes
2. Match every `new` with `delete`
3. Consider using smart pointers (`std::unique_ptr`) for automatic cleanup

**Getting overwhelmed?**
- Focus on one virtual function at a time
- Start with concrete classes, add pure virtual later
- Remember: this is like interfaces in Java, but more explicit
- The `override` keyword is your friend - use it always!

## Common Patterns

### Basic Interface Pattern
```cpp
// 1. Define interface
struct Shape {
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

// 2. Implement concrete class
struct Circle : Shape {
    double radius;
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
};

// 3. Use polymorphically
Shape* shape = new Circle(5.0);
std::cout << shape->area() << "\n";
delete shape;
```

### Factory Pattern
```cpp
std::unique_ptr<Logger> create_logger(const std::string& type) {
    if (type == "console") return std::make_unique<ConsoleLogger>();
    if (type == "file") return std::make_unique<FileLogger>("log.txt");
    if (type == "silent") return std::make_unique<SilentLogger>();
    return nullptr;
}
```

### Collection of Polymorphic Objects
```cpp
std::vector<std::unique_ptr<Shape>> shapes;
shapes.push_back(std::make_unique<Circle>(5.0));
shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));

for (const auto& shape : shapes) {
    std::cout << "Area: " << shape->area() << "\n";
}
// Smart pointers automatically clean up!
```

## Memory Safety Tips

**Always do this:**
```cpp
struct Base {
    virtual ~Base() = default;  // Virtual destructor!
};
```

**Consider smart pointers:**
```cpp
std::unique_ptr<Base> obj = std::make_unique<Derived>();
// No need for manual delete!
```

**Avoid object slicing:**
```cpp
// BAD - slicing occurs
void process_shape(Shape shape) { /* ... */ }

// GOOD - polymorphism works
void process_shape(const Shape& shape) { /* ... */ }
void process_shape(Shape* shape) { /* ... */ }
```

## Success Checklist

After Chapter 5, you should be able to:
- [ ] Create abstract base classes with pure virtual functions
- [ ] Implement derived classes that override virtual functions
- [ ] Use the `override` keyword correctly
- [ ] Work with polymorphic objects through base class pointers
- [ ] Include virtual destructors in base classes
- [ ] Understand when to use virtual vs non-virtual functions
- [ ] Apply polymorphism to solve design problems

**Not there yet?** Review the logging example - it demonstrates all key concepts in a practical way.

## When to Use Virtual Functions

**Use virtual functions when:**
- You need different behavior for the same interface
- You want to work with objects through base class pointers
- You're designing a plugin or extensible system
- You need runtime polymorphism

**Don't use virtual functions when:**
- All derived classes have identical behavior
- Performance is critical and alternatives exist
- You only have one implementation (no polymorphism needed)
- You can solve the problem with templates (compile-time polymorphism)