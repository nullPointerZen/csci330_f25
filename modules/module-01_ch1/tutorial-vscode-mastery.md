# Tutorial: VS Code + C++ Development Mastery

## 🎯 Learning Objectives

After completing this tutorial, you will:
- Master essential VS Code shortcuts for C++ development
- Set up and use integrated debugging effectively  
- Troubleshoot common compilation and tool issues
- Navigate projects efficiently using VS Code features
- Integrate Git workflow for assignment submissions

**⏱️ Time Estimate**: 30-45 minutes  
**Prerequisites**: Completed Chapter 1 lecture notes and basic VS Code setup

---

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] VS Code installed and configured (from DEVELOPMENT_SETUP.md)
- [ ] C++ compiler working (tested with simple program)
- [ ] Chapter 1 lecture notes completed
- [ ] Basic understanding of C++ program structure

**🚫 Don't continue** until VS Code can compile and run a basic C++ program.

---

## 🛠️ Section 1: Essential VS Code Shortcuts (10 minutes)

### The Power User Workflow

Instead of clicking through menus every time, master these essential shortcuts:

#### **Building and Running**
| Action | Windows/Linux | macOS | What It Does |
|--------|---------------|-------|-------------|
| **Build** | `Ctrl+Shift+B` | `Cmd+Shift+B` | Compile your program |
| **Run** | `Ctrl+F5` | `Cmd+F5` | Run without debugging |
| **Debug** | `F5` | `F5` | Run with debugging |
| **Terminal** | `Ctrl+`` (backtick) | `Cmd+`` | Toggle integrated terminal |

#### **Navigation and Editing**
| Action | Windows/Linux | macOS | What It Does |
|--------|---------------|-------|-------------|
| **Command Palette** | `Ctrl+Shift+P` | `Cmd+Shift+P` | Access all commands |
| **Quick Open** | `Ctrl+P` | `Cmd+P` | Quickly open files |
| **Go to Line** | `Ctrl+G` | `Cmd+G` | Jump to specific line |
| **Find/Replace** | `Ctrl+F` / `Ctrl+H` | `Cmd+F` / `Cmd+Option+F` | Search and replace |

### ✅ Checkpoint 1: Shortcut Practice
**Test**: Use shortcuts to build and run a simple program

1. Create a new file called `shortcut_test.cpp`:
```cpp
#include <iostream>
int main() {
    std::cout << "Testing VS Code shortcuts!\n";
    return 0;
}
```

2. **Practice the workflow:**
   - [ ] Save with `Ctrl+S` (Windows/Linux) or `Cmd+S` (macOS)
   - [ ] Build with `Ctrl+Shift+B` (Windows/Linux) or `Cmd+Shift+B` (macOS)
   - [ ] Run with `Ctrl+F5` (Windows/Linux) or `Cmd+F5` (macOS)
   - [ ] Open terminal with `Ctrl+`` (Windows/Linux) or `Cmd+`` (macOS)

**Success Criteria**: You can complete this build-run cycle in under 30 seconds using only shortcuts.

**Stuck?** Check that your compiler is properly configured in VS Code settings.

---

## 🐛 Section 2: Integrated Debugging Mastery (15 minutes)

### Setting Up Debug Configuration

VS Code's integrated debugger is incredibly powerful. Here's how to master it:

#### **Basic Debugging Workflow**

1. **Set Breakpoints**: Click left of line numbers (red dot appears)
2. **Start Debugging**: Press `F5`
3. **Step Through Code**: Use `F10` (step over), `F11` (step into)
4. **Inspect Variables**: Hover over variables or check Variables panel

### Hands-On Debug Practice

Create this program for debugging practice:

```cpp
// debug_practice.cpp
#include <iostream>
#include <vector>

int calculate_sum(const std::vector<int>& numbers) {
    int total = 0;
    for (int i = 0; i < numbers.size(); i++) {
        total += numbers[i];
    }
    return total;
}

int main() {
    std::vector<int> values = {10, 20, 30, 40};
    int result = calculate_sum(values);
    std::cout << "Sum is: " << result << std::endl;
    return 0;
}
```

#### **Debug Session Steps:**

1. **Set breakpoints** on these lines:
   - Line with `int result = calculate_sum(values);`
   - Line with `total += numbers[i];` (inside the loop)
   - Line with `return total;`

2. **Start debugging** with `F5`

3. **When program stops at first breakpoint:**
   - Look at the Variables panel - can you see `values` array?
   - Press `F11` to step INTO the function

