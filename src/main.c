#include <stdint.h>
#include "bitset.h"
#include "sudoku.h"

#ifndef WASM

int main() {
  Sudoku* state = sudoku_new();

  sudoku_set(state, 1, 3, 8);
  sudoku_set(state, 1, 7, 8);
  sudoku_print_state(state);

  sudoku_solve(&game1);
  sudoku_print_state(&game1);
}

#endif /* ifndef WASM */
