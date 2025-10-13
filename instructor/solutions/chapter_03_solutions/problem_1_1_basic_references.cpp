// Problem 1.1: Reference Fundamentals
// Demonstrates basic reference creation and usage

#include <cstdio>

int main() {
    // Create an integer variable 'score' with value 85
    int score = 85;
    
    // Create a reference 'score_ref' that refers to 'score'
    int& score_ref = score;
    
    // Print both score and score_ref
    printf("Original score: %d, Reference: %d\n", score, score_ref);
    
    // Modify score through score_ref to 92
    score_ref = 92;
    
    // Print both values again to show they're the same
    printf("Modified score: %d, Reference: %d\n", score, score_ref);
    
    // Demonstrate that they share the same memory address
    printf("Address of score: %p\n", &score);
    printf("Address of score_ref: %p\n", &score_ref);
    
    return 0;
}