4. **Inside the function:**
   - Use `F10` to step through the loop
   - Watch how `total` changes in Variables panel
   - Watch how `i` increments each iteration

5. **Advanced inspection:**
   - Hover over `numbers[i]` to see current value
   - In the Debug Console, type `total` to see current value
   - Try typing `numbers.size()` in Debug Console

### ✅ Checkpoint 2: Debug Workflow Mastery
**Test**: Successfully debug a program with intentional bug

Modify the calculate_sum function to have a bug:
```cpp
int calculate_sum(const std::vector<int>& numbers) {
    int total = 0;
    for (int i = 1; i < numbers.size(); i++) {  // Bug: starts at 1 instead of 0
        total += numbers[i];
    }
    return total;
}
```

**Your task:**
- [ ] Set breakpoints and run debugger
- [ ] Step through the loop and observe what's happening
- [ ] Identify that first element (index 0) is being skipped
- [ ] Fix the bug by changing `i = 1` to `i = 0`
- [ ] Verify fix by running debugger again

**Success Criteria**: You can identify and fix the bug using VS Code's debugging tools.

---

## 📁 Section 3: Project Navigation & File Management (10 minutes)

### Efficient Project Navigation

As your programs get larger, efficient navigation becomes crucial:

#### **Multi-file Project Setup**
```
my_project/
├── main.cpp
├── calculator.cpp
├── calculator.h
└── utils.cpp
```

#### **Navigation Shortcuts**
| Action | Shortcut | Usage |
|--------|----------|-------|
| **Quick Open** | `Ctrl+P` / `Cmd+P` | Type filename to open |
| **Go to Definition** | `F12` | Jump to function/variable definition |
| **Go to Declaration** | `Ctrl+F12` / `Cmd+F12` | Jump to declaration |
| **Find All References** | `Shift+F12` | See all uses of symbol |
| **Navigate Back** | `Alt+Left` / `Ctrl+-` | Return to previous location |

### ✅ Checkpoint 3: Navigation Practice
**Test**: Navigate efficiently in a multi-file project

1. Create these files in a folder:

**main.cpp:**
```cpp
#include "calculator.h"
#include <iostream>

int main() {
    int result = add(5, 3);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

**calculator.h:**
```cpp
#ifndef CALCULATOR_H
#define CALCULATOR_H

int add(int a, int b);

#endif
```

**calculator.cpp:**
```cpp
#include "calculator.h"

