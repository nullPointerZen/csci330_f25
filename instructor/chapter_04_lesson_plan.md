# Chapter 4: Object Lifecycle - Lesson Plan

## Course: C++ for Python/Java Programmers
## Delivery Mode: Self-Paced, Asynchronous
## Total Learning Time: 11.5-13.5 hours across 3 components

---

## 📖 Three-Component Learning Sequence

This chapter follows a structured, self-paced approach where each component builds on the previous:

### Component 1: Textbook Foundation (2-3 hours)
**Student Activity**: Read Chapter 4 "Object Lifecycle" from C++ Crash Course
- **Purpose**: Establish core theoretical foundation for constructors, destructors, and RAII
- **Instructor Role**: None (self-paced reading)
- **Assessment**: Comprehension verified through subsequent components

### Component 2: Contextualized Tutorial (7-8 hours) 
**Student Activity**: Work through `chapter_04_lecture_notes.md`
- **Purpose**: Bridge textbook concepts to Python/Java knowledge with hands-on practice
- **Instructor Role**: Available for office hours support
- **Content**: Comparative explanations + guided practice problems

### Component 3: Applied Assessment (2.5 hours)
**Student Activity**: Complete `chapter_04_assignments.md` 
- **Purpose**: Demonstrate mastery through independent problem-solving
- **Instructor Role**: Grade final submissions
- **Assessment**: Banking system + resource management projects

---

## 🎯 Instructor Focus Areas

### Key Teaching Points
**Emphasize the Learning Sequence**:
- Students MUST complete textbook reading before lecture notes
- Lecture notes contextualize and reinforce textbook concepts
- Assignments test combined knowledge from both sources
- **Critical**: Don't let students skip ahead or work out of sequence

### Development Environment Setup
**Continue using your chosen workflow from previous chapters:**
- **Option A**: Docker + Command Line
- **Option B**: VS Code + Docker (highly recommended for object lifecycle debugging)
- **Option C**: VS Code + Local Compiler

**For Chapter 4's constructor/destructor concepts, debugger step-through is essential!**

---

## Learning Objectives

By the end of this lesson, students will be able to:

1. **Explain** the C++ object lifecycle (construction, use, destruction)
2. **Write** constructors to initialize objects with default and custom values
3. **Implement** destructors to clean up object resources
4. **Apply** basic RAII principles for automatic resource management
5. **Use** dynamic memory allocation with new/delete safely
6. **Compare** C++ object lifecycle with Python/Java equivalents

---

## Key Concepts with Python/Java Equivalencies

### 1. Object Construction/Initialization

| Language | Constructor Syntax | When Called | Example |
|----------|-------------------|-------------|---------|
| **C++** | `ClassName(params) { }` | Object creation | `ClockOfTheLongNow clock{2020};` |
| **Python** | `def __init__(self, params):` | Object creation | `clock = Clock(2020)` |
| **Java** | `public ClassName(params) { }` | Object creation | `Clock clock = new Clock(2020);` |

### 2. Object Destruction/Cleanup

| Language | Destructor/Cleanup | When Called | Automatic? |
|----------|-------------------|-------------|-----------|
| **C++** | `~ClassName() { }` | Scope exit/delete | Yes (deterministic) |
| **Python** | `def __del__(self):` | Garbage collection | No (non-deterministic) |
| **Java** | `finalize()` (deprecated) | Garbage collection | No (non-deterministic) |

### 3. Memory Management

| Aspect | C++ | Python | Java |
|--------|-----|--------|------|
| **Stack Objects** | `ClockOfTheLongNow clock;` | N/A (all heap) | N/A (all heap) |
| **Heap Objects** | `new ClockOfTheLongNow()` | `Clock()` (automatic) | `new Clock()` |
| **Cleanup** | Manual (`delete`) or automatic (destructors) | Automatic (GC) | Automatic (GC) |
| **RAII** | Yes (automatic cleanup) | No (with statement for files) | Try-with-resources |

### 4. Constructor Types

| Type | C++ | Python | Java |
|------|-----|--------|------|
| **Default** | `Clock() { }` | `def __init__(self):` | `public Clock() { }` |
| **Parameterized** | `Clock(int year) { }` | `def __init__(self, year):` | `public Clock(int year) { }` |
| **Copy** | `Clock(const Clock& other)` | Manual implementation | Manual implementation |

---

## Lesson Structure

### Module 1: Object Lifecycle Basics (40 minutes)

#### Content Delivery
- **Object Lifecycle Overview**: Construction → Use → Destruction
- **Stack vs Heap Objects**: Automatic vs manual management
- **Comparison**: How Python and Java hide this complexity

**VS Code Lifecycle Debugging:**
- **Call Stack**: See constructor and destructor calls in real-time
- **Variables Panel**: Watch objects appear and disappear from scope
- **Breakpoints in Constructors**: Step through object initialization
- **Breakpoints in Destructors**: See when objects are cleaned up

