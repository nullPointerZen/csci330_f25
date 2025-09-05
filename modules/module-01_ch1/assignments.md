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
- **Time expectation**: 1.5 hours total for both problem sets
- Test all programs thoroughly before submission

---

## Problem Set 1: Fundamentals and Basic Programming (45 minutes)

### Problem 1.1: Your First Program (10 minutes)
**Objective**: Practice basic C++ program structure and compilation

Write a program that prints your name, favorite programming language, and one reason you're learning C++.

**Complete Template**:
```cpp
#include <cstdio>

int main() {
    // Print your information here
    printf("Name: [Your Name]\n");
    printf("Favorite Language: [Your Language]\n");
    printf("Learning C++ because: [Your Reason]\n");
    return 0;
}
```

**Compilation Practice**:
1. Save as `hello.cpp`
2. Compile: `g++ -o hello hello.cpp`
3. Run: `./hello` (Linux/macOS) or `hello.exe` (Windows)
4. Document the compile-run cycle in comments

### Problem 1.2: Temperature Converter with Functions (20 minutes)
**Objective**: Work with variables, arithmetic, and functions

Create a program with a function that converts Celsius to Fahrenheit using: F = (C × 9/5) + 32

**Template**:
```cpp
#include <cstdio>

// Function to convert Celsius to Fahrenheit
int celsius_to_fahrenheit(int celsius) {
    // Your conversion code here
}

int main() {
    int temp_celsius = 25;
    int temp_fahrenheit = celsius_to_fahrenheit(temp_celsius);
    
    printf("%d°C = %d°F\n", temp_celsius, temp_fahrenheit);
    
    // Test with multiple values
    printf("%d°C = %d°F\n", 0, celsius_to_fahrenheit(0));
    printf("%d°C = %d°F\n", 100, celsius_to_fahrenheit(100));
    
    return 0;
}
```

**Extension**: Create a second function using `double` variables. Compare the results and explain the difference in comments.

### Problem 1.3: Number Analysis with Decisions (15 minutes)
**Objective**: Use if-else statements and understand program flow

Write a program that analyzes multiple numbers and categorizes them.

**Template**:
```cpp
#include <cstdio>

void analyze_number(int num) {
    printf("Analyzing %d: ", num);
    
    // Your if-else logic here
    // Determine if positive, negative, or zero
    // Also determine if even or odd (for non-zero numbers)
}

int main() {
    // Test with various numbers
    analyze_number(10);
    analyze_number(-5);
    analyze_number(0);
    analyze_number(7);
    
    return 0;
}
```

---

## Problem Set 2: Integrated Calculator Project (45 minutes)

### Problem 2.1: Calculator Functions with Error Handling (30 minutes)
**Objective**: Combine everything you've learned into a complete calculator

Build a calculator with basic operations and error checking:

**Complete Template**:
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

void divide(int a, int b) {
    if (b == 0) {
        printf("Error: Cannot divide by zero!\n");
    } else {
        printf("%d / %d = %d\n", a, b, a / b);
    }
}

int main() {
    // Test all operations
    int x = 15, y = 3;
    
    printf("Calculator Testing:\n");
    printf("%d + %d = %d\n", x, y, add(x, y));
    printf("%d - %d = %d\n", x, y, subtract(x, y));
    printf("%d * %d = %d\n", x, y, multiply(x, y));
    divide(x, y);
    
    // Test edge cases
    printf("\nEdge Case Testing:\n");
    divide(10, 0);  // Should show error
    printf("%d + %d = %d\n", -5, 8, add(-5, 8));
    
    return 0;
}
```

### Problem 2.2: Interactive Calculator Enhancement (15 minutes)
**Objective**: Add user interaction and validation

Extend your calculator to read two numbers and perform all operations:

**Template**:
```cpp
#include <cstdio>

// Use your functions from Problem 2.1 here
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { /* your code */ }
int multiply(int a, int b) { /* your code */ }
void divide(int a, int b) { /* your code with error checking */ }

int main() {
    int num1, num2;
    
    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);
    
    printf("\nCalculator Results for %d and %d:\n", num1, num2);
    
    // Perform all operations
    printf("Addition: %d + %d = %d\n", num1, num2, add(num1, num2));
    printf("Subtraction: %d - %d = %d\n", num1, num2, subtract(num1, num2));
    printf("Multiplication: %d * %d = %d\n", num1, num2, multiply(num1, num2));
    printf("Division: ");
    divide(num1, num2);
    
    return 0;
}
```

**Test Cases**: Try with inputs like (15, 3), (10, 0), and (-5, 2)

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
**Total: 1.5 hours** for both problem sets. If taking significantly longer, ask for help during office hours!

### Need Help?
- 📋 **Assignment template**: `modules/module-01_ch1/assignment-template/`
- 🔄 **Workflow guide**: `/ASSIGNMENT_WORKFLOW.md`
- 🆘 **Git help**: `/reference/git-commands.md`