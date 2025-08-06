# Chapter 10: Testing - Lesson Plan

## Course: C++ for Python/Java Programmers
## Estimated Time: 2.5 hours maximum (self-paced)

---

## Development Environment Setup
**Continue using your chosen workflow from previous chapters:**
- **Option A**: Docker + Command Line (great for automated test running)
- **Option B**: VS Code + Docker (excellent for test debugging and coverage visualization)
- **Option C**: VS Code + Local Compiler

**For Chapter 10's testing concepts, VS Code's test integration shows failures clearly!**

---

## Learning Objectives

By the end of this lesson, students will be able to:

1. **Understand** the importance of unit testing in C++ development
2. **Set up and use** a basic C++ unit testing framework (simple assertions)
3. **Write** effective unit tests for C++ functions and classes
4. **Apply** test-driven development (TDD) basics in C++
5. **Debug** failed tests and improve code quality through testing
6. **Compare** C++ testing approaches with Python (unittest, pytest) and Java (JUnit)

---

## Key Concepts with Python/Java Equivalencies

### 1. Testing Framework Comparison

| Language | Popular Frameworks | Basic Assertion | Test Organization |
|----------|-------------------|-----------------|-------------------|
| **C++** | Simple Assert / Catch2 / Google Test | `assert(condition)` | Functions or classes |
| **Python** | unittest / pytest | `assert condition` / `self.assertEqual()` | Classes (unittest) or functions (pytest) |
| **Java** | JUnit | `assertEquals()` / `assertTrue()` | Methods in test classes |

### 2. Test Structure Patterns

| Language | Setup Pattern | Test Method | Cleanup |
|----------|---------------|-------------|---------|
| **C++** | Constructor/Setup function | Regular function call | Destructor/Cleanup function |
| **Python** | `setUp()` method | `test_*` methods | `tearDown()` method |
| **Java** | `@Before` annotation | `@Test` annotation | `@After` annotation |

### 3. Assertion Types

| Concept | C++ (Simple) | Python (unittest) | Java (JUnit) |
|---------|--------------|-------------------|--------------|
| **Equality** | `assert(a == b)` | `self.assertEqual(a, b)` | `assertEquals(a, b)` |
| **Truth** | `assert(condition)` | `self.assertTrue(condition)` | `assertTrue(condition)` |
| **Exceptions** | try/catch block | `self.assertRaises()` | `@Test(expected=...)` |

### 4. Test Organization

| Aspect | C++ | Python | Java |
|--------|-----|--------|------|
| **File Naming** | `test_*.cpp` or `*_test.cpp` | `test_*.py` | `*Test.java` |
| **Test Discovery** | Manual compilation | `python -m pytest` | IDE or Maven/Gradle |
| **Running Tests** | Execute compiled binary | `python -m unittest` | `java -cp ... TestRunner` |

---

## Lesson Structure

### Pre-Work: Testing Mindset (Not counted in course time)
**Complete before starting Chapter 10**

#### Required Pre-Work
1. Review simple debugging techniques from previous chapters
2. Think about how you've tested programs so far (print statements, manual testing)
3. Consider: "How do you know your code works correctly?"

#### Background Knowledge
- Basic C++ functions and classes (Chapters 1-9)
- Understanding of compilation and linking
- Familiarity with basic debugging

### Module 1: Why Testing Matters (30 minutes)

#### Content Delivery
- **Testing Motivation**: Why manual testing isn't enough
- **Types of Testing**: Unit tests vs integration tests vs system tests
- **Testing in C++**: Challenges and benefits compared to Python/Java

#### Activities
1. Examine a simple C++ function with bugs
2. Try to find bugs through manual testing (limited success)
3. Discuss why automated testing helps

#### Key Concepts
- Tests as documentation
- Regression prevention
- Confidence in refactoring

#### Check for Understanding
- Can explain why automated testing is important
- Understands the difference between testing strategies

### Module 2: Simple Testing Framework (45 minutes)

#### Content Delivery
- **Basic Assertions**: Using `assert()` and custom assertion functions
- **Test Structure**: Arrange-Act-Assert pattern
- **Simple Framework**: Building basic test utilities

#### Activities
1. Write simple assertion functions
2. Create basic test runner
3. Test a simple calculator function

#### Practice Focus
- Writing clear test functions
- Understanding assertion failures
- Basic test organization

### Module 3: Unit Testing Patterns (60 minutes)

#### Content Delivery
- **Test Organization**: How to structure test files
- **Test Cases**: Testing normal cases, edge cases, error cases
- **Test Data**: Setting up test inputs and expected outputs

#### Activities
1. Write comprehensive tests for a string manipulation function
2. Test edge cases (empty strings, null pointers)
3. Practice testing class methods

#### Key Concepts
- Comprehensive test coverage
- Testing both happy path and error conditions
- Organizing tests logically

### Module 4: Test-Driven Development Basics (35 minutes)

#### Content Delivery
- **TDD Cycle**: Red-Green-Refactor
- **Writing Tests First**: Benefits and challenges
- **Debugging Tests**: Understanding test failures

#### Activities
1. Implement a simple function using TDD approach
2. Experience the red-green-refactor cycle
3. Debug failing tests and improve code

#### Final Check
- Can write tests before implementing functions
- Understands how to debug test failures
- Sees value in TDD approach

---

## Assessment Strategy

### Formative Assessment (Throughout)
- **Code Review**: Students review each other's test code
- **Test Debugging**: Fix intentionally broken tests
- **Quick Checks**: After each module, verify understanding

### Summative Assessment  
- **Testing Project** (45 minutes):
  - Write comprehensive tests for a provided C++ class
  - Include tests for normal operation, edge cases, and error conditions
  - Use TDD to add one new method to the class
  - All tests must pass and demonstrate good testing practices

### Rubric (Pass/Fail)
| Criteria | Pass Requirement |
|----------|------------------|
| Test Coverage | Tests cover normal cases, edge cases, and error conditions |
| Test Quality | Tests are clear, focused, and properly organized |
| TDD Implementation | New method implemented using TDD cycle |
| Code Quality | All tests pass and code follows good practices |

---

## Practical Examples

### Calculator Class Testing
Students will work with a calculator class similar to familiar examples but focus on testing:

```cpp
class Calculator {
public:
    int add(int a, int b);
    int subtract(int a, int b);
    int multiply(int a, int b);
    double divide(int a, int b);  // Throws exception for division by zero
};
```

### String Utilities Testing
Testing string manipulation functions (similar to Python string methods):

```cpp
bool startsWith(const std::string& str, const std::string& prefix);
std::string removeSpaces(const std::string& str);
std::vector<std::string> split(const std::string& str, char delimiter);
```

---

## Connection to Python/Java Testing

### Python unittest Parallel
```python
import unittest

class TestCalculator(unittest.TestCase):
    def test_add(self):
        calc = Calculator()
        self.assertEqual(calc.add(2, 3), 5)
```

### C++ Equivalent
```cpp
void test_add() {
    Calculator calc;
    assert(calc.add(2, 3) == 5);
    printf("test_add: PASSED\n");
}
```

### Java JUnit Parallel
```java
@Test
public void testAdd() {
    Calculator calc = new Calculator();
    assertEquals(5, calc.add(2, 3));
}
```

---

## Additional Resources

### Required Reading
- Chapter 10: "Testing" from C++ Crash Course (focus on basic concepts)

### Supplementary Materials
- [Simple C++ Testing Frameworks](https://github.com/catchorg/Catch2) - For advanced students
- [TDD in C++](https://www.agilealliance.org/glossary/tdd/) - Test-driven development principles
- [Google Test Documentation](https://google.github.io/googletest/) - Industry-standard framework (reference only)

### Office Hours Topics
- Setting up testing environments
- Debugging test failures
- When and how to test private methods
- Testing best practices

---

## Teaching Notes

### Common Challenges
1. **Testing Mindset**: Students often want to skip testing to "save time"
2. **C++ Complexity**: Testing in C++ requires more setup than Python/Java
3. **Assertion Failures**: Understanding what failed and why

### Differentiation
- **For Advanced Students**: Introduce mock objects and advanced testing patterns
- **For Struggling Students**: Focus on simple assertion-based testing first

### Time Management
- Keep initial examples very simple
- Focus on testing concepts over framework complexity
- Use familiar functions (calculator, string operations) as test subjects

### Practical Tips
- Start with testing functions before testing classes
- Emphasize readable test names and clear assertions
- Show how tests serve as executable documentation

---

## Success Indicators

Students successfully completing this chapter will:
- Write clear, comprehensive unit tests
- Use testing to improve code quality
- Understand the value of automated testing
- Be prepared for more advanced testing frameworks
- Have practical experience with test-driven development

This foundation prepares students for real-world C++ development where testing is essential for maintainable, reliable code.