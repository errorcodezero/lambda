#include "computer.h"
#include "core.h"
#include "instructions.h"
#include <stdio.h>
#include <string.h>

void computer_init(Computer *self) {
  memset(self, 0, sizeof(Computer));
  setup_instructions(self);
}

void computer_start(Computer *self) {
  self->cores[0].instruction_pointer = memory_get_24(self, 0);
  self->cores[0].awake = true;
}

void computer_reset(Computer *self) { memset(self, 0, sizeof(Computer)); }

void computer_step_core(Computer *self, Core *core) {
  if (core->awake)
    self->instructions[memory_get(self, core->instruction_pointer)](self, core);
}

void computer_step(Computer *self) {
  for (uint8_t i = 0; i < COMPUTER_CORES; i++)
    computer_step_core(self, &self->cores[i]);
}

uint8_t memory_get(Computer *self, uint32_t index) {
  return self->memory[index];
}

uint32_t memory_get_24(Computer *self, uint32_t index) {
  return ((uint32_t)self->memory[index]) |
         ((uint32_t)self->memory[index + 1] << 8) |
         ((uint32_t)self->memory[index + 2] << 16);
}

void computer_print(Computer *self) {
  for (uint8_t i = 0; i < COMPUTER_CORES; i++) {
    printf("--- CORE %d ---\n", i);
    core_print(&self->cores[i]);
  }
}
