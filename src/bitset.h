#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define BITSET_FMT(bitset)               \
  (bitset_contains(bitset, 1)), \
  (bitset_contains(bitset, 2)), \
  (bitset_contains(bitset, 3)), \
  (bitset_contains(bitset, 4)), \
  (bitset_contains(bitset, 5)), \
  (bitset_contains(bitset, 6)), \
  (bitset_contains(bitset, 7)), \
  (bitset_contains(bitset, 8)), \
  (bitset_contains(bitset, 9))

#define BITSET_TEMPLATE "%d%d%d%d%d%d%d%d%d"

// Set that can store 16 elements
typedef uint16_t Bitset;

Bitset bitset_insert(Bitset bitset, size_t value);
Bitset bitset_remove(Bitset bitset, size_t value);
bool bitset_contains(Bitset bitset, size_t value);
