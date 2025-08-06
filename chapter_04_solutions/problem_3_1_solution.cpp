// Problem 3.1: Stack vs Heap Objects Solution
// Demonstrates the difference between automatic and manual object management

#include <cstdio>

class Timer {
public:
    Timer(const char* name) : name{name} {
        printf("Timer '%s' started\n", name);
    }
    
    ~Timer() {
        printf("Timer '%s' finished\n", name);
    }
    
    void tick() {
        printf("Timer '%s' tick\n", name);
    }
    
private:
    const char* name;
};

int main() {
    printf("=== Creating stack object ===\n");
    Timer stack_timer{"StackTimer"};
    stack_timer.tick();
    
    printf("\n=== Creating heap object ===\n");
    Timer* heap_timer = new Timer{"HeapTimer"};
    heap_timer->tick();
    
    printf("\n=== Manual cleanup of heap object ===\n");
    delete heap_timer;  // Destructor called here for heap object
    heap_timer = nullptr; // Good practice: prevent accidental reuse
    
    printf("\n=== About to exit main ===\n");
    return 0;
    // Destructor called automatically here for stack_timer
}

/* 
Compilation command:
g++ -o stack_vs_heap problem_3_1_solution.cpp

Expected Output:
=== Creating stack object ===
Timer 'StackTimer' started
Timer 'StackTimer' tick

=== Creating heap object ===
Timer 'HeapTimer' started
Timer 'HeapTimer' tick

=== Manual cleanup of heap object ===
Timer 'HeapTimer' finished

=== About to exit main ===
Timer 'StackTimer' finished

Key Learning Points:
1. Stack objects: Automatic cleanup when scope ends
2. Heap objects: Manual cleanup required with delete
3. Stack timer destroyed AFTER heap timer (LIFO - Last In, First Out)
4. Use -> operator for heap objects, . operator for stack objects
5. Setting pointer to nullptr after delete prevents accidental reuse
6. Prefer stack objects when possible - safer and automatic

Memory Management Comparison:
- Python: All objects on heap, garbage collector cleans up
- Java: All objects on heap, garbage collector cleans up  
- C++: Choice of stack (automatic) or heap (manual)

Stack vs Heap Decision:
- Use stack when: Object lifetime matches scope, reasonable size
- Use heap when: Object needs to outlive scope, very large, or dynamic size
*/