# Chapter 5: Runtime Polymorphism - Lesson Plan

## Course: C++ for Python/Java Programmers
## Delivery Mode: Self-Paced, Asynchronous
## Total Learning Time: 7.75-8.75 hours across 3 components

---

## 📖 Three-Component Learning Sequence

This chapter follows a structured, self-paced approach where each component builds on the previous:

### Component 1: Textbook Foundation (1-2 hours)
**Student Activity**: Read Chapter 5 "Runtime Polymorphism" from C++ Crash Course
- **Purpose**: Establish core theoretical foundation for virtual functions and polymorphic design
- **Instructor Role**: None (self-paced reading)
- **Assessment**: Comprehension verified through subsequent components

### Component 2: Contextualized Tutorial (4.5 hours) 
**Student Activity**: Work through `chapter_05_lecture_notes.md`
- **Purpose**: Bridge textbook concepts to Python/Java knowledge with hands-on practice
- **Instructor Role**: Available for office hours support
- **Content**: Comparative explanations + guided practice problems

### Component 3: Applied Assessment (2.25 hours)
**Student Activity**: Complete `chapter_05_assignments.md` 
- **Purpose**: Demonstrate mastery through independent problem-solving
- **Instructor Role**: Grade final submissions
- **Assessment**: Polymorphic class hierarchies and virtual function usage

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
- **Option B**: VS Code + Docker (excellent for polymorphism visualization)
- **Option C**: VS Code + Local Compiler

**For Chapter 5's polymorphism concepts, step-through debugging shows virtual function dispatch!**

---

## Learning Objectives

By the end of this lesson, students will be able to:

1. **Explain** runtime polymorphism and how it relates to inheritance concepts from Python/Java
2. **Create** base classes with virtual functions for polymorphic behavior
3. **Implement** derived classes that override virtual functions appropriately
4. **Use** polymorphic objects through base class pointers/references
5. **Apply** the override keyword for safe function overriding
6. **Design** simple class hierarchies using inheritance and virtual functions

---

## Key Concepts with Python/Java Equivalencies

### 1. Inheritance and Virtual Functions

| Language | Base Class | Derived Class | Virtual Method |
|----------|------------|---------------|----------------|
| **C++** | `struct Base { virtual void func() = 0; };` | `struct Derived : Base { void func() override; };` | Explicitly `virtual` |
| **Python** | `class Base: def func(self): raise NotImplementedError` | `class Derived(Base): def func(self): ...` | All methods virtual by default |
| **Java** | `abstract class Base { abstract void func(); }` | `class Derived extends Base { void func() {...} }` | All methods virtual by default |

### 2. Polymorphic Behavior

| Concept | C++ | Python | Java |
|---------|-----|--------|------|
| **Interface** | Pure virtual functions | Abstract methods | Abstract methods |
| **Implementation** | Override with `override` keyword | Just redefine method | `@Override` annotation |
| **Usage** | Base class pointer/reference | Duck typing | Base class reference |

### 3. Memory Management

| Aspect | C++ | Python | Java |
|--------|-----|--------|------|
| **Destruction** | Virtual destructor needed | Automatic cleanup | Garbage collected |
| **Object Creation** | Manual or automatic | Automatic | `new` operator |
| **Polymorphic Deletion** | `virtual ~Base() = default;` | Handled automatically | Handled by GC |

---

## Lesson Structure

### Module 1: Introduction to Inheritance (35 minutes)

#### Content Delivery
- **Review**: OOP concepts from Python/Java
- **C++ Inheritance Syntax**: Basic class derivation
- **Virtual Functions**: Why they're needed in C++

#### Activities
1. Create a simple base class with a virtual function
2. Derive a class and override the function
3. Compare with Python/Java inheritance

#### Key Points
- C++ requires explicit `virtual` keyword (unlike Python/Java)
- Inheritance syntax: `class Derived : public Base`
- Virtual functions enable runtime polymorphism

