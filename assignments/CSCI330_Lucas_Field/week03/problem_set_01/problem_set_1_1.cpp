// Template provided:
#include <cstdio>

int main() {
  // TODO: Create an integer variable 'score' with value 85
  int score = 85;
  // TODO: Create a reference 'score_ref' that refers to 'score'
  int& score_ref = score;
  // TODO: Print both score and score_ref
  printf("Score: %d\nScore Ref: %d\n", score, score_ref);
  // TODO: Modify score through score_ref to 92
  score_ref = 92;
  // TODO: Print both values again to show they're the same
  printf("New Value of Score: %d\nScore Ref: %d\n", score, score_ref);
  return 0;
}
