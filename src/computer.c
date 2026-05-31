#include "computer.h"
#include "console.h"
#include "core.h"
#include "instructions.h"
#include <stdio.h>
#include <string.h>

void computer_init(Computer *self) {
  memset(self, 0, sizeof(Computer));
  setup_instructions(self);
}

void computer_start(Computer *self) {
  printf("%sCOMPUTER START%s\n", CONSOLE_BLUE, CONSOLE_RESET);
  self->cores[0].instruction_pointer = memory_get_24(self, 0);
  console_print_core(0, self->cores[0].instruction_pointer);
  printf("INSTRUCTION VECTOR 0x%X\n", memory_get_24(self, 0));
  self->cores[0].awake = true;
  console_print_core(0, self->cores[0].instruction_pointer);
  printf("START\n");
}

void computer_reset(Computer *self) { memset(self, 0, sizeof(Computer)); }

void computer_step_core(Computer *self, uint8_t core_id) {
  if (self->cores[core_id].awake) {
    self->cores[core_id].registers[STATUS_REGISTER] &= 0x00FF;
    self->cores[core_id].registers[BANK_REGISTER] &= 0x00FF;
    self->cores[core_id].registers[ZERO_REGISTER] = 0;
    // Auto incrementation of the instruction pointer works since the length of
    // an instruction is encoded within the first nibble.
    self->instructions[memory_get(
        self, self->cores[core_id].instruction_pointer)](self, core_id);
    if (!self->cores[core_id].jumped)
      self->cores[core_id].instruction_pointer +=
          (((self->memory[self->cores[core_id].instruction_pointer] >> 4) % 9) +
           1);
    else
      self->cores[core_id].jumped = false;
  }
}

void computer_step(Computer *self) {
  if (!self->halted)
    for (uint8_t i = 0; i < COMPUTER_CORES; i++)
      computer_step_core(self, i);
}

uint8_t memory_get(Computer *self, uint32_t index) {
  return self->memory[index];
}

uint16_t memory_get_16(Computer *self, uint32_t index) {
  return ((uint16_t)self->memory[index]) |
         ((uint16_t)self->memory[index + 1] << 8);
}

uint32_t memory_get_24(Computer *self, uint32_t index) {
  return ((uint32_t)self->memory[index]) |
         ((uint32_t)self->memory[index + 1] << 8) |
         ((uint32_t)self->memory[index + 2] << 16);
}

uint32_t memory_get_32(Computer *self, uint32_t index) {
  return ((uint32_t)self->memory[index]) |
         ((uint32_t)self->memory[index + 1] << 8) |
         ((uint32_t)self->memory[index + 2] << 16) |
         ((uint32_t)self->memory[index + 3] << 24);
}

void computer_print(Computer *self) {
  for (uint8_t i = 0; i < COMPUTER_CORES; i++) {
    printf("--- ");
    console_print_core(i, self->cores[i].instruction_pointer);
    printf("---\n");
    core_print(&self->cores[i]);
  }
}
