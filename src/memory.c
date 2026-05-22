#include "memory.h"
#include <stdbool.h>

uint8_t memory_struct_get(Memory *self, uint32_t index) {
  return self->data[index];
}

Memory init_memory() {
  Memory memory = {
  };

  return memory;
}
