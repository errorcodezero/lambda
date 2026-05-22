#ifndef INCLUDE_SRC_MEMORY_H_
#define INCLUDE_SRC_MEMORY_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_WIDTH 16777216
#define MEMORY_MAX_VAL MEMORY_WIDTH
#define MEMORY_MIN_VAL 0

typedef struct Memory Memory;

typedef struct Memory {
  uint8_t data[MEMORY_WIDTH];
} Memory;

Memory init_memory();
uint8_t memory_get(Memory *self, uint32_t index);

#endif // INCLUDE_SRC_MEMORY_H_