#### Activities
1. Create simple objects and observe their lifecycle
2. Practice with both stack and heap allocation
3. Use debugger to see constructor/destructor calls
4. **Debug Exercise**: Step through object creation and destruction

#### Key Concepts
- Constructors initialize objects
- Destructors clean up objects
- Stack objects are automatic, heap objects need `delete`

### Module 2: Constructors and Initialization (45 minutes)

#### Content Delivery
- **Default Constructors**: No-parameter initialization
- **Parameterized Constructors**: Custom initialization
- **Constructor Overloading**: Multiple initialization options
- **Member Initialization**: Setting initial values

**Constructor Debugging Tips:**
- **Step Into (F11)**: Step into constructor calls to see initialization
- **Watch Member Variables**: See how constructor parameters become members
- **Multiple Constructors**: Step through different constructor overloads

#### Activities
1. Write constructors for a `BankAccount` class
2. Create objects with different initialization strategies
3. Practice constructor overloading
4. **Debug Activity**: Step through constructor overload resolution

#### Python/Java Connection
- Similar to `__init__` in Python
- Similar to constructors in Java
- All constructors run automatically

### Module 3: Destructors and RAII (45 minutes)

#### Content Delivery
- **Destructor Purpose**: Cleanup resources
- **RAII Principle**: Resource Acquisition Is Initialization
- **Automatic vs Manual**: When destructors are called
- **Common Uses**: File handles, memory, network connections

**RAII Debugging Strategy:**
- **Destructor Breakpoints**: See exactly when cleanup happens
- **Call Stack at Destruction**: Understand destruction order
- **Resource Tracking**: Watch file handles and memory in debugger
- **Scope Visualization**: See when objects go out of scope

#### Activities
1. Write destructors for resource cleanup
2. Practice with file handling using RAII
3. See memory leaks when destructors are missing
4. **Debug RAII**: Step through automatic resource cleanup

#### Key Insight
- C++ destructors are like Python's `with` statement
- Automatic cleanup prevents resource leaks

### Module 4: Dynamic Memory and Best Practices (40 minutes)

#### Content Delivery
- **new and delete**: Manual memory management
- **Memory Leaks**: What happens when you forget `delete`
- **Best Practices**: Prefer stack objects when possible
- **Smart Pointers Preview**: Modern C++ solutions

**Memory Debugging Tools:**
- **Address Sanitizer**: Automatically detect memory leaks
- **Heap Visualization**: See memory allocation in debugger
- **Leak Detection**: Use static analysis tools to find missing deletes
- **Valgrind Integration**: Advanced memory debugging (Linux)

#### Activities
1. Practice with `new` and `delete`
2. Create intentional memory leaks to see the problem
3. Fix memory leaks with proper cleanup
4. **Debug Memory**: Use Address Sanitizer to detect leaks automatically

#### Critical Safety
- Every `new` needs a `delete`
- Prefer stack objects over heap objects
- Use RAII to avoid manual memory management

---

## Assessment Strategy

### Formative Assessment (Throughout)
- **Code Reviews**: Check constructor/destructor pairs
- **Memory Checking**: Use tools to detect leaks
- **Concept Checks**: Quick quizzes on lifecycle stages

### Summative Assessment
- **Resource Manager Project** (45 minutes):
  - Create a `FileLogger` class that opens a file in constructor
  - Write log messages through methods
  - Close file automatically in destructor
  - Test with both stack and heap allocation
  - Handle error cases (file won't open)

### Rubric (Pass/Fail)
| Criteria | Pass Requirement |
|----------|------------------|
| Constructor | Initializes all members properly |
| Destructor | Cleans up resources (closes file) |
| RAII | File opens in constructor, closes in destructor |
| Memory Safety | No memory leaks with heap allocation |
| Error Handling | Handles file open failures gracefully |

---

## Teaching Notes

### Common Challenges
1. **Forgetting delete**: Students from GC languages forget manual cleanup
2. **Constructor syntax**: Different from Python `__init__` syntax
3. **When destructors run**: Non-deterministic in Python/Java vs deterministic in C++

### Differentiation
- **For Advanced Students**: Introduce copy constructors and move semantics
- **For Struggling Students**: Focus on stack objects first, delay heap allocation

### Python/Java Connections
- Emphasize how C++ makes explicit what Python/Java hide
- Compare RAII to Python's `with` statement
- Show Java's try-with-resources as similar concept

### Time Management
- Keep Module 1 conceptual with simple examples
- More hands-on practice in Modules 2-3
- Module 4 is critical for memory safety

---

## Additional Resources

### Required Reading
- Chapter 4: "Object Lifecycle" from C++ Crash Course

### Supplementary Materials
- [RAII Explained](https://en.cppreference.com/w/cpp/language/raii) - RAII concept
- [Valgrind Tutorial](https://valgrind.org/) - Memory leak detection
- Memory management best practices guide

### Office Hours Topics
- Understanding when destructors are called
- Debugging memory leaks
- When to use stack vs heap objects
- Transitioning from garbage collection to manual memory management