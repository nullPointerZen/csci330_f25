# Homework Hints - Academic Integrity Guidelines

## 📚 Purpose

These "homework hints" are provided to help you get **unstuck** when working on assignments. They are **learning aids**, not solutions to copy wholesale.

## ✅ Appropriate Use

**When you're stuck and need a hint:**
- Study the code to understand the approach
- Learn from the implementation patterns
- Use small snippets to overcome specific roadblocks
- Adapt the concepts to your own solution

## 📝 Required Citation

**If you reference any code from homework hints:**

1. **Add a comment citing the source:**
   ```cpp
   // Reference: homework-hints/chapter-04/banking_system.cpp
   // Used RAII pattern for automatic resource cleanup
   ```

2. **Explain what it does in your own words:**
   ```cpp
   // This AccountLock class automatically locks an account in the constructor
   // and unlocks it in the destructor, ensuring cleanup even if exceptions occur
   class AccountLock {
       // ... your implementation
   };
   ```

3. **Adapt it to your specific needs** - don't copy entire functions wholesale

## 🚫 Academic Integrity Violations

**DO NOT:**
- Copy entire functions or classes without understanding
- Submit homework hints code as your own work
- Share these hints with other students (they can access them themselves)
- Use hints without proper citation and explanation

## 🎯 Learning Goals

The goal is to help you:
- Understand C++ concepts when you're stuck
- Learn proper coding patterns and practices
- Overcome specific implementation challenges
- Build confidence in your programming abilities

Remember: The struggle is part of learning. Use these hints to get unstuck, but make sure you understand what you're using!

## 📂 Directory Structure

Each chapter contains appropriately-scoped examples demonstrating the key concepts:
- **Chapter 2**: Type system analysis and student management
- **Chapter 3**: Reference usage and library management
- **Chapter 4**: RAII principles and banking system
- **Chapter 5**: Runtime polymorphism and shapes
- **Chapters 6-15**: Continue with chapter-specific concepts

## 🔧 Compilation Instructions

All solutions compile with:
```bash
g++ -std=c++17 -Wall -Wextra -g -o solution_name solution_file.cpp
```

---

**Questions about academic integrity?** Ask your instructor!