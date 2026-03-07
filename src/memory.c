#include "memory.h"
#include <stdbool.h>

struct Memory* init_memory(bool debug) {
  Memory* memory = calloc(1, sizeof(Memory));
  memory->get = memory_struct_get;

  return memory;
}
