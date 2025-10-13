# Chapter 4: Warmup Exercises - Object Lifecycle (30 minutes)

## Purpose
Need some help getting started? Work through these exercises before tackling the main assignments. They'll build your confidence with constructors, destructors, and RAII. (Be sure to read the textbook chapter and lecture notes before starting these!)

---

## Exercise 1: Constructor Basics (10 minutes)

### Goal
Understand how constructors initialize objects.

### Your Task
Create `warmup1.cpp`:

```cpp
#include <cstdio>
#include <cstring>

class SimpleBook {
private:
    char title[100];
    int pages;

public:
    // Default constructor
    SimpleBook() {
        strcpy(title, "Unknown");
        pages = 0;
        printf("Default constructor called\n");
    }

    // Parameterized constructor
    SimpleBook(const char* t, int p) {
        strcpy(title, t);
        pages = p;
        printf("Parameterized constructor for '%s'\n", title);
    }

    void print() const {
        printf("Book: %s (%d pages)\n", title, pages);
    }
};

int main() {
    // Using default constructor
    SimpleBook book1;
    book1.print();

    // Using parameterized constructor
    SimpleBook book2("C++ Primer", 976);
    book2.print();

    // TODO: Create book3 with your favorite book
    // SimpleBook book3("Your Book", 123);
    // book3.print();

    return 0;
}
```

### Expected Output
```
Default constructor called
Parameterized constructor for 'C++ Primer'
Book: Unknown (0 pages)
Book: C++ Primer (976 pages)
```

### Check Yourself
- Which constructor is called for each object?
- What happens if you don't provide any constructor?
- Can you have multiple constructors? (Yes - it's called overloading!)

---

## Exercise 2: Destructor and RAII (10 minutes)

### Goal
See destructors in action and understand RAII (Resource Acquisition Is Initialization).

### Your Task
Create `warmup2.cpp`:

```cpp
#include <cstdio>

class ResourceHolder {
private:
    int id;
    static int counter;

public:
    ResourceHolder() : id(++counter) {
        printf("Resource %d acquired\n", id);
    }

    ~ResourceHolder() {
        printf("Resource %d released\n", id);
    }

    void use() {
        printf("Using resource %d\n", id);
    }
};

int ResourceHolder::counter = 0;

void demo_scope() {
    printf("Entering demo_scope\n");
    ResourceHolder local_resource;
    local_resource.use();
    printf("Leaving demo_scope\n");
    // Destructor called automatically here!
}

int main() {
    printf("Main started\n");

    ResourceHolder main_resource;
    main_resource.use();

    demo_scope();

    printf("Main ending\n");
    // main_resource destructor called here
    return 0;
}
```

### Expected Output
```
Main started
Resource 1 acquired
Using resource 1
Entering demo_scope
Resource 2 acquired
Using resource 2
Leaving demo_scope
Resource 2 released
Main ending
Resource 1 released
```

### Key Insights
- Destructors called automatically when objects go out of scope
- RAII ensures resources are always cleaned up
- Local objects destroyed in reverse order of creation

---

## Exercise 3: Copy Constructor (10 minutes)

### Goal
Understand when copy constructors are called.

### Your Task
Create `warmup3.cpp`:

```cpp
#include <cstdio>
#include <cstring>

class Student {
private:
    char name[50];
    int id;

public:
    Student(const char* n, int i) : id(i) {
        strcpy(name, n);
        printf("Constructor: %s\n", name);
    }

    // Copy constructor
    Student(const Student& other) : id(other.id) {
        strcpy(name, other.name);
        printf("Copy constructor: %s\n", name);
    }

    ~Student() {
        printf("Destructor: %s\n", name);
    }

    void print() const {
        printf("Student: %s (ID: %d)\n", name, id);
    }
};

void pass_by_value(Student s) {
    printf("In function: ");
    s.print();
}  // s destroyed here

void pass_by_reference(const Student& s) {
    printf("In function: ");
    s.print();
}  // No copy, no destructor

int main() {
    Student alice("Alice", 1001);

    printf("\nPassing by value:\n");
    pass_by_value(alice);  // Copy constructor called

    printf("\nPassing by reference:\n");
    pass_by_reference(alice);  // No copy

    printf("\nMain ending\n");
    return 0;
}
```

### Expected Output
```
Constructor: Alice

Passing by value:
Copy constructor: Alice
In function: Student: Alice (ID: 1001)
Destructor: Alice

Passing by reference:
In function: Student: Alice (ID: 1001)

Main ending
Destructor: Alice
```

### Key Observations
- Pass by value creates a copy (expensive!)
- Pass by reference avoids the copy
- Each copy needs its own destructor call

---

## Success Checklist

Before moving to main assignments:
- [ ] I understand when constructors are called
- [ ] I understand when destructors are called
- [ ] I see how RAII manages resources automatically
- [ ] I know the difference between default and parameterized constructors
- [ ] I understand when copy constructors are invoked
- [ ] I can predict object lifecycle in different scopes

---

## Quick Tips

### Constructor Types
```cpp
Class() { }                     // Default constructor
Class(params) { }               // Parameterized constructor
Class(const Class& other) { }  // Copy constructor
```

### Initialization List (More Efficient)
```cpp
class Person {
    string name;
    int age;
public:
    // Better way:
    Person(string n, int a) : name(n), age(a) { }

    // Less efficient:
    Person(string n, int a) {
        name = n;  // Assignment, not initialization
        age = a;
    }
};
```

### RAII Pattern
```cpp
class FileHandler {
    FILE* file;
public:
    FileHandler(const char* name) {
        file = fopen(name, "r");  // Acquire resource
    }
    ~FileHandler() {
        if (file) fclose(file);   // Release resource
    }
};
// File automatically closed when object goes out of scope!
```

---

## Common Pitfalls

1. **Forgetting to initialize members**
   ```cpp
   class Bad {
       int* ptr;
   public:
       Bad() { }  // ptr uninitialized - dangerous!
   };
   ```

2. **Not defining copy constructor for pointer members**
   ```cpp
   class Risky {
       int* data;
   public:
       // Need custom copy constructor if you have pointers!
   };
   ```

3. **Returning local objects by reference**
   ```cpp
   Student& bad_function() {
       Student local("Temp", 999);
       return local;  // DANGER: local destroyed!
   }
   ```

---

## Next Steps

These warmups covered the basics. The main assignments will have you:
- Build classes with multiple constructors
- Implement the Rule of Three (constructor, destructor, copy constructor)
- Create RAII wrappers for resources
- Work with move semantics (C++11)

You're ready to tackle the main assignments!