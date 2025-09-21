1. Problem Set 1-1
```cpp
// Template provided:
#include <cstdio>

int main() {
    // TODO: Create an integer variable 'score' with value 85
    int score = 85;
    // TODO: Create a reference 'score_ref' that refers to 'score'
    int& score_ref = score;
    // TODO: Print both score and score_ref
    printf("Score: %d\n Score Ref: %d", score, score_ref);
    // TODO: Modify score through score_ref to 92
    score_ref = 92;
    // TODO: Print both values again to show they're the same
    printf("New Value of Score: %d\n Score Ref: %d\n", score, score_ref);
    return 0;
}
```
Output:
```output
student@cpp-dev:~/workspace$ ./problem_set_1_1
Score: 85
 Score Ref: 85New Value of Score: 92
 Score Ref: 92
 ```
Works as expected, going to reformat to make look neater.
Fixed output:
```output
student@cpp-dev:~/workspace$ ./problem_set_1_1
Score: 85
Score Ref: 85
New Value of Score: 92
Score Ref: 92
```
2. Problem Set 1-2:
```cpp
// Template provided:
#include <cstdio>

int main() {
    int original = 100;

    // TODO: Create a copy of original called 'copy_val'
    int copy_val = original;
    // TODO: Create a reference to original called 'ref_val'
    int& ref_val = orignal;
    // TODO: Modify original to 200
    original = 200;
    // TODO: Print all three values to show the difference
    printf("Original Value: %d\nCopied Value: %d\nReference Value: %d\n", original, copy_val, ref_val)
    return 0;
}
```
Compiler issues:
```
problem_set_1_2.cpp: In function 'int main()':
problem_set_1_2.cpp:10:20: error: 'orignal' was not declared in this scope; did you mean 'original'?
   10 |     int* ref_val = orignal;
      |                    ^~~~~~~
      |                    original
problem_set_1_2.cpp:14:69: warning: format '%d' expects argument of type 'int', but argument 4 has type 'int*' [-Wformat=]
   14 |     printf("Original Value: %d\nCopied Value: %d\nReference Value: %d\n", original, copy_val, ref_val)
      |                                                                    ~^                         ~~~~~~~
      |                                                                     |                         |
      |                                                                     int                       int*
      |                                                                    %n
problem_set_1_2.cpp:14:103: error: expected ';' before 'return'
   14 |     printf("Original Value: %d\nCopied Value: %d\nReference Value: %d\n", original, copy_val, ref_val)
      |                                                                                                       ^
      |                                                                                                       ;
   15 |     return 0;
      |     ~~~~~~                                                                              \
```
Simple spelling error with original, fixed.
```
problem_set_1_2.cpp:10:20: error: 'orignal' was not declared in this scope; did you mean 'original'?
   10 |     int* ref_val = orignal;
      |                    ^~~~~~~
      |
```
Forgot colon after print
```
   14 |     printf("Original Value: %d\nCopied Value: %d\nReference Value: %d\n", original, copy_val, ref_val)
      |                                                                                                       ^
      |                                                                                                       ;
   15 |     return 0;
      |     ~
```
Output:
```output
student@cpp-dev:~/workspace$ ./problem_set_1_2
Original Value: 200
Copied Value: 100
Reference Value: 200
```
