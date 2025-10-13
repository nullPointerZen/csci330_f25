# CSCI330 Catch-Up Assignment: Chapters 2-5 Essentials

## 📋 Purpose

This condensed assignment helps students who have fallen behind get back on track. Instead of completing all 100 points of missed work (4 chapters × 25 points each), this assignment covers the **essential concepts** from Chapters 2-5 and is worth **50 points** (50% credit recovery).

---

## 🎯 Assignment Overview

**Worth**: 50 points (recovers 50% of missed assignment points)
**Time Estimate**: 4 hours total (1 hour per chapter)
**Due Date**: October 12, 2025 (two weeks)

**Requirements**: Complete ONE focused program per chapter demonstrating core concepts

---

## ✅ What You Need to Do

### Chapter 2: Types and Memory (12.5 points)
**Program**: `types_essentials.cpp`
**Time**: 60 minutes

Create a program that demonstrates:

1. **Fundamental Types** (4 points)
   - Declare and use int, double, char, bool
   - Use `sizeof()` to show type sizes
   - Display range limits using `<climits>` (INT_MAX, INT_MIN, etc.)

2. **Type Conversions** (4 points)
   - Show implicit conversion (int to double)
   - Demonstrate explicit casting with `static_cast<>`
   - Show information loss in narrowing conversions (double to int)

3. **Arrays and Basic Memory** (4.5 points)
   - Create an array of at least 5 integers
   - Access elements safely with bounds checking
   - Calculate array statistics (sum, average, max)
   - Use pointer arithmetic to iterate through array

**Example Output**:
```
=== Type System Basics ===
int: 4 bytes, range: -2147483648 to 2147483647
double: 8 bytes, value: 3.14159

=== Type Conversions ===
double(3.14159) -> int: 3 (precision lost!)
int(42) -> double: 42.000000

=== Array Operations ===
Array: [85, 92, 78, 88, 95]
Sum: 438, Average: 87.6, Max: 95
```

---

### Chapter 3: References (12.5 points)
**Program**: `references_essentials.cpp`
**Time**: 60 minutes

Create a program that demonstrates:

1. **Basic References** (4 points)
   - Create a variable and a reference to it
   - Show that modifying through reference changes the original
   - Print addresses to prove they're the same

2. **Const References** (4 points)
   - Write a function taking const reference parameter
   - Show you can read but not modify through const reference
   - Demonstrate efficiency for large structs

3. **Reference Parameters** (4.5 points)
   - Create a struct (e.g., `Student` with name, GPA)
   - Write a function that takes non-const reference and modifies it
   - Write a function that takes const reference for read-only access
   - Demonstrate both in main

**Example Output**:
```
=== Basic References ===
Original: 100, Reference: 100
Modified through reference: 200
Addresses match: 0x7fff5fbff8bc == 0x7fff5fbff8bc

=== Student Management ===
Original: Alice, GPA: 3.5
After update: Alice, GPA: 3.8
Is honor student: Yes
```

---

### Chapter 4: Object Lifecycle (12.5 points)
**Program**: `lifecycle_essentials.cpp`
**Time**: 60 minutes

Create a program that demonstrates:

1. **Constructor Basics** (4 points)
   - Create a class with default constructor and parameterized constructor
   - Add a destructor that prints when object is destroyed
   - Demonstrate multiple constructor overloads
   - Show automatic constructor/destructor calls

2. **RAII Pattern** (4 points)
   - Create a class that manages a resource (e.g., file, array, counter)
   - Acquire resource in constructor
   - Release resource in destructor
   - Demonstrate automatic cleanup even with early returns

3. **Copy Constructor** (4.5 points)
   - Implement copy constructor for your class
   - Show deep copy vs shallow copy behavior
   - Demonstrate when copies are made
   - Add logging to track object creation/destruction

**Example Output**:
```
=== Constructor/Destructor Demo ===
[Constructor] Account #1001 created: $1000.00
[Constructor] Account #1002 created: $2500.00
[Copy Constructor] Creating copy of Account #1001
[Destructor] Account #1002 destroyed
[Destructor] Account #1001 (copy) destroyed
[Destructor] Account #1001 destroyed

Summary: 3 objects created, 3 objects destroyed
```

---

### Chapter 5: Runtime Polymorphism (12.5 points)
**Program**: `polymorphism_essentials.cpp`
**Time**: 60 minutes

Create a program that demonstrates:

1. **Basic Inheritance and Virtual Functions** (4 points)
   - Create abstract base class `Shape` with pure virtual functions
   - Implement at least 2 derived classes (e.g., `Circle`, `Rectangle`)
   - Use `virtual` keyword correctly
   - Include virtual destructor

2. **Polymorphic Behavior** (4 points)
   - Create array/vector of base class pointers
   - Store different derived types in the collection
   - Call virtual functions through base pointers
   - Demonstrate polymorphic behavior

3. **Practical Application** (4.5 points)
   - Calculate total area of all shapes
   - Find shape with largest/smallest area
   - Display information for each shape
   - Properly clean up dynamic memory

**Example Output**:
```
=== Shape Collection ===
Rectangle (5.0 x 3.0): Area = 15.00
Circle (radius 2.5): Area = 19.63
Rectangle (4.0 x 4.0): Area = 16.00

=== Statistics ===
Total area: 50.63
Largest shape: Circle (19.63)
Smallest shape: Rectangle (15.00)

[Cleanup] Destroying Rectangle
[Cleanup] Destroying Circle
[Cleanup] Destroying Rectangle
```

