#ifndef INCLUDE_SRC_COMPUTER_H_
#define INCLUDE_SRC_COMPUTER_H_

#include "core.h"
#include "display.h"

typedef struct Computer {
  Core *cores[4];
  Color display[500][300];
} Computer;

void step_core(Core *core);

#endif // INCLUDE_SRC_COMPUTER_H_
