#ifndef INCLUDE_SRC_COMPUTER_H_
#define INCLUDE_SRC_COMPUTER_H_

#include "core.h"
#include "display.h"
#include "instructions.h"
#include "memory.h"
#include <stdint.h>

typedef struct Computer {
  Core cores[4];
  Color display[500][300];
  Memory *memory;
  InstructionHandler *instructions;
} Computer;

Computer computer_init();
void computer_reset(Computer *self);
void computer_step_core(Computer *self, Core *core);

#endif // INCLUDE_SRC_COMPUTER_H_
