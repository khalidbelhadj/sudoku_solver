#include "sudoku.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"

Cell sudoku_cell(size_t row, size_t col) {
  return (Cell){.row = row, .col = col};
}

bool sudoku_cell_is_valid(Cell cell) {
  return 0 < cell.row && cell.row <= 9 && 0 < cell.col && cell.col <= 9;
}

Sudoku* sudoku_new() {
  Sudoku* state = malloc(sizeof(Sudoku));
  *state = (Sudoku){
      .board = (size_t*)calloc(1, sizeof(size_t) * 9 * 0),
      .row_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0},
      .col_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0},
      .grid_contains = {0, 0, 0, 0, 0, 0, 0, 0, 0},
  };

  return state;
}

size_t sudoku_get(Sudoku* state, Cell position) {
  return state->board[BOARD_INDEX(position)];
}

void sudoku_set(Sudoku* state, Cell position, size_t value) {
  if (0 >= value || value >  9) {
    printf("value invalid: %zu", value);
    exit(EXIT_FAILURE);
  }

  Bitset* row = &(state->row_contains[position.row - 1]);
  Bitset* col = &(state->col_contains[position.col - 1]);
  Bitset* grid = &(state->grid_contains[BOARD_GRID_INDEX(position)]);

  *row = bitset_insert(*row, value);
  *col = bitset_insert(*col, value);
  *grid = bitset_insert(*grid, value);

  state->board[BOARD_INDEX(position)] = value;
}

void sudoku_unset(Sudoku* state, Cell position) {
  size_t value = sudoku_get(state, position);

  Bitset* row = &(state->row_contains[position.row - 1]);
  Bitset* col = &(state->col_contains[position.col - 1]);
  Bitset* grid = &(state->grid_contains[BOARD_GRID_INDEX(position)]);

  *row = bitset_remove(*row, value);
  *col = bitset_remove(*col, value);
  *grid = bitset_remove(*grid, value);

  state->board[BOARD_INDEX(position)] = 0;
}

Cell sudoku_next_empty_cell(Sudoku* state) {
  for (size_t row = 1; row <= 9; ++row) {
    for (size_t col = 1; col <= 9; ++col) {
      Cell cell = sudoku_cell(row, col);

      if (sudoku_get(state, cell) == 0) {
        return sudoku_cell(row, col);
      }
    }
  }

  return sudoku_cell(0, 0);
}

bool sudoku_solve(Sudoku* state) {
  Cell next_empty_cell = sudoku_next_empty_cell(state);

  // No more empty cells
  if (!sudoku_cell_is_valid(next_empty_cell)) {
    return true;
  }

  size_t row = next_empty_cell.row;
  size_t col = next_empty_cell.col;

  Bitset valid_numbers =
    ~(state->row_contains[row - 1] |
      state->col_contains[col - 1] |
      state->grid_contains[BOARD_GRID_INDEX(next_empty_cell)]);

  for (size_t value = 1; value <= 9; ++value) {
    if (!bitset_contains(valid_numbers, value)) {
      continue;
    }

    sudoku_set(state, next_empty_cell, value);

    if (sudoku_solve(state)) {
      return true;
    }

    sudoku_unset(state, next_empty_cell);
  }

  return false;
}

void sudoku_print_state(Sudoku* state) {
  printf("----------------------\n");
  for (size_t row = 1; row <= 9; ++row) {
    printf("|");

    for (size_t col = 1; col <= 9; ++col) {
      size_t value = sudoku_get(state, sudoku_cell(row, col));

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
  for (size_t i = 0; i < 9; ++i) {
    printf("%zu: "BITSET_TEMPLATE"\n", i + 1, BITSET_FMT(state->row_contains[i]));
  }

  printf("col contains:\n");
  for (size_t i = 0; i < 9; ++i) {
    printf("%zu: "BITSET_TEMPLATE"\n", i + 1, BITSET_FMT(state->col_contains[i]));
  }

  printf("grid contains:\n");
  for (size_t i = 0; i < 9; ++i) {
    printf("%zu: "BITSET_TEMPLATE"\n", i + 1, BITSET_FMT(state->grid_contains[i]));
  }

}
