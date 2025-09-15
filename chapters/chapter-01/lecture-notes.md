# Chapter 1: Up and Running - Complete Guide

## 📖 Learning Sequence (IMPORTANT!)

**🔄 How This Chapter Works:**
1. **📚 FIRST**: Read Textbook Chapter 1 "Up and Running" (1-2 hours)
2. **🔍 SECOND**: Work through these lecture notes for Python/Java context and hands-on practice (4-5 hours)
3. **✅ THIRD**: Complete the chapter assignments to demonstrate mastery (2.25 hours)

**⚠️ Critical**: Each step builds on the previous one. Don't skip ahead!

## 🎯 Learning Objectives

**📚 PREREQUISITE: Read Textbook Chapter 1 "Up and Running" FIRST**

After completing the textbook reading and this chapter's materials, you will:
1. **Set up** VS Code + Docker development environment
2. **Write, compile, and run** your first C++ programs
3. **Debug** common compilation errors
4. **Compare** C++ with Python/Java concepts you already know
5. **Complete** hands-on programming exercises
6. **Understand** how C++ compilation differs from Python/Java (from textbook)

**⏱️ Time Budget:**
- **📚 Textbook Reading: 1-2 hours** (Chapter 1: "Up and Running" - REQUIRED FIRST)
- **🛠️ Setup: 30-60 minutes** (one-time, including troubleshooting)
- **💻 Hands-on Work: 4-5 hours** (course materials + assignments + debugging)
- **📖 Note: Reading time is separate and must be completed BEFORE hands-on work**

---

## 🛠️ Development Environment Setup

**⚠️ Important**: Before starting this chapter, complete the one-time development environment setup.

**📋 Setup Guide**: Follow the comprehensive setup instructions in [DEVELOPMENT_SETUP.md](./DEVELOPMENT_SETUP.md)

This setup guide provides:
- VS Code installation and configuration
- Docker Desktop setup (optional)
- Essential C++ extensions
- Quick verification test
- Troubleshooting for common issues

**✅ Setup Complete?** Once you've followed the setup guide and verified your environment works, continue with the chapter content below.

**⏱️ Setup Time**: ~15-20 minutes (one-time only)

---

## 📚 Core Concepts: C++ vs Python/Java (2.5 hours)

**📖 Bridge to Textbook**: Now that you've read about C++ program structure in Chapter 1, let's connect those concepts to the Python/Java knowledge you already have.

### 1. Program Structure & Entry Point

The textbook explained that every C++ program needs a `main()` function. Here's how this compares to languages you know:

| Language | Entry Point | Notes |
|----------|-------------|-------|
| **C++** | `int main() { return 0; }` | Required; returns exit code to OS |
| **Python** | No explicit main | Convention: `if __name__ == "__main__":` |
| **Java** | `public static void main(String[] args) {}` | Must be inside a class |

**Key Insight**: C++ `main()` is like Python's `if __name__ == "__main__"` block - it's where your program starts.

### 2. The Compilation Process

**From Textbook to Context**: The textbook covered C++ compilation. Here's how it compares to the interpreted languages you know:

| Language | Process | When Errors Found |
|----------|---------|------------------|
| **C++** | Source → Machine Code → Run | Compile time |
| **Python** | Source → Run (interpreted) | Runtime |
| **Java** | Source → Bytecode → Run on JVM | Compile time |

**What this means**: C++ catches many errors before your program runs, making it faster but requiring an extra step.

### 3. Including External Code

```cpp
#include <cstdio>  // Like Python's import, but happens at compile time
```

| Language | How to Import | When Processed |
|----------|---------------|----------------|
| **C++** | `#include <header>` | Before compilation |
| **Python** | `import module` | At runtime |
| **Java** | `import package.Class;` | At compile time |

### 4. Variables and Types

**C++ requires explicit types** (like Java, unlike Python):

```cpp
int age = 25;        // Must specify 'int'
double price = 9.99; // Must specify 'double'  
char grade = 'A';    // Single character
```

| Aspect | C++ | Python | Java |
|--------|-----|--------|------|
| **Type Required** | Yes | No | Yes |
| **Type Changes** | No | Yes | No |
| **Declaration** | `int x = 5;` | `x = 5` | `int x = 5;` |

### 5. Output to Console

