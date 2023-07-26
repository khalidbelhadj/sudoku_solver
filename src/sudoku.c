#include "sudoku.h"
#include "bitset.h"

char sudoku_get(Sudoku* state, char row, char col) {
  return state->board[BOARD_INDEX(row, col)];
}

Sudoku * something(Sudoku * state) {
  return state;
}

char sudoku_set(Sudoku* state, char row, char col, char value) {

  sudoku_unset(state, row, col);

  Bitset* row_bitset = &(state->row_contains[row - 1]);
  Bitset* col_bitset = &(state->col_contains[col - 1]);
  Bitset* grid_bitset = &(state->grid_contains[BOARD_GRID_INDEX(row, col)]);

  if (bitset_contains(*row_bitset, (int)value) ||
      bitset_contains(*col_bitset, (int)value) ||
      bitset_contains(*grid_bitset, (int)value)) {
    return 0;
  }

  *row_bitset = bitset_insert(*row_bitset, (int)value);
  *col_bitset = bitset_insert(*col_bitset, (int)value);
  *grid_bitset = bitset_insert(*grid_bitset, (int)value);

  state->board[BOARD_INDEX(row, col)] = value;
  return 1;
}

void sudoku_unset(Sudoku* state, char row, char col) {
  char value = sudoku_get(state, row, col);

  Bitset* row_bitset = &(state->row_contains[row - 1]);
  Bitset* col_bitset = &(state->col_contains[col - 1]);
  Bitset* grid_bitset = &(state->grid_contains[BOARD_GRID_INDEX(row, col)]);

  *row_bitset = bitset_remove(*row_bitset, (int)value);
  *col_bitset = bitset_remove(*col_bitset, (int)value);
  *grid_bitset = bitset_remove(*grid_bitset, (int)value);

  state->board[BOARD_INDEX(row, col)] = 0;
}

void sudoku_next_empty_cell(Sudoku* state, char * row_target, char * col_target) {
  for (char row = 1; row <= 9; ++row) {
    for (char col = 1; col <= 9; ++col) {
      if (sudoku_get(state, row, col) == 0) {
        *row_target = row;
        *col_target = col;
        return;
      }
    }
  }

  *row_target = 0;
  *col_target = 0;
}

char sudoku_solve(Sudoku* state) {
  char row, col;
  sudoku_next_empty_cell(state, &row, &col);

  // No more empty cells
  if (row == 0 && col == 0) {
    return 1;
  }

  Bitset valid_numbers =
    ~(state->row_contains[row - 1] |
      state->col_contains[col - 1] |
      state->grid_contains[BOARD_GRID_INDEX(row, col)]);

  for (char value = 1; value <= 9; ++value) {
    if (!bitset_contains(valid_numbers, value)) {
      continue;
    }

    sudoku_set(state, row, col, value);

    if (sudoku_solve(state)) {
      return 1;
    }

    sudoku_unset(state, row, col);
  }

  return 0;
}

#ifndef WASM

#include <stdio.h>

void sudoku_print_state(Sudoku* state) {
  printf("----------------------\n");
  for (char row = 1; row <= 9; ++row) {
    printf("|");

    for (char col = 1; col <= 9; ++col) {
      char value = sudoku_get(state, row, col);

      if (value == 0) {
        printf("  ");
      } else {
        printf("%zu ", value);
      }

      if (col % 3 == 0) {
        printf("|");
      }
    }

    if (row % 3 == 0) {
      printf("\n----------------------");
    }

    printf("\n");
  }

  printf("row contains:\n");
  for (char i = 0; i < 9; ++i) {
    printf("%zu: "BITSET_TEMPLATE"\n", i + 1, BITSET_FMT(state->row_contains[i]));
  }

  printf("col contains:\n");
  for (char i = 0; i < 9; ++i) {
    printf("%zu: "BITSET_TEMPLATE"\n", i + 1, BITSET_FMT(state->col_contains[i]));
  }

  printf("grid contains:\n");
  for (char i = 0; i < 9; ++i) {
    printf("%zu: "BITSET_TEMPLATE"\n", i + 1, BITSET_FMT(state->grid_contains[i]));
  }

}
#endif /* ifndef WASM */
