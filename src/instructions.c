#include "instructions.h"
#include "computer.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void setup_instructions(Computer *computer) {
  // add instructions here
  computer->instructions[I_HLT] = HLT_handler;
}

void HLT_handler(Computer *computer, uint8_t core_id) {
  computer->cores[core_id].awake = false;
  printf("CORE %d HALTED\n", core_id);
  assert(computer != 0);
}
