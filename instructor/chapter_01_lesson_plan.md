# Chapter 1: Up and Running - Lesson Plan

## Course: C++ for Python/Java Programmers
## Delivery Mode: Self-Paced, Asynchronous
## Total Learning Time: 7.25-8.25 hours across 3 components

---

## 📖 Three-Component Learning Sequence

This chapter follows a structured, self-paced approach where each component builds on the previous:

### Component 1: Textbook Foundation (1-2 hours)
**Student Activity**: Read Chapter 1 "Up and Running" from C++ Crash Course
- **Purpose**: Establish core theoretical foundation
- **Instructor Role**: None (self-paced reading)
- **Assessment**: Comprehension verified through subsequent components

### Component 2: Contextualized Tutorial (4-5 hours) 
**Student Activity**: Work through `chapter_01_lecture_notes.md`
- **Purpose**: Bridge textbook concepts to Python/Java knowledge with hands-on practice
- **Instructor Role**: Available for office hours support
- **Content**: Comparative explanations + guided practice problems

### Component 3: Applied Assessment (2.25 hours)
**Student Activity**: Complete `chapter_01_assignments.md` 
- **Purpose**: Demonstrate mastery through independent problem-solving
- **Instructor Role**: Grade final submissions
- **Assessment**: Mini calculator project + foundational exercises

---

## 🎯 Instructor Focus Areas

### Key Teaching Points
**Emphasize the Learning Sequence**:
- Students MUST complete textbook reading before lecture notes
- Lecture notes contextualize and reinforce textbook concepts
- Assignments test combined knowledge from both sources
- **Critical**: Don't let students skip ahead or work out of sequence

---

## Learning Objectives

By the end of this three-component sequence, students will be able to:

1. **Set up** a C++ development environment on their operating system
2. **Write, compile, and run** a basic C++ program
3. **Explain** the C++ compilation process (preprocessor, compiler, linker)
4. **Use** basic C++ syntax including variables, functions, and control flow
5. **Apply** debugging techniques using IDE debuggers
6. **Compare** C++ syntax and concepts with Python/Java equivalents

---

## Key Concepts with Python/Java Equivalencies

### 1. Program Structure & Entry Point

| Language | Entry Point | Notes |
|----------|-------------|-------|
| **C++** | `int main() {`<br>&nbsp;&nbsp;`return 0;`<br>`}` | Required; returns exit code |
| **Python** | No explicit main | Convention: `if __name__ == "__main__":` |
| **Java** | `public static void main(String[] args) {}` | Must be in a class |

### 2. Compilation Model

| Language | Type | Process | Output |
|----------|------|---------|--------|
| **C++** | Compiled | Source → Object → Executable | Machine code |
| **Python** | Interpreted | Source → Bytecode (automatic) | Runs directly |
| **Java** | Hybrid | Source → Bytecode → JVM | Platform independent |

### 3. Including External Code

| Language | Syntax | When Processed | Example |
|----------|--------|----------------|---------|
| **C++** | `#include <header>` | Preprocessor (before compilation) | `#include <cstdio>` |
| **Python** | `import module` | Runtime | `import math` |
| **Java** | `import package.Class;` | Compile time | `import java.util.Scanner;` |

### 4. Variable Declaration

| Aspect | C++ | Python | Java |
|--------|-----|--------|------|
| **Declaration** | `int x;` | `x = None` or just use | `int x;` |
| **Initialization** | `int x = 42;` | `x = 42` | `int x = 42;` |
| **Type Required** | Yes (static) | No (dynamic) | Yes (static) |
| **Type Change** | Not allowed | Allowed | Not allowed |

### 5. Console Output

| Language | Basic Output | Formatted Output |
|----------|--------------|------------------|
| **C++** | `printf("Hello\n");` | `printf("Value: %d\n", x);` |
| **Python** | `print("Hello")` | `print(f"Value: {x}")` |
| **Java** | `System.out.println("Hello");` | `System.out.printf("Value: %d\n", x);` |

