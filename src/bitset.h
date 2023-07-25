#pragma once

#define BITSET_FMT(bitset)      \
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

typedef int Bitset;

Bitset bitset_insert(Bitset bitset, int value);
Bitset bitset_remove(Bitset bitset, int value);
char bitset_contains(Bitset bitset, int value);
