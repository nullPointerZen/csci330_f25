# Chapter 4: Object Lifecycle - Problem Sets

## 📋 Before You Begin

**✅ Prerequisites Check:**
- [ ] **Completed textbook reading**: Chapter 4 "Object Lifecycle"
- [ ] **Worked through lecture notes**: All core concepts and hands-on problems
- [ ] **Development environment ready**: VS Code + compiler setup verified

**🚫 Don't start these assignments until you've completed the textbook and lecture notes!**

## ✨ Streamlined Assignment Structure  
**New Approach**: 3 focused problems for better learning
- **Problem Set 1**: Constructor Basics (45 minutes) - REQUIRED
- **Problem Set 2**: RAII and Resource Management (60 minutes) - REQUIRED
- **Problem Set 3**: Move Semantics Introduction (30 minutes) - REQUIRED

**Total Core Time**: 2.25 hours

---

## 🎯 Problem Set 1: Constructor and Destructor Basics (45 minutes)
*Understanding object lifecycle through practical examples*

### Problem 1.1: Simple Bank Account (25 minutes)
**Objective**: Master constructor/destructor patterns through a complete banking system

Create a program called `banking_system.cpp` that implements:

**Base Account Class:**
1. Create a `BankAccount` base class with:
   - Multiple constructors (default, balance, full account info)
   - Copy constructor and assignment operator
   - Virtual destructor with logging
   - Account number generation (static counter)
   - Balance management with validation

**Specialized Account Types:**
2. Implement derived classes:
   - `SavingsAccount` (with interest rate)
   - `CheckingAccount` (with overdraft protection)
   - `BusinessAccount` (with transaction limits)

**Lifecycle Demonstration:**
3. Create accounts using different constructors
4. Show object creation/destruction order in nested scopes
5. Demonstrate copy behavior and resource management
6. Track total accounts created/destroyed (static members)

### Problem 1.2: Constructor Types (20 minutes)  
**Objective**: Apply RAII principles for transaction safety and logging

Extend your banking system with automatic resource management:

**Transaction Logger (RAII):**
1. Create a `TransactionLogger` class that:
   - Opens log file in constructor
   - Automatically closes file in destructor
   - Ensures all transactions are logged even if exceptions occur
   - Demonstrates stack-based resource management

**Safe Transaction Operations:**
2. Implement transaction safety:
   - Atomic transfer operations (all-or-nothing)
   - Automatic rollback on failure
   - Exception-safe balance updates
   - Resource cleanup even when operations fail

**Advanced RAII Patterns:**
3. Create utility classes demonstrating RAII:
   - `AccountLock` (prevents concurrent access)
   - `BalanceBackup` (automatic restoration on failure)
   - `AuditTrail` (automatic compliance logging)

**Expected Output** (partial):
```
=== Banking System with RAII Demo ===
[Constructor] Account #1001 created: John Doe, $1000.00
[Constructor] Account #1002 created: Jane Smith, $1500.00
[Constructor] Business Account #1003: Acme Corp, $10000.00

[Transaction Log] Transfer initiated: #1001 -> #1002, $200.00
[RAII Logger] Transaction log opened: bank_transactions.log
[Success] Transfer completed successfully
[RAII Logger] Transaction log closed automatically

[Destructor] Account #1003 destroyed: Final balance $9800.00
[Destructor] Account #1002 destroyed: Final balance $1700.00  
[Destructor] Account #1001 destroyed: Final balance $800.00

Summary: 3 accounts created, 3 accounts destroyed, 1 transfer completed
```

**Skills Developed**: Constructor overloading, virtual destructors, RAII patterns, exception safety

---

## 🎯 Core Assignment 2: Resource Management Framework (2 hours)
*Advanced memory management system showcasing dynamic allocation and smart resource handling*

### Part A: Dynamic Memory Manager (60 minutes)
**Objective**: Build a comprehensive memory management system with proper cleanup

Create `resource_manager.cpp` implementing:

**Resource Manager Class:**
1. Design a `ResourceManager` template class that:
   - Manages dynamic arrays of any type
   - Provides safe allocation/deallocation
   - Prevents memory leaks through RAII
   - Supports resizing and copying

**Dynamic Student Database:**
2. Apply the resource manager to build:
   - Dynamic student record system
   - Automatic capacity expansion
   - Safe copying and assignment
   - Memory usage tracking and reporting

**Memory Safety Demonstrations:**
3. Create scenarios showing:
   - What happens without proper cleanup (controlled leaks)
   - Automatic cleanup with RAII
   - Exception safety during allocation
   - Resource cleanup in complex inheritance hierarchies

### Part B: Advanced Lifecycle Patterns (60 minutes)
**Objective**: Master complex object relationships and lifecycle dependencies

