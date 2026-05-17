#ifndef INCLUDE_SRC_COMPUTER_H_
#define INCLUDE_SRC_COMPUTER_H_

#include "core.h"
#include "display.h"
#include <stdint.h>

#define MEMORY

typedef struct Computer {
  Core *cores[4];
  Color display[500][300];
  uint8_t memory[16777217];
} Computer;

void computer_reset(Computer *self);

#endif // INCLUDE_SRC_COMPUTER_H_
