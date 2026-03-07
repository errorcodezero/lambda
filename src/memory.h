#ifndef INCLUDE_SRC_MEMORY_H_
#define INCLUDE_SRC_MEMORY_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MEMORY_WIDTH 2^24
#define MEMORY_MAX_VAL MEMORY_WIDTH - 1
#define MEMORY_MIN_VAL 0

typedef struct Memory {
  uint8_t data[MEMORY_WIDTH];
  uint8_t (*get)(struct Memory * self);
} Memory;

struct Memory * init_memory(bool debug);
uint8_t memory_struct_get(struct Memory * self);

#endif  // INCLUDE_SRC_MEMORY_H_