Extend your resource manager with advanced patterns:

**Dependency Management:**
1. Implement objects with dependencies:
   - Parent objects that own child objects
   - Shared resources with reference counting
   - Circular dependency detection and prevention
   - Ordered destruction based on dependencies

**Factory Pattern with RAII:**
2. Create object factories that:
   - Manage object creation and registration
   - Provide automatic cleanup on program exit
   - Handle creation failures gracefully
   - Maintain object inventories and statistics

**Integration with Banking System:**
3. Combine both assignments:
   - Use resource manager for account storage
   - Implement account pools with automatic cleanup
   - Create report generators with RAII file handling
   - Build complete system with proper resource lifecycle

**Performance Analysis:**
4. Compare different approaches:
   - Stack vs heap allocation performance
   - RAII overhead vs manual management
   - Memory fragmentation analysis
   - Constructor/destructor call overhead

**Files**: `banking_system.cpp`, `resource_manager.cpp`
**Time Estimate**: 4 hours total (2 + 2)
**Skills Developed**: Advanced RAII, memory management, object relationships, performance optimization

---

## 🏆 Challenge Exercises (OPTIONAL - for advanced students)

### Challenge 1: Smart Pointer Implementation (45 minutes)
**Objective**: Build your own smart pointer classes

Implement basic smart pointers before learning STL versions:
1. Create `unique_ptr` equivalent with move semantics
2. Implement `shared_ptr` with reference counting
3. Add `weak_ptr` to break circular references
4. Build comprehensive test suite
5. Compare performance with raw pointers

### Challenge 2: Exception-Safe Programming (40 minutes)
**Objective**: Master exception safety guarantees

Create robust classes with different safety levels:
1. Basic guarantee (no leaks, but object may be in altered state)
2. Strong guarantee (rollback on exception)  
3. No-throw guarantee (operations never fail)
4. Implement exception-safe container class
5. Build automatic testing for exception scenarios

### Challenge 3: Custom Memory Allocators (50 minutes)
**Objective**: Understand memory allocation at a deeper level

Implement specialized allocators:
1. Pool allocator for fixed-size objects
2. Stack allocator for temporary objects
3. Tracking allocator with leak detection
4. Aligned allocator for SIMD operations
5. Benchmark different allocation strategies

### Challenge 4: Profiling and Optimization (35 minutes)
**Objective**: Optimize object lifecycle performance

Performance analysis project:
1. Profile constructor/destructor overhead
2. Optimize hot paths in object creation
3. Minimize memory allocations
4. Implement object pooling strategies
5. Measure and document improvements

### Challenge 5: Thread-Safe RAII (55 minutes)
**Objective**: Extend RAII to multi-threaded environments

Build thread-safe resource management:
1. Thread-safe reference counting
2. Lock-free object pools
3. Atomic resource initialization
4. Reader-writer locks for shared resources
5. Deadlock prevention strategies

---


## 🎯 Success Criteria

Before moving to Chapter 5, ensure you can:

**Constructor/Destructor Mastery:**
- [ ] Implement multiple constructor types appropriately
- [ ] Use virtual destructors correctly in inheritance hierarchies
- [ ] Understand and apply copy constructors and assignment operators
- [ ] Debug constructor/destructor call order in complex scenarios

**RAII Expertise:**
- [ ] Design classes that automatically manage resources
- [ ] Create exception-safe code using RAII principles
- [ ] Apply RAII to file handling, memory, and other resources
- [ ] Understand stack vs heap object lifecycle differences

**Memory Management:**
- [ ] Safely allocate and deallocate dynamic memory
- [ ] Prevent and debug memory leaks
- [ ] Understand object ownership and lifetime relationships
- [ ] Apply appropriate memory management patterns

**Professional Development:**
- [ ] Write robust, exception-safe C++ code
- [ ] Debug complex object lifecycle issues
- [ ] Design maintainable class hierarchies
- [ ] Apply modern C++ best practices for resource management

---

## 💡 Study Strategy

### Week 1 Focus: Core Assignment 1
- Start with simple classes, build complexity gradually
- Use debugger to watch constructor/destructor calls
- Practice with different object creation patterns
- Get comfortable with RAII concepts

### Week 2 Focus: Core Assignment 2  
- Build on RAII knowledge from Assignment 1
- Focus on dynamic memory safety
- Integrate concepts across both assignments
- Challenge yourself with error scenarios

### Advanced Students:
- Pick 2-3 challenge exercises that interest you
- Focus on understanding WHY, not just HOW
- Share your solutions and learn from others
- Consider contributing to open-source C++ projects

**Remember**: Object lifecycle is fundamental to C++ mastery. Invest the time to truly understand these concepts - they form the foundation for everything else in C++.