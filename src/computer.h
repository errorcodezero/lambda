#ifndef INCLUDE_SRC_COMPUTER_H_
#define INCLUDE_SRC_COMPUTER_H_

#include "display.h"

typedef struct Computer {
  void* cores[4];
  Color display[500][300];
} Computer;

#endif  // INCLUDE_SRC_COMPUTER_H_
