#ifndef INCLUDE_SRC_COMPUTER_H_
#define INCLUDE_SRC_COMPUTER_H_

#include "core.h"
#include "display.h"
#include "memory.h"
#include <stdint.h>

typedef struct Computer Computer;

typedef void (*InstructionHandler)(Computer *computer);

typedef struct Computer {
  Core cores[4];
  Color display[500][300];
  Memory *memory;
  InstructionHandler instructions[0x100];
} Computer;

Computer computer_init();
void computer_reset(Computer *self);
void computer_step_core(Computer *self, Core *core);

#endif // INCLUDE_SRC_COMPUTER_H_
