#ifndef INCLUDE_SRC_MEMORY_H_
#define INCLUDE_SRC_MEMORY_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MEMORY_WIDTH 16777216
#define MEMORY_MAX_VAL MEMORY_WIDTH - 1
#define MEMORY_MIN_VAL 0

typedef struct Memory Memory;

typedef struct Memory {
  uint8_t data[MEMORY_WIDTH];
  uint8_t (*get)(Memory * self, uint32_t index);
} Memory;

Memory init_memory();
uint8_t memory_struct_get(Memory * self, uint32_t index);

#endif  // INCLUDE_SRC_MEMORY_H_
