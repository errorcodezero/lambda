#include "bitwise_instructions.h"
#include "computer.h"
#include "console.h"
#include "instructions.h"
#include <stdio.h>

void setup_bitwise_instructions(Computer *computer) {
  computer->instructions[I_XORR] = XORR_handler;
  computer->instructions[I_ANDR] = ANDR_handler;
  computer->instructions[I_NOTR] = ANDR_handler;
  computer->instructions[I_ORR] = ANDR_handler;
  computer->instructions[I_NORR] = ANDR_handler;
  computer->instructions[I_NANDR] = ANDR_handler;
  computer->instructions[I_XNORR] = ANDR_handler;
}

void XORR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(core, register_id_1,
               core->registers[register_id_1] ^ core->registers[register_id_2]);

  console_print_core(core_id);
  printf("XORR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void ANDR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(core, register_id_1,
               core->registers[register_id_1] & core->registers[register_id_2]);

  console_print_core(core_id);
  printf("ANDR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void NOTR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(core, register_id_1, !core->registers[register_id_2]);

  console_print_core(core_id);
  printf("NOTR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void ORR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(core, register_id_1,
               core->registers[register_id_1] | core->registers[register_id_2]);

  console_print_core(core_id);
  printf("ORR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void NORR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(core, register_id_1,
               !(core->registers[register_id_1] | core->registers[register_id_2]));

  console_print_core(core_id);
  printf("NORR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void NAND_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(core, register_id_1,
               !(core->registers[register_id_1] & core->registers[register_id_2]));

  console_print_core(core_id);
  printf("NAND REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void XNORR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(core, register_id_1,
               !(core->registers[register_id_1] ^ core->registers[register_id_2]));

  console_print_core(core_id);
  printf("XNORR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}
