#include <cstdio>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

void divide(int a, int b) {
    if (b == 0) {
        printf("Error: Cannot divide by zero!\n");
    } else {
        printf("%d / %d = %d\n", a, b, a / b);
    }
}

int main() {
    int x = 10;
    int y = 0;  // Try changing to 2, -5, or 0 to test edge cases

    printf("%d + %d = %d\n", x, y, add(x, y));
    printf("%d - %d = %d\n", x, y, subtract(x, y));
    printf("%d * %d = %d\n", x, y, multiply(x, y));
    divide(x, y);  // This will trigger the edge case if y == 0

    return 0;
}