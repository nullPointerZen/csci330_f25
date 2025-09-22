#include <cstdio>
int square(int x) {
    return x * x;
}

int main() {
    int num = 5;
    int result = square(num);
    printf("%d squared is %d\n", num, result);
    return 0;
}