#include "instructions.h"
#include "computer.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void setup_instructions(Computer *computer) {
  // add instructions here
  computer->instructions[I_HLT] = HLT_handler;
}

void HLT_handler(Computer *computer, Core *core) {
  core->awake = false;
  printf("CORE HALTED\n");
  assert(computer != 0);
  assert(core != 0);
}