### 6. Function Definition

| Language | Syntax | Return Type |
|----------|--------|-------------|
| **C++** | `int add(int a, int b) {`<br>&nbsp;&nbsp;`return a + b;`<br>`}` | Must specify |
| **Python** | `def add(a, b):`<br>&nbsp;&nbsp;`return a + b` | Dynamic |
| **Java** | `public static int add(int a, int b) {`<br>&nbsp;&nbsp;`return a + b;`<br>`}` | Must specify |

---

## Student Support Strategy

### Component-Based Office Hours Support

#### During Component 1 (Textbook Reading)
**Student Activity**: Independent reading
**Instructor Support**: 
- Minimal - reading is foundational
- Answer clarifying questions about concepts
- **Red Flag**: Students asking about programming syntax during reading phase

#### During Component 2 (Lecture Notes Tutorial)  
**Student Activity**: Contextual learning + hands-on practice
**Instructor Support**:
- **High availability** - this is where students need most help
- Environment setup troubleshooting
- Concept clarification (textbook + Python/Java bridges)
- Debugging compilation errors
- **Red Flag**: Students who haven't read textbook (refer them back to Component 1)

#### During Component 3 (Assignments)
**Student Activity**: Independent problem-solving
**Instructor Support**:
- **Minimal guidance** - this is assessment
- Clarify assignment requirements only
- **No debugging help** - they should be ready by this stage
- **Red Flag**: Students struggling with basic concepts (incomplete earlier components)

---

## Detailed Component Structure

### Component 1: Textbook Foundation (1-2 hours)
**Student Responsibility**: Read Chapter 1 independently

**Learning Coverage**:
- C++ program structure and compilation
- Basic syntax and language features  
- Fundamental programming concepts in C++

**Instructor Monitoring**: 
- No direct teaching required
- Track completion through Component 2 performance

### Component 2: Contextualized Tutorial (4-5 hours)
**Student Activity**: Work through lecture notes with hands-on practice

#### Module 2A: Environment Setup (30-60 minutes)
**One-time setup - not counted in regular chapter time**
**Complete before starting Chapter 1**

#### Required Pre-Work
1. Choose your development workflow:
   - **Option A**: Docker + Command Line (lightweight)
   - **Option B**: VS Code + Docker (recommended for most students)
   - **Option C**: VS Code + Local Compiler (quick start)
2. Follow the setup guide for your chosen workflow
3. Verify installation by compiling a test program
4. Submit screenshot showing successful "Hello, World!" compilation

#### Support Available
- Detailed setup guides for all workflow options
- Office hours for troubleshooting
- Multiple backup options if primary setup fails

### Module 1: First C++ Program (30 minutes)

#### Content Delivery
- **Quick Comparison**: Hello World in C++, Python, and Java
- **Essential Syntax**: Basic program structure
- **Compilation Basics**: Why C++ needs compilation (5 minute overview)

#### Activities
1. Type the Hello World program
2. Compile and run successfully
3. Modify to print personal information

#### Check for Understanding
- Program compiles and runs correctly
- Can explain basic syntax differences

### Module 2: Variables and Types (45 minutes)

#### Content Delivery
- **Static Typing**: Why types matter in C++
- **Basic Types**: int, double, char
- **Variable Declaration**: Required vs optional in Python/Java

#### Activities
1. Temperature conversion program
2. Practice with different data types
3. Simple arithmetic operations

#### Key Concepts
- Type declarations are mandatory
- Semicolons end every statement
- Format specifiers for printf

### Module 3: Functions and Control Flow (60 minutes)

#### Content Delivery
- **Function Basics**: Declaration, definition, calling
- **Control Flow**: if/else statements
- **Function Order**: Declare before use

#### Activities
1. Write simple functions (square, add)
2. Create decision-making programs
3. Combine functions with control flow

#### Practice Focus
- Function syntax and calling
- Basic if/else logic
- Parameter passing

### Module 4: Integration Practice (35 minutes)

#### Content Delivery
- **Putting It Together**: Review all concepts
- **Simple Debugging**: Basic error checking
- **Testing Strategies**: Verify your programs work

#### Activities
1. Mini calculator project
2. Test with different inputs
3. Handle simple errors (division by zero)

#### Final Check
- All concepts work together
- Can write, compile, run, and test programs

---

### Component 3: Applied Assessment (2.25 hours)
**Student Activity**: Complete assignments independently

**Assessment Philosophy**: Students apply combined knowledge from textbook + lecture notes

#### Problem Set Structure:
1. **Getting Started (30 min)**: Basic program structure and compilation
2. **Basic Programming (45 min)**: Variables, functions, control flow  
3. **Mini Calculator Project (60 min)**: Integration of all concepts

**Instructor Role**: Grade submissions, provide feedback

---

## Assessment Strategy

### Component-Based Assessment

#### Component 1 Assessment
**Method**: Indirect (through Component 2 performance)
**Indicator**: Students who struggle in Component 2 likely didn't complete reading

#### Component 2 Assessment  
**Method**: Formative (practice problems are scaffolded)
**Purpose**: Build confidence and skill before Component 3

#### Component 3 Assessment
**Method**: Summative (graded assignments)
**Requirements**: Mini Calculator Project + foundational exercises

### Rubric (Pass/Fail)
| Criteria | Pass Requirement |
|----------|------------------|
| Compilation | Program compiles cleanly without errors |
| Basic Functions | Add, subtract, multiply functions work correctly |
| Output Format | Results print clearly with proper labels |
| Zero Division | Division by zero shows error message |

---

## Additional Resources

### Required Reading
- Chapter 1: "Up and Running" from C++ Crash Course

### Supplementary Materials
- [cppreference.com](https://cppreference.com) - C++ reference
- [Compiler Explorer](https://godbolt.org) - See assembly output
- [C++ vs Python vs Java Cheat Sheet](#) - Quick syntax reference

### Development Environment Guides
- `chapter_01_development_workflows.md` - Compare all workflow options
- `chapter_01_docker_setup.md` - Docker installation and setup
- `chapter_01_vscode_setup.md` - VS Code configuration guide
- `chapter_01_github_workflow.md` - Professional Git workflow
- `chapter_01_cmake_basics.md` - Build system introduction
- `docker_troubleshooting.md` - Common issues and solutions

### Office Hours Topics
- Troubleshooting environment setup
- Understanding compiler errors
- Transitioning from interpreted to compiled languages

---

## Teaching Notes for Self-Paced Delivery

### Common Student Issues by Component

#### Component 1 Issues (Textbook Reading)
**Problem**: Students skip reading and jump to Component 2
**Solution**: Emphasize that lecture notes assume textbook knowledge
**Red Flag**: Students asking basic questions answered in textbook

#### Component 2 Issues (Lecture Notes)
**Problem**: Environment setup difficulties
**Solution**: Multiple backup options (online compilers, pre-configured containers)
**Red Flag**: Students spending too much time on setup vs. learning

#### Component 3 Issues (Assignments)
**Problem**: Students not ready for independent work
**Solution**: Refer back to Components 1-2, not debugging help
**Red Flag**: Basic syntax errors indicate incomplete foundation

### Supporting Weak Students
- **Don't lower standards** - maintain the three-component sequence
- **Provide more support in Component 2** (where teaching happens)
- **Emphasize that explanation in lecture notes helps everyone**
- **Office hours focus**: Environment and concept clarification, not assignment debugging

### Supporting Strong Students  
- **Let them move quickly through Component 2**
- **Encourage exploration of compiler flags, optimization**
- **Component 3 extensions**: More complex calculator features

### Sequence Enforcement
- **Monitor student questions** to identify sequence violations
- **Redirect students back to prerequisite components**  
- **Don't provide shortcuts** - the sequence builds proper foundation