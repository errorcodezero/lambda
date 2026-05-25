#include "instructions.h"
#include "arithmetic_instructions.h"
#include "bitwise_instructions.h"
#include "computer.h"
#include "core_instructions.h"
#include <assert.h>
#include <stdbool.h>

void setup_instructions(Computer *computer) {
  // add instructions here
  setup_arithmetic_instructions(computer);
  setup_core_instructions(computer);
  setup_bitwise_instructions(computer);
}
