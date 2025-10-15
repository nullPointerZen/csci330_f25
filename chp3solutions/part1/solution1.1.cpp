#include <cstdio>

int main() {
    // Create an integer variable 'score' with value 85
    int score = 85;

    // Create a reference 'score_ref' that refers to 'score'
    int& score_ref = score;

    // Print both score and score_ref
    std::printf("Initial values:\n");
    std::printf("score = %d\n", score);
    std::printf("score_ref = %d\n", score_ref);

    // Modify score through score_ref to 92
    score_ref = 92;

    // Print both values again to show they're the same
    std::printf("\nAfter modifying through reference:\n");
    std::printf("score = %d\n", score);
    std::printf("score_ref = %d\n", score_ref);

    return 0;
}