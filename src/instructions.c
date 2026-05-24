#include "instructions.h"
#include "computer.h"
#include "core.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void setup_instructions(Computer *computer) {
  // add instructions here
  computer->instructions[I_HLT] = HLT_handler;
  computer->instructions[I_LDI] = LDI_handler;
}

void HLT_handler(Computer *computer, uint8_t core_id) {
  computer->cores[core_id].awake = false;
  bool computer_awake = false;
  for(uint8_t i = 0; i < COMPUTER_CORES; i++) {
	computer_awake |= computer->cores[i].awake;
  }
  printf("CORE %d HALTED\n", core_id);
  if (!computer_awake) {
	printf("COMPUTER STOPPED\n");
	computer->halted = true;
  }
}

void LDI_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t reg_id = memory_get(computer, core->instruction_pointer + 1);
  uint16_t immediate = memory_get_16(computer, core->instruction_pointer + 2);

  set_register(core, reg_id, immediate);
  printf("CORE %d LOADED REG 0x%X WITH DATA 0x%X\n", core_id, reg_id, immediate);
  core->instruction_pointer += 4;
}