int add(int a, int b) {
    return a + b;
}
```

2. **Navigation tests:**
   - [ ] In main.cpp, press `F12` while cursor is on `add` - jumps to definition
   - [ ] Use `Ctrl+P` / `Cmd+P` and type "calc" - quickly opens calculator files
   - [ ] Use `Alt+Left` / `Ctrl+-` to navigate back
   - [ ] Right-click on `add` and select "Find All References"

**Success Criteria**: You can navigate between files quickly without using file explorer.

---

## 🔗 Section 4: Git Integration Workflow (10 minutes)

### Built-in Git Features

VS Code has powerful Git integration for assignment submissions:

#### **Git Panel Features**
- **Source Control View**: Click git icon in sidebar or `Ctrl+Shift+G`
- **Stage Changes**: Click `+` next to modified files
- **Commit**: Enter message and click checkmark
- **Push/Pull**: Use `...` menu for sync operations

### Assignment Submission Workflow

Here's the typical workflow for assignment submissions:

#### **Step-by-Step Git Process**
1. **Check Status**: Open Source Control view (`Ctrl+Shift+G`)
2. **Review Changes**: Click on modified files to see differences
3. **Stage Files**: Click `+` next to files you want to commit
4. **Write Commit Message**: Describe what you completed
5. **Commit**: Click checkmark or `Ctrl+Enter`
6. **Push**: Click `...` menu → Push (or sync if configured)

### ✅ Checkpoint 4: Git Workflow Practice
**Test**: Complete a full Git workflow in VS Code

1. **Modify your shortcut_test.cpp** file:
```cpp
#include <iostream>
int main() {
    std::cout << "Testing VS Code shortcuts and Git!\n";
    std::cout << "This change will be committed.\n";
    return 0;
}
```

2. **Git workflow:**
   - [ ] Open Source Control view (`Ctrl+Shift+G`)
   - [ ] See your modified file listed
   - [ ] Click on file to view differences (green = added, red = removed)
   - [ ] Stage the file by clicking `+`
   - [ ] Enter commit message: "Add Git workflow practice"
   - [ ] Commit by clicking checkmark
   - [ ] (If connected to remote) Push changes

**Success Criteria**: You can complete assignment submission workflow entirely within VS Code.

---

## 🛠️ Section 5: Troubleshooting Common Issues (5 minutes)

### When Things Go Wrong

Every developer encounters these issues. Here's how to solve them quickly:

#### **Compilation Problems**
| Problem | Solution |
|---------|----------|
| **"g++ not found"** | Check compiler installation, restart VS Code |
| **"No build task"** | Use `Ctrl+Shift+P` → "Tasks: Configure Task" |
| **Include errors** | Check file paths, ensure headers in correct location |
| **Permission denied** | Check file permissions, run as administrator if needed |

#### **Debugging Problems**
| Problem | Solution |
|---------|----------|
| **No debug config** | Use `Ctrl+Shift+P` → "Debug: Add Configuration" |
| **Breakpoints not hit** | Ensure you're building with debug info (`-g` flag) |
| **Variables not shown** | Check optimization level, use Debug build |

#### **Git Problems**
| Problem | Solution |
|---------|----------|
| **Not a git repository** | Initialize with `git init` in terminal |
| **Permission denied** | Check SSH keys or use HTTPS |
| **Merge conflicts** | Use VS Code's built-in merge editor |

### ✅ Checkpoint 5: Problem-Solving Skills
**Test**: Intentionally create and solve a common problem

1. **Create a compilation error:**
```cpp
#include <iostream>
int main() {
    std::cout << "Missing semicolon here"  // Intentional error
    return 0;
}
```

2. **Problem-solving process:**
   - [ ] Try to build (`Ctrl+Shift+B`)
   - [ ] Read error message carefully
   - [ ] Identify the line number and issue
   - [ ] Fix the missing semicolon
   - [ ] Build again to verify fix

**Success Criteria**: You can interpret compiler error messages and fix basic syntax errors quickly.

---

## 🎯 Final Challenge: Complete Development Workflow

**Time Limit**: 10 minutes

Create a complete C++ program using everything you've learned:

### **Requirements**
1. **Create** a program that calculates the area of a rectangle
2. **Use** function separation (declaration in header, definition in source)
3. **Debug** the program with breakpoints
4. **Test** with multiple input values
5. **Commit** your work to Git

### **Files to Create**
**geometry.h:**
```cpp
#ifndef GEOMETRY_H
#define GEOMETRY_H

double rectangle_area(double width, double height);

#endif
```

**geometry.cpp:**
```cpp
#include "geometry.h"

double rectangle_area(double width, double height) {
    return width * height;  // Set breakpoint here
}
```

**main.cpp:**
```cpp
#include "geometry.h"
#include <iostream>

int main() {
    double width = 5.0;
    double height = 3.0;
    double area = rectangle_area(width, height);  // Set breakpoint here
    std::cout << "Area: " << area << std::endl;
    return 0;
}
```

### ✅ Final Verification Checklist
- [ ] **Build**: Used `Ctrl+Shift+B` to compile successfully
- [ ] **Debug**: Set breakpoints and stepped through code
- [ ] **Navigate**: Used `F12` to jump to function definition
- [ ] **Variables**: Inspected variable values during debugging
- [ ] **Git**: Staged, committed, and (if applicable) pushed changes
- [ ] **Test**: Verified program produces correct output
- [ ] **Time**: Completed entire workflow in under 10 minutes

---

## 🎉 Congratulations!

You've mastered the essential VS Code workflow for C++ development! You now have the skills to:
- Build and debug C++ programs efficiently
- Navigate multi-file projects with ease
- Troubleshoot common development issues
- Manage your code with integrated Git workflow

### **Next Steps**
- Apply these skills to your Chapter 1 assignments
- Reference this tutorial whenever you encounter tool-related issues
- As projects get more complex, these skills will save you hours of frustration

### **Quick Reference Card**
| Action | Shortcut | When to Use |
|--------|----------|-------------|
| Build | `Ctrl+Shift+B` | Before testing code |
| Debug | `F5` | When code doesn't work as expected |
| Quick Open | `Ctrl+P` | Finding files quickly |
| Go to Definition | `F12` | Understanding code structure |
| Git View | `Ctrl+Shift+G` | Assignment submissions |

**Keep this tutorial handy** - you'll reference it throughout the course!