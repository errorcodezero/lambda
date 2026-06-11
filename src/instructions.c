#include "instructions.h"
#include "arithmetic_instructions.h"
#include "bitwise_instructions.h"
#include "computer.h"
#include "core_instructions.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

Instructions instruction_from_string(const char *string) {
  #define STR_CMP(name, val) if (strcmp(#name, string) == 0) return val;
  INSTRUCTION_LIST(STR_CMP)
  #undef STR_CMP
  return -1;
}

void setup_instructions(Computer *computer) {
  // add instructions here
  setup_arithmetic_instructions(computer);
  setup_core_instructions(computer);
  setup_bitwise_instructions(computer);
}
