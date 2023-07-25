#include "bitset.h"

Bitset bitset_insert(Bitset bitset, int value) {
  //  assert(0 < value && value <= 16 && "Value out of range, bitset can hold values from 1-15.");
  return (1 << (value - 1)) | bitset;
}

Bitset bitset_remove(Bitset bitset, int value) {
  // assert(0 < value && value <= 16 && "Value out of range, bitset can hold values from 1-15.");
  return (1 << (value - 1)) ^ bitset;
}

char bitset_contains(Bitset bitset, int value) {
  // assert(0 < value && value <= 16 && "Value out of range, bitset can hold values from 1-15.");
  return (bitset >> (value - 1)) & 1;
}