### Module 2: Pure Virtual Functions and Abstract Classes (40 minutes)

#### Content Delivery
- **Abstract Base Classes**: Pure virtual functions (`= 0`)
- **Interface Design**: Creating contracts for derived classes
- **Virtual Destructors**: Why they're essential

#### Activities
1. Create an abstract logger interface
2. Implement multiple concrete loggers
3. Test polymorphic behavior

#### Practical Focus
- Design patterns similar to Java interfaces
- Memory safety with virtual destructors
- Clear separation of interface and implementation

### Module 3: Polymorphic Usage Patterns (50 minutes)

#### Content Delivery
- **Runtime Dispatch**: How virtual function calls work
- **Base Class Pointers**: Working with polymorphic objects
- **Override Keyword**: Modern C++ safety features

#### Activities
1. Use base class pointers to call derived functions
2. Create collections of polymorphic objects
3. Practice the `override` keyword

#### Key Concepts
- Runtime vs compile-time polymorphism
- Pointer/reference semantics for polymorphism
- Type safety with `override`

### Module 4: Practical Application Project (35 minutes)

#### Content Delivery
- **Real-world Example**: Building a logging system
- **Design Principles**: When to use virtual functions
- **Best Practices**: Modern C++ polymorphism

#### Activities
1. Build a complete logging system with multiple outputs
2. Test the system with different logger types
3. Extend the system with new logger types

#### Integration Focus
- Combine all concepts learned
- Practice good object-oriented design
- Prepare for more advanced polymorphism topics

---

## Assessment Strategy

### Formative Assessment (Throughout)
- **Code Reading**: Identify virtual vs non-virtual functions
- **Quick Fixes**: Debug common inheritance errors
- **Concept Checks**: Compare C++ patterns to Python/Java

### Summative Assessment  
- **Polymorphic Shape System** (45 minutes):
  - Create abstract `Shape` base class with virtual area/perimeter functions
  - Implement `Rectangle` and `Circle` derived classes
  - Use base class pointers to work with different shapes
  - Template provided with base structure

### Rubric (Pass/Fail)
| Criteria | Pass Requirement |
|----------|------------------|
| **Virtual Functions** | Base class has proper virtual functions declared |
| **Inheritance** | Derived classes inherit correctly and override functions |
| **Polymorphism** | Can use base class pointers to call derived methods |
| **Override Safety** | Uses `override` keyword appropriately |
| **Memory Safety** | Includes virtual destructor in base class |

---

## Additional Resources

### Required Reading
- Chapter 5: "Runtime Polymorphism" from C++ Crash Course

### Supplementary Materials
- [Polymorphism in C++](https://isocpp.org/wiki/faq/virtual-functions) - C++ FAQ
- [Virtual Functions Explained](https://cppreference.com/w/cpp/language/virtual) - Reference
- [Inheritance Best Practices](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#c-classes-and-class-hierarchies) - Core Guidelines

### Office Hours Topics
- Understanding virtual function tables (vtables)
- When to use inheritance vs composition
- Common polymorphism pitfalls and solutions

---

## Teaching Notes

### Common Challenges
1. **Forgetting Virtual**: Students often forget virtual keyword coming from Python/Java
2. **Memory Management**: Virtual destructor confusion
3. **Override Safety**: Understanding why `override` helps catch errors

### Differentiation
- **For Advanced Students**: Explore virtual function implementation details, multiple inheritance
- **For Struggling Students**: Focus on the logging example, provide more step-by-step guidance

### Time Management
- Emphasize hands-on coding over theory
- Use familiar examples (shapes, animals, vehicles) that relate to Python/Java experience
- Keep virtual function table discussion brief and practical

### Connection to Previous Chapters
- **Chapter 4**: Object lifecycle now includes virtual destructors
- **Future Preparation**: Sets foundation for Chapter 6's templates and compile-time polymorphism