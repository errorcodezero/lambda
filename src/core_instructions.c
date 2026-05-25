#include "core_instructions.h"
#include "computer.h"
#include "console.h"
#include "core.h"
#include <stdio.h>

void setup_core_instructions(Computer *computer) {
  computer->instructions[I_HLT] = HLT_handler;
  computer->instructions[I_LDI] = LDI_handler;
  computer->instructions[I_RLD] = RLD_handler;
  computer->instructions[I_ALD] = ALD_handler;
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
  uint8_t register_id = memory_get(computer, core->instruction_pointer + 1);
  uint16_t immediate = memory_get_16(computer, core->instruction_pointer + 2);

  set_register(core, register_id, immediate);
  console_print_core(core_id);
  printf("LDI REG 0x%X, IMMEDIATE 0x%X\n", register_id, immediate);
}

void RLD_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
  uint32_t memory_address =
      (((uint32_t)core->registers[BANK_REGISTER]) << 16) +
      memory_get_16(computer, core->instruction_pointer + 2);
  uint32_t original_memory_address = memory_address;
  bool indirection = memory_get(computer, core->instruction_pointer + 1) >> 4;
  if (indirection)
    memory_address = memory_get_24(computer, memory_address);
  set_register(core, register_id, memory_get_16(computer, memory_address));

  console_print_core(core_id);
  printf("RLD %s, REG 0x%X, MEMORY ADDRESS 0x%X\n",
         (indirection ? "WITH INDIRECTION" : "WITHOUT INDIRECTION"),
         register_id, original_memory_address);
}

void ALD_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
  uint32_t memory_address =
      memory_get_24(computer, core->instruction_pointer + 2);
  uint32_t original_memory_address = memory_address;
  bool indirection = memory_get(computer, core->instruction_pointer + 1) >> 4;
  if (indirection)
    memory_address = memory_get_24(computer, memory_address);
  set_register(core, register_id, memory_get_16(computer, memory_address));

  console_print_core(core_id);
  printf("ALD %s, REG 0x%X, MEMORY ADDRESS 0x%X\n",
         (indirection ? "WITH INDIRECTION" : "WITHOUT INDIRECTION"),
         register_id, original_memory_address);
}
