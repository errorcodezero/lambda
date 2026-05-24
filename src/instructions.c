#include "instructions.h"
#include "computer.h"
#include "console.h"
#include "core.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "arithmetic_instructions.h"

void setup_instructions(Computer *computer) {
  // add instructions here
  setup_arithmetic_instructions(computer);
  computer->instructions[I_HLT] = HLT_handler;
  computer->instructions[I_LDI] = LDI_handler;
  computer->instructions[I_RLD] = RLD_handler;
}

void HLT_handler(Computer *computer, uint8_t core_id) {
  computer->cores[core_id].awake = false;
  bool computer_awake = false;
  for (uint8_t i = 0; i < COMPUTER_CORES; i++) {
    computer_awake |= computer->cores[i].awake;
  }
  console_print_core(core_id);
  printf("HLT\n");
  if (!computer_awake) {
    printf("%sCOMPUTER STOPPED%s\n", CONSOLE_BLUE, CONSOLE_RESET);
    computer->halted = true;
  }
}

void LDI_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t reg_id = memory_get(computer, core->instruction_pointer + 1);
  uint16_t immediate = memory_get_16(computer, core->instruction_pointer + 2);

  set_register(core, reg_id, immediate);
  console_print_core(core_id);
  printf("LDI REG 0x%X, IMMEDIATE 0x%X\n", reg_id, immediate);
}

void RLD_handler(Computer *computer, uint8_t core_id) {
  (void) computer->cores[core_id];
}
