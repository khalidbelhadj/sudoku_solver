#pragma once

#include "bitset.h"

//       1  2  3   4  5  6   7  8  9
//      |--|--|--||--|--|--||--|--|--|
//  1   |  |  |  ||  |  |  ||  |  |  |
//  2   |  |1 |  ||  |2 |  ||  |3 |  |
//  3   |  |  |  ||  |  |  ||  |  |  |
//      |--|--|--||--|--|--||--|--|--|
//  4   |  |  |  ||  |  |  ||  |  |  |
//  5   |  |4 |  ||  |5 |  ||  |6 |  |
//  6   |  |  |  ||  |  |  ||  |  |  |
//      |--|--|--||--|--|--||--|--|--|
//  7   |  |  |  ||  |  |  ||  |  |  |
//  8   |  |7 |  ||  |8 |  ||  |9 |  |
//  9   |  |  |  ||  |  |  ||  |  |  |
//      |--|--|--||--|--|--||--|--|--|
//

#define WASM
#define BOARD_INDEX(row, col) 9 * ((row)-1) + (col)-1
#define BOARD_GRID_INDEX(row, col) ((row - 1) / 3) * 3 + ((col - 1) / 3)

#define CELL_FMT(cell) cell.row, cell.col
#define CELL_TEMPLATE "(%zu, %zu)"

// Representation of sudoku board
typedef struct {
  char* board;
  Bitset row_contains[9];
  Bitset col_contains[9];
  Bitset grid_contains[9];
} Sudoku;

// Returns the value of cell `position` in `state`
char sudoku_get(Sudoku* state, char row, char col);

Sudoku* something(Sudoku* state);

// Sets the cell `position` to `value` in `state`
char sudoku_set(Sudoku* state, char row, char col, char value);

void sudoku_unset(Sudoku* state, char row, char col);

// Returns the board index of the next empty cell in `state`
void sudoku_next_empty_cell(Sudoku* state, char* row_target, char* col_target);

// Returns true if there exists a solution to the `state`. The `state` is
// mutated.
char sudoku_solve(Sudoku* state);

// Prints the formatted vertion of `state`
#ifndef WASM
void sudoku_print_state(Sudoku* state);
#endif  // !WASM