```cpp
printf("Hello, World!\n");           // Basic output
printf("I am %d years old\n", age);  // With variables
```

| Language | Basic | With Variables |
|----------|-------|----------------|
| **C++** | `printf("Hi\n");` | `printf("Age: %d\n", age);` |
| **Python** | `print("Hi")` | `print(f"Age: {age}")` |
| **Java** | `System.out.println("Hi");` | `System.out.printf("Age: %d\n", age);` |

### 6. Functions

```cpp
int add(int a, int b) {    // Return type required
    return a + b;
}
```

| Language | Function Definition |
|----------|-------------------|
| **C++** | `int add(int a, int b) { return a + b; }` |
| **Python** | `def add(a, b): return a + b` |
| **Java** | `public static int add(int a, int b) { return a + b; }` |

**Key Point**: C++ functions must specify return type and parameter types.

---

## 🧩 Hands-On Problems (2.25 hours)

**📖 Ready to Apply**: You've read the textbook and reviewed the Python/Java connections above. Now let's put that knowledge to work with hands-on practice that prepares you for the assignments.

### Problem Set 1: First Steps (45 minutes)

#### Problem 1.1: Your Personal Introduction
Write a program that prints:
- Your name
- Your favorite programming language (Python or Java)
- One reason you're excited to learn C++

```cpp
#include <cstdio>

int main() {
    // TODO: Add your printf statements here
    return 0;
}
```

**Expected output example**:
```
My name is Alex
My favorite language is Python
I'm learning C++ to build faster programs
```

#### Problem 1.2: Understanding Compilation
Create this program and deliberately make these mistakes to see the error messages:

```cpp
#include <cstdio>

int main() {
    printf("Hello, World!\n")  // Remove semicolon - what error do you get?
    return 0;
}
```

1. **Remove the semicolon** - compile and note the error message
2. **Fix it and try removing** `#include <cstdio>` - what happens?
3. **Fix it and try changing** `main()` to `main` - what's the error?

**Learning Goal**: Understand common compiler errors so you can fix them quickly.

#### Problem 1.3: Compilation Practice
Save your program as `intro.cpp` and practice the compile-run cycle:

```bash
# Compile
g++ -o intro intro.cpp

# Run
./intro          # Mac/Linux
intro.exe        # Windows (if using Windows compiler)
```

**Document**: What happens at each step? Time yourself - how long does compilation take?

### Problem Set 2: Variables and Types (45 minutes)

#### Problem 2.1: Temperature Converter
Convert 25°C to Fahrenheit using: F = (C × 9/5) + 32

```cpp
#include <cstdio>

int main() {
    int celsius = 25;
    // TODO: Calculate fahrenheit and print both values
    return 0;
}
```

**Expected output**: `25°C = 77°F`

**Extension**: Try with `double` instead of `int`. What's different about the result?

#### Problem 2.2: Your First Function
Write a function to calculate the square of a number:

```cpp
#include <cstdio>

// TODO: Write the square function here
int square(int x) {
    // Your code here
}

int main() {
    int num = 7;
    int result = square(num);
    printf("%d squared is %d\n", num, result);
    return 0;
}
```

**Expected output**: `7 squared is 49`

#### Problem 2.3: Multiple Variables
Create a program that uses different variable types:

```cpp
#include <cstdio>

int main() {
    int age = 20;
    double height = 5.8;    // feet  
    char grade = 'A';
    
    // TODO: Print all three variables in one sentence
    // Example: "I am 20 years old, 5.8 feet tall, and got an A grade"
    
    return 0;
}
```

**Challenge**: Figure out the correct `printf` format specifiers for each type.

### Problem Set 3: Control Flow (55 minutes)

#### Problem 3.1: Simple Decisions
Write a program that checks if a number is positive, negative, or zero:

```cpp
#include <cstdio>

int main() {
    int num = -5;  // Try different values
    
    // TODO: Use if/else to print whether num is positive, negative, or zero
    
    return 0;
}
```

#### Problem 3.2: Grade Calculator
Convert a numeric grade to letter grade:

```cpp
#include <cstdio>

int main() {
    int score = 87;  // Try different scores
    
    // TODO: Convert to letter grade (A: 90+, B: 80-89, C: 70-79, D: 60-69, F: <60)
    
    return 0;
}
```

#### Problem 3.3: Simple Loop
Print numbers 1 through 5 using a for loop:

