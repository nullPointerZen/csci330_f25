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

## 📝 Assignment Submission

### Quick Start
1. **Get the template**: Copy from `modules/module-01_ch1/assignment-template/`
2. **Complete the problems**: Follow the detailed structure above
3. **Submit via Git**: Create Pull Request with your solutions

### Detailed Workflow

#### Step 1: Set Up Your Assignment Directory
```bash
# Copy template to your personal directory
mkdir -p assignments/CSCI330_FirstName_LastName/week01
cp -r modules/module-01_ch1/assignment-template/* assignments/CSCI330_FirstName_LastName/week01/

# Navigate to your assignment directory
cd assignments/CSCI330_FirstName_LastName/week01
```

#### Step 2: Complete All Problem Sets
Organize your solutions following this structure:
```
assignments/CSCI330_FirstName_LastName/week01/
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
└── README.md (with compilation notes and outputs)
```

**For each solution include**:
- Source code with basic comments
- Compilation method used (g++, VS Code, CMake)
- Sample output showing the program works
- Any challenges you faced

#### Step 3: Submit via Pull Request
```bash
# Create and switch to feature branch
git checkout -b week01-submission

# Add your completed work
git add assignments/CSCI330_FirstName_LastName/week01/
git commit -m "Complete HW_01: Chapter 1 Problem Sets

- Implemented all problem sets (1.1-3.3)
- Added comprehensive README with compilation notes
- Tested all solutions with sample outputs"

# Push branch and create PR
git push -u origin week01-submission
```

#### Step 4: Canvas Submission
**🎯 REQUIRED**: Submit the link to your completed assignment directory on Canvas:
```
https://github.com/YourUsername/csci330_f25/tree/main/assignments/CSCI330_FirstName_LastName/week01
```

**Example**: `https://github.com/jsmith/csci330_f25/tree/main/assignments/CSCI330_John_Smith/week01`

### Assessment Criteria
- [ ] All 9 problems completed with working solutions
- [ ] Proper file organization following naming convention
- [ ] Clear README with compilation notes and sample outputs  
- [ ] Code compiles without errors and warnings
- [ ] Professional Git workflow (meaningful commits, clean PR)
- [ ] Canvas submission includes correct GitHub directory link

### Time Expectation
**Total: 2.25 hours** for all problem sets. If taking significantly longer, ask for help during office hours!

### Need Help?
- 📋 **Assignment template**: `modules/module-01_ch1/assignment-template/`
- 🔄 **Workflow guide**: `/ASSIGNMENT_WORKFLOW.md`
- 🆘 **Git help**: `/reference/git-commands.md`