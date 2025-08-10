# Chapter 1: Quick Help Guide

## Top 5 Compiler Errors (Fix These First!)

| Error Message | Likely Cause | Quick Fix |
|--------------|--------------|-----------|
| `expected ';'` | Missing semicolon | Add `;` at end of previous line |
| `'printf' was not declared` | Missing include | Add `#include <cstdio>` at top |
| `expected '(' before` | Wrong function syntax | Check parentheses: `main()` not `main` |
| `undefined reference` | Function not defined | Make sure you wrote the function body |
| `expected '}'` | Missing closing brace | Match every `{` with a `}` |

## Compilation Quick Reference

```bash
# Compile your program
g++ -o program_name source_file.cpp

# Run your program
./program_name        # Mac/Linux
program_name.exe      # Windows
```

## C++ vs Python/Java Quick Comparison

| Need | C++ | Python | Java |
|------|-----|--------|------|
| **Variable** | `int x = 5;` | `x = 5` | `int x = 5;` |
| **Print** | `printf("Hi\n");` | `print("Hi")` | `System.out.println("Hi");` |
| **Function** | `int add(int a, int b)` | `def add(a, b):` | `public int add(int a, int b)` |

## Stuck? Try This!

**Program won't compile?**
1. Check for missing semicolons (`;`)
2. Verify `#include <cstdio>` at top
3. Make sure `main()` has parentheses

**Program compiles but crashes?**
1. Check for division by zero
2. Verify printf format matches variable types
3. Make sure functions return values when expected

**Getting overwhelmed?**
- Take a 10-minute break
- Review one concept at a time
- Ask for help - this is normal!
- Remember: advanced students struggled with this too

## Environment Setup (Pre-Work)

### Windows: Visual Studio
1. Download Visual Studio Community (free)
2. Select "Desktop development with C++"
3. Create new Console App project

### Mac: Xcode  
1. Install Xcode from App Store
2. Open Terminal, type: `xcode-select --install`
3. Create new Command Line Tool (C++)

### Linux: GCC
```bash
sudo apt install g++          # Ubuntu/Debian
sudo dnf install gcc-c++      # Fedora
```

### Online Backup Option
If local setup fails: Use [Replit.com](https://replit.com) with C++ template

## Time Management Tips

- **Module 1**: 30 minutes (Hello World basics)
- **Module 2**: 45 minutes (Variables and types)  
- **Module 3**: 60 minutes (Functions and if/else)
- **Module 4**: 35 minutes (Integration practice)
- **Total**: 2.5 hours maximum

**Taking longer?** That's normal! Ask for help rather than struggling alone.

## Success Checklist

After Chapter 1, you should be able to:
- [ ] Write a Hello World program
- [ ] Declare variables with proper types
- [ ] Write simple functions
- [ ] Use if/else statements
- [ ] Compile and run programs successfully
- [ ] Fix basic compilation errors

**Not there yet?** Review the concepts you're missing and try the problems again.