---

## 📝 Submission Requirements

### File Structure
Create a folder named `CSCI330_YourName_CatchUp` containing:
```
CSCI330_YourName_CatchUp/
├── types_essentials.cpp
├── references_essentials.cpp
├── lifecycle_essentials.cpp
├── polymorphism_essentials.cpp
└── README.md
```

### README.md Must Include
1. **Your name and student ID**
2. **Compilation commands** for each program
3. **Brief explanation** of what each program demonstrates (2-3 sentences per chapter)
4. **Challenges encountered** and how you solved them
5. **Resources used** (textbook pages, homework hints, etc.)

### Canvas Submission Instructions
1. **Compress your folder** into a zip file: `CSCI330_YourName_CatchUp.zip`
2. **Upload to Canvas** in the "Catch-Up Assignment" submission area
3. **Verify** that all 5 files (4 .cpp files + 1 README.md) are in the zip

**Submission Checklist:**
- [ ] All 4 .cpp programs compile without errors
- [ ] README.md is complete with all required sections
- [ ] Folder is properly named: `CSCI330_YourName_CatchUp`
- [ ] Zip file is properly named: `CSCI330_YourName_CatchUp.zip`
- [ ] Uploaded to Canvas before deadline

### Code Requirements
- All programs must compile without errors
- Use meaningful variable names
- Include comments explaining key concepts
- Follow consistent coding style
- Test with multiple inputs where appropriate

---

## 🆘 Getting Help

### Allowed Resources
- ✅ Textbook chapters 2-5
- ✅ Lecture notes and quick-help guides
- ✅ Homework hints (with proper citation)
- ✅ Office hours and instructor help
- ✅ Official C++ documentation

### Required Citation Format
If you reference homework hints, add comments:
```cpp
// Reference: homework-hints/chapter-04/banking_system.cpp
// Used RAII pattern for automatic resource cleanup
// Adapted to work with simplified account structure
```

### 2-Hour Rule
If stuck on the same problem for 2+ hours:
1. Review relevant textbook section
2. Check homework hints for that chapter
3. Ask for help in office hours
4. Don't struggle alone!

---

## 📊 Grading Rubric

### Chapter 2: Types (12.5 points)
- **4 pts**: Fundamental types and type system
- **4 pts**: Type conversions (implicit/explicit)
- **4.5 pts**: Arrays and pointer arithmetic

### Chapter 3: References (12.5 points)
- **4 pts**: Basic reference usage
- **4 pts**: Const correctness
- **4.5 pts**: Reference parameters in functions

### Chapter 4: Lifecycle (12.5 points)
- **4 pts**: Constructors and destructors
- **4 pts**: RAII pattern implementation
- **4.5 pts**: Copy constructor and deep copy

### Chapter 5: Polymorphism (12.5 points)
- **4 pts**: Inheritance and virtual functions
- **4 pts**: Polymorphic behavior through base pointers
- **4.5 pts**: Practical application with memory management

**Total: 50 points**

---

## ⏰ Time Management Strategy

### Week 1 (First Week After Assignment)
- **Day 1-2**: Chapter 2 (Types) - 1 hour
- **Day 3-4**: Chapter 3 (References) - 1 hour
- **Day 5-6**: Chapter 4 (Lifecycle) - 1 hour

### Week 2 (Second Week)
- **Day 1-2**: Chapter 5 (Polymorphism) - 1 hour
- **Day 3-5**: Testing, documentation, cleanup
- **Day 6**: Final review and submission

**Pro Tip**: Work in focused 60-minute blocks with breaks. Each chapter is designed to take approximately 1 hour.

---

## 🎯 Success Criteria

After completing this assignment, you should be able to:

- [ ] Use fundamental C++ types appropriately
- [ ] Apply type conversions safely
- [ ] Work with references for efficient parameter passing
- [ ] Implement classes with proper constructors/destructors
- [ ] Apply RAII pattern for resource management
- [ ] Use inheritance and virtual functions correctly
- [ ] Work with polymorphic objects through base pointers

**Most importantly**: You'll be ready to continue with current coursework!

---

## ⚠️ Important Notes

### Point Recovery
- This assignment recovers **50 points** out of 100 points missed
- Maximum grade for missed chapters: 50% each
- You cannot earn full points for skipped chapters
- **Focus on learning, not just points**

### Moving Forward
- Complete this assignment ASAP
- Stay current with new assignments
- Don't fall behind again
- Use this as a foundation to catch up on concepts

### Academic Integrity
- Work must be your own
- Citing homework hints is required
- No sharing solutions with other students
- Ask instructor if unclear about what's allowed

---

## 💪 Motivation

**You can do this!** This assignment is challenging but achievable:

- 4 hours of focused work (1 hour per chapter)
- Clear requirements and examples
- Homework hints available for reference
- Instructor support during office hours

**The goal**: Get you back on track so you can succeed in this course. The concepts in Chapters 2-5 are foundational - understanding them will make everything else easier.

**Remember**: 50% recovery is better than 0%, and you'll learn essential C++ concepts that you need for the rest of the course.

---

**Questions?** Contact instructor during office hours or via email.

**Due Date**: October 12, 2025 at 11:59 PM
