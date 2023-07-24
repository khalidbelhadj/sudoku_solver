#include <stdint.h>
#include "bitset.h"
#include "sudoku.h"

int main() {
  Sudoku* xs = sudoku_new();

   sudoku_print_state(xs);
  printf(sudoku_solve(xs) ? "true" : "false");
  sudoku_print_state(xs);
}
