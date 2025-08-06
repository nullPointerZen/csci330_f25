# Chapter 6: Compile-Time Polymorphism - Quick Help Guide

## Top 5 New Template Errors (And How to Fix Them)

### 1. **"Template parameter not declared"**
```
Error: 'T' was not declared in this scope
```
**What it means:** You forgot the `template<typename T>` declaration before your function/class.

**Fix:**
```cpp
// Wrong:
T maximum(T a, T b) { return (a > b) ? a : b; }

// Right:
template<typename T>
T maximum(T a, T b) { return (a > b) ? a : b; }
```

### 2. **"No matching function for template argument deduction"**
```
Error: no matching function for call to 'func()'
```
**What it means:** The compiler can't figure out what type T should be.

**Fix:**
```cpp
// If this fails:
maximum(5, 3.14);  // int vs double - ambiguous

// Try this:
maximum<double>(5, 3.14);  // Explicitly specify type
// Or this:
maximum(5.0, 3.14);  // Make both the same type
```

### 3. **"Template specialization after instantiation"**
```
Error: explicit specialization of 'class Template' after instantiation
```
**What it means:** You're trying to specialize a template after it's already been used.

**Fix:** Put all template specializations before any code that uses the template.

### 4. **"Invalid use of template"**
```
Error: invalid use of template-name 'MyClass' without an argument list
```
**What it means:** You're using a template class without specifying the type.

**Fix:**
```cpp
// Wrong:
MyClass obj;

// Right:
MyClass<int> obj;
```

### 5. **"No type named 'something' in template parameter"**
```
Error: 'T' has no member named 'method'
```
**What it means:** Your template assumes T has certain methods/operators, but the type you're using doesn't.

**Fix:** Only use operations that work for all types you plan to use, or document requirements clearly.

---

## Quick Reference: New Syntax

### Function Templates
```cpp
// Basic function template
template<typename T>
T function_name(T parameter) {
    // implementation
}

// Multiple template parameters
template<typename T1, typename T2>
auto function_name(T1 a, T2 b) -> decltype(a + b) {
    return a + b;
}

// Using the template
int result = function_name(5, 10);        // T deduced as int
int result = function_name<int>(5, 10);   // T explicitly specified
```

### Template Classes
```cpp
// Class template declaration
template<typename T>
class ClassName {
private:
    T member_variable;
public:
    ClassName(T initial_value);
    T get_value() const;
    void set_value(const T& new_value);
};

// Constructor definition (outside class)
template<typename T>
ClassName<T>::ClassName(T initial_value) : member_variable(initial_value) {}

// Method definition (outside class)
template<typename T>
T ClassName<T>::get_value() const {
    return member_variable;
}

// Using the template class
ClassName<int> obj(42);
ClassName<string> text_obj("hello");
```

### Template Specialization (Advanced)
```cpp
// General template
template<typename T>
class Printer {
public:
    static void print(const T& value) {
        cout << "Value: " << value << endl;
    }
};

// Specialization for bool
template<>
class Printer<bool> {
public:
    static void print(const bool& value) {
        cout << "Boolean: " << (value ? "true" : "false") << endl;
    }
};
```

---

## "Stuck? Try This!" Common Troubleshooting

### When Templates Won't Compile:
1. **Check your template declaration:** Every template function/class needs `template<typename T>` (or similar) right before it
2. **Look at the error line carefully:** Template errors are verbose but usually point to the exact problem
3. **Try explicit type specification:** If `func(a, b)` fails, try `func<int>(a, b)`
4. **Make sure types match:** Template deduction fails when types are ambiguous

### When Template Classes Act Weird:
1. **Remember the angle brackets:** `MyClass obj;` should be `MyClass<int> obj;`
2. **Check your constructor:** Template class constructors need the same template syntax
3. **Method definitions outside class:** Need full `ClassName<T>::method_name` syntax

### When You Get Massive Error Messages:
1. **Read the first few lines:** Template errors cascade, fix the first one
2. **Look for "required from":** Shows you where the problem actually started
3. **Check for typos in template parameter names:** `template<typename T>` but using `U` in the code

### Performance Confusion:
1. **Templates are compile-time:** No runtime overhead like virtual functions
2. **Each type creates a separate copy:** `vector<int>` and `vector<string>` are completely different classes
3. **Code bloat is possible:** Using templates with many types increases executable size

---

## Success Checklist: What You Should Master

### ✅ Basic Template Skills
- [ ] Can write a simple function template that works with multiple types
- [ ] Understand the difference between `template<typename T>` and regular functions
- [ ] Can use both automatic type deduction and explicit type specification
- [ ] Know when to use templates vs function overloading

### ✅ Template Classes
- [ ] Can create a template class with proper constructor syntax
- [ ] Understand how to instantiate template classes: `MyClass<int> obj;`
- [ ] Can define template class methods both inside and outside the class
- [ ] Know how template classes compare to Java generics

### ✅ Debugging and Error Handling
- [ ] Can read and understand common template error messages
- [ ] Know how to fix "template parameter not declared" errors
- [ ] Understand why some operations don't work with all types
- [ ] Can explain when template argument deduction fails

### ✅ Conceptual Understanding
- [ ] Can explain compile-time vs runtime polymorphism
- [ ] Know when to use templates vs inheritance/virtual functions
- [ ] Understand the performance implications of templates
- [ ] Can compare C++ templates to Python duck typing and Java generics

### ✅ Practical Application
- [ ] Can create useful generic classes (containers, utilities)
- [ ] Know basic template best practices (header files, meaningful names)
- [ ] Can write templates that work with both built-in and user-defined types
- [ ] Understand template specialization concepts

---

## Quick Comparison: Templates vs Other Approaches

| Feature | C++ Templates | Java Generics | Python Duck Typing | Virtual Functions |
|---------|---------------|---------------|-------------------|-------------------|
| **When decided** | Compile-time | Compile-time | Runtime | Runtime |
| **Type safety** | Full | Full | Runtime checks | Full |
| **Performance** | No overhead | Type erasure overhead | Dynamic dispatch | Virtual call overhead |
| **Code size** | Can increase | Minimal increase | No increase | Minimal increase |
| **Flexibility** | Very high | High | Very high | Medium |
| **Error messages** | Complex | Clearer | Runtime errors | Clear |

### When to Use Each:
- **Templates:** Need compile-time decisions, maximum performance, type safety
- **Virtual functions:** Need runtime polymorphism, object hierarchies
- **Mix both:** Different problems need different solutions!

---

## Remember: Templates are Your Friend!
- Start simple: basic function templates first
- Practice with built-in types (int, double, string) before custom classes  
- Read error messages carefully - they're more helpful than they look
- Think "compile-time" - templates create code at compile time, not runtime