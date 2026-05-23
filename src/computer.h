#ifndef INCLUDE_SRC_COMPUTER_H_
#define INCLUDE_SRC_COMPUTER_H_

#include "core.h"
#include "display.h"
#include "instructions.h"
#include "memory.h"
#include <stdint.h>

#define MEMORY_WIDTH 0xA000000

typedef struct Computer {
  Core cores[4];
  Color display[500][300];
  uint8_t memory[MEMORY_WIDTH];
  InstructionHandler *instructions;
} Computer;

Computer computer_init();
void computer_reset(Computer *self);
void computer_step_core(Computer *self, Core *core);
uint8_t memory_get(Computer *self, uint32_t index);

#endif // INCLUDE_SRC_COMPUTER_H_
