#include "instructions.h"
#include "computer.h"
#include <assert.h>
#include <stdbool.h>
#include "arithmetic_instructions.h"
#include "core_instructions.h"

void setup_instructions(Computer *computer) {
  // add instructions here
  setup_arithmetic_instructions(computer);
  setup_core_instructions(computer);
}
