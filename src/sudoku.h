#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
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


#define BOARD_INDEX(position) 9 * ((position.row) - 1) + (position.col) - 1
#define BOARD_GRID_INDEX(position) ((position.row - 1) % 3) * 3 + ((position.col - 1) % 3)

#define CELL_FMT(cell) cell.row, cell.col
#define CELL_TEMPLATE "(%zu, %zu)"

typedef struct {
  size_t row;
  size_t col;
} Cell;

Cell sudoku_cell(size_t row, size_t col);

bool sudoku_cell_is_valid(Cell cell);

// Representation of sudoku board
typedef struct {
  size_t* board;
  Bitset row_contains[9];
  Bitset col_contains[9];
  Bitset grid_contains[9];
} Sudoku;

// Returns a new empty Sudoku state
Sudoku* sudoku_new();

// Returns the value of cell `position` in `state`
size_t sudoku_get(Sudoku* state, Cell position);

// Sets the cell `position` to `value` in `state`
void sudoku_set(Sudoku* state, Cell position, size_t value);

void sudoku_unset(Sudoku* state, Cell position);

// Returns the board index of the next empty cell in `state`
Cell sudoku_next_empty_cell(Sudoku* state);

// Returns true if there exists a solution to the `state`. The `state` is mutated.
bool sudoku_solve(Sudoku* state);

// Prints the formatted vertion of `state`
void sudoku_print_state(Sudoku* state);
