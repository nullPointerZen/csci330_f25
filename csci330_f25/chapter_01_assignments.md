# Chapter 1: Up and Running - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 1 "Up and Running"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## Instructions
- These problems apply concepts from both the textbook and lecture notes
- Each problem builds on previous concepts  
- **Time expectation**: 2.25 hours total for all three problem sets
- Test all programs thoroughly before submission

---

## Problem Set 1: Getting Started (30 minutes)

### Problem 1.1: Your First Program
**Objective**: Practice basic C++ program structure

Write a program that:
1. Prints your name
2. Prints your favorite programming language  
3. Prints one reason you're learning C++

**Template to get you started**:
```cpp
#include <cstdio>

int main() {
    // Your code here
    return 0;
}
```

**Python/Java Note**: Unlike `python script.py` or `java ClassName`, C++ requires explicit compilation first.

### Problem 1.2: Fix the Errors  
**Objective**: Understand common compilation errors

Fix the 3 errors in this program:
```cpp
#include <cstdio>

int main(){
    int age = 25;
    char name[] = "Alex";
    printf("Hello, I am %s and I am %d years old\n", name, age);
    return 0;
}
```

**Hint**: This program is actually correct! Try to compile it. If it works, explain why these concepts might be confusing to Python/Java programmers.

### Problem 1.3: Compilation Practice
**Objective**: Get comfortable with the compile-run cycle

1. Save your Problem 1.1 solution as `hello.cpp`
2. Compile it using your chosen workflow:
   - **Docker/CLI**: `g++ -o hello hello.cpp`
   - **VS Code**: Press Ctrl+Shift+B (Cmd+Shift+B on macOS)
   - **Command line**: `g++ -o hello hello.cpp`
3. Run it:
   - **Linux/macOS**: `./hello`
   - **Windows**: `hello.exe`
4. Document what happens at each step

---

## Problem Set 2: Basic Programming (45 minutes)

### Problem 2.1: Temperature Converter
**Objective**: Work with variables and arithmetic

Create a program that converts 25°C to Fahrenheit using the formula: F = (C × 9/5) + 32

Requirements:
- Use `int` variables for the calculation
- Print both the Celsius and Fahrenheit values
- Use meaningful variable names

**Extension**: Try the same calculation with `double` variables. What's different?

### Problem 2.2: Simple Function
**Objective**: Write and call your first function

Write a function called `square` that takes an integer and returns its square.

**Template**:
```cpp
#include <cstdio>

int square(int x) {
    // Your code here
}

int main() {
    int num = 5;
    int result = square(num);
    printf("%d squared is %d\n", num, result);
    return 0;
}
```

### Problem 2.3: Basic Decisions
**Objective**: Use if-else statements

Write a program that:
1. Declares an integer variable with any value you choose
2. Uses if-else to print whether the number is positive, negative, or zero

**Test cases**: Try with values like 10, -5, and 0.

---

## Problem Set 3: Mini Calculator Project (60 minutes)

### Problem 3.1: Calculator Functions
**Objective**: Combine everything you've learned

Build a simple calculator with these functions:
- `int add(int a, int b)`
- `int subtract(int a, int b)`  
- `int multiply(int a, int b)`

**Starter template**:
```cpp
#include <cstdio>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    // Your code here
}

int multiply(int a, int b) {
    // Your code here
}

int main() {
    int x = 10;
    int y = 3;
    
    printf("%d + %d = %d\n", x, y, add(x, y));
    printf("%d - %d = %d\n", x, y, subtract(x, y));
    printf("%d * %d = %d\n", x, y, multiply(x, y));
    
    return 0;
}
```

### Problem 3.2: Add Error Checking
**Objective**: Handle edge cases

Add a division function with a twist:
```cpp
void divide(int a, int b) {
    if (b == 0) {
        printf("Error: Cannot divide by zero!\n");
    } else {
        printf("%d / %d = %d\n", a, b, a / b);
    }
}
```

Add this to your calculator and test it with both normal values and zero.

### Problem 3.3: Test Your Calculator
**Objective**: Verify your work

Test your calculator with these inputs:
- 15 + 7
- 20 - 8  
- 6 * 4
- 12 / 3
- 10 / 0 (should show error message)

Make sure all outputs are correct!

---

## Submission Guidelines

**For each problem set**:
1. Include source code with basic comments
2. Show compilation method used:
   - **Docker/CLI**: Include the `g++` command
   - **VS Code**: Mention "Built with VS Code (Ctrl+Shift+B)"
   - **CMake**: Include `cmake` and `make` commands
3. Provide sample output
4. Note any challenges you faced
5. Include workflow used (Docker, VS Code + Docker, or Local)

**File organization**:
```
chapter01_solutions/
├── problem_set_1/
│   ├── problem_1_1.cpp
│   ├── problem_1_2.cpp
│   └── problem_1_3.cpp
├── problem_set_2/
│   ├── problem_2_1.cpp
│   ├── problem_2_2.cpp
│   └── problem_2_3.cpp
├── problem_set_3/
│   ├── problem_3_1.cpp
│   ├── problem_3_2.cpp
│   └── problem_3_3.cpp
└── README.md (with compilation notes)
```

**Expected time commitment**: 2.25 hours total for all problem sets. If you're taking longer, ask for help!