# Chapter 12: Utilities - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 12 "Utilities" (2-3 hours)
2. **🔍 SECOND**: Work through these lecture notes for hands-on practice (3-4 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 12 "Utilities" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Master** move semantics and std::move for performance optimization
2. **Implement** std::optional for type-safe nullable values
3. **Apply** std::variant for type-safe discriminated unions
4. **Use** std::any for type-erased value storage
5. **Design** perfect forwarding with std::forward
6. **Optimize** code using modern C++ utility classes

**⏱️ Time Budget:**
- **📚 Textbook Reading: 2-3 hours** (Chapter 12: "Utilities" - REQUIRED FIRST)
- **💻 Hands-on Work: 4-5 hours** (course materials + assignments + debugging)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**

## 🧠 Key Concepts Summary

### **1. Move Semantics**
- **Performance optimization**: Avoid expensive copies
- **std::move**: Explicitly request move operation
- **Move constructors/assignment**: Transfer resources efficiently
- **Perfect forwarding**: Preserve value categories in templates

### **2. std::optional<T>**
- **Nullable types**: Type-safe alternative to pointers for optional values
- **Explicit presence/absence**: has_value() and value() methods
- **Default values**: value_or() for safe defaults
- **Monadic operations**: transform() and and_then() for chaining

### **3. std::variant<T1, T2, ...>**
- **Type-safe unions**: Store one of several types safely
- **Visitor pattern**: std::visit for type-safe access
- **Index tracking**: Knows which type is currently stored
- **Exception safety**: Strong exception safety guarantees

### **4. std::any**
- **Type erasure**: Store any copyable type
- **Runtime type checking**: any_cast for safe retrieval
- **Type information**: type() method for runtime queries
- **Performance cost**: Dynamic allocation and type overhead

### **5. Utility Functions**
- **std::exchange**: Atomically replace and return old value
- **std::swap**: Efficient value swapping
- **std::tuple**: Multiple value containers
- **std::pair**: Two-value containers

## 💻 Practical Applications

### **Performance Optimization**
```cpp
// Move semantics for efficiency
std::vector<std::string> create_strings() {
    std::vector<std::string> result;
    // ... populate result
    return result;  // Automatic move optimization
}

// Optional for nullable returns
std::optional<User> find_user(int id) {
    if (user_exists(id)) {
        return User{id};
    }
    return std::nullopt;
}
```

### **Type-Safe Programming**
```cpp
// Variant for discriminated unions
using Value = std::variant<int, double, std::string>;
Value parse_input(const std::string& input);

// Pattern matching with visitors
std::visit([](const auto& value) {
    using T = std::decay_t<decltype(value)>;
    if constexpr (std::is_same_v<T, int>) {
        // Handle integer
    } else if constexpr (std::is_same_v<T, std::string>) {
        // Handle string
    }
}, value);
```

## 🔧 Common Patterns and Pitfalls

### **Best Practices**
- Use std::optional instead of pointers for optional values
- Prefer std::variant over void* or unsafe unions
- Use move semantics for expensive-to-copy objects
- Apply perfect forwarding in template functions

### **Common Mistakes**
- Calling std::move unnecessarily
- Not handling all variant alternatives
- Using std::any when compile-time types are known
- Forgetting to check optional.has_value()

### **Performance Considerations**
- Move operations should be noexcept when possible
- std::optional has minimal overhead
- std::variant has small overhead for type index
- std::any has significant overhead for type erasure

## 📝 Before Next Chapter

Ensure you understand:
- When move semantics provide benefits
- How to safely use optional and variant types
- Performance implications of different utility types
- Perfect forwarding in generic code

**Next Chapter Preview**: Chapter 13 covers STL containers, applying these utility concepts to data structures.