```cpp
#include <cstdio>

int main() {
    // TODO: Write a for loop that prints 1, 2, 3, 4, 5 (each on its own line)
    
    return 0;
}
```

**Python Connection**: This is like `for i in range(1, 6):`

---

## 🔧 Quick Reference & Troubleshooting

### Top 5 Compiler Errors

| Error Message | Cause | Fix |
|--------------|-------|-----|
| `expected ';'` | Missing semicolon | Add `;` at end of statement |
| `'printf' was not declared` | Missing include | Add `#include <cstdio>` |
| `expected '(' before` | Wrong function syntax | Use `main()` not `main` |
| `undefined reference to main` | No main function | Add `int main() { return 0; }` |
| `expected '}'` | Missing brace | Match every `{` with `}` |

### Printf Format Specifiers

| Type | Specifier | Example |
|------|-----------|---------|
| `int` | `%d` | `printf("Number: %d\n", 42);` |
| `double` | `%f` | `printf("Price: %.2f\n", 9.99);` |
| `char` | `%c` | `printf("Grade: %c\n", 'A');` |
| `string` | `%s` | `printf("Name: %s\n", "Alex");` |

### Compilation Commands

```bash
# Basic compilation
g++ program.cpp -o program

# With debug info (recommended while learning)
g++ -g -Wall program.cpp -o program

# Run the program
./program        # Mac/Linux
program.exe      # Windows
```

### VS Code Shortcuts

| Action | Windows/Linux | macOS |
|--------|---------------|-------|
| **Build** | Ctrl+Shift+B | Cmd+Shift+B |
| **Terminal** | Ctrl+` | Cmd+` |
| **Command Palette** | Ctrl+Shift+P | Cmd+Shift+P |

---

## ❓ Troubleshooting

### Setup Issues

**Docker not starting?**
- Restart Docker Desktop
- Check if virtualization is enabled in BIOS
- Try running: `docker run hello-world`

**VS Code can't find compiler?**
- Make sure C/C++ extension is installed
- Restart VS Code after installing extensions
- Try building from integrated terminal manually

**Programs won't run?**
- Check file permissions: `chmod +x program`
- Make sure you're in the right directory
- Try absolute path: `/full/path/to/program`

### Common Programming Issues

**Program compiles but crashes?**
- Check for division by zero
- Verify printf format matches variable types
- Make sure functions return values when needed

**Weird characters in output?**
- Check for missing `\n` in printf statements
- Verify character encoding (usually UTF-8)

**Compilation takes forever?**
- Check for infinite loops in code
- Make sure you're not compiling the same file multiple times
- Restart your development environment

### Getting Help

**Still stuck after 15 minutes?**
1. Copy the exact error message
2. Note what you were trying to do
3. Ask for help in:
   - Office hours
   - Study groups
   - Course forum
   - Stack Overflow (for general C++ questions)

**Remember**: Every expert was once a beginner. Asking for help is part of learning!

---

## ✅ Chapter 1 Success Checklist

After completing this chapter, you should be able to:
- [ ] Set up VS Code + Docker environment
- [ ] Write a "Hello, World!" program
- [ ] Declare variables with correct types
- [ ] Use printf to output values
- [ ] Write simple functions
- [ ] Use if/else statements and basic loops
- [ ] Compile and run programs successfully
- [ ] Debug common compilation errors
- [ ] Understand how C++ differs from Python/Java

**Not there yet?** 
- Review the concepts giving you trouble
- Try the problems again
- Ask for help - that's what office hours are for!

**Ready to move on?**
- Great! Chapter 2 will dive deeper into C++ types and memory concepts
- You'll learn about pointers, arrays, and memory management
- We'll use visual debugging tools to understand how C++ handles memory

---

## 🚀 What's Next?

**Chapter 2: Types and Memory** will cover:
- Static typing vs dynamic typing
- Pointers and memory addresses  
- Arrays and strings
- Visual debugging with VS Code
- Memory management concepts

**Time to celebrate!** 🎉 You've completed your first chapter of C++ and built your development environment. The foundation is set - now we can focus on the exciting parts of C++ programming!

---

*Remember: C++ is powerful but has a learning curve. Take it one concept at a time, use the debugger to understand what's happening, and don't hesitate to ask for help. You've got this!*