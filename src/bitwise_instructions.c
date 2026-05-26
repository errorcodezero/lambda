#include "bitwise_instructions.h"
#include "computer.h"
#include "console.h"
#include "core.h"
#include "instructions.h"
#include <stdio.h>

void setup_bitwise_instructions(Computer *computer) {
  computer->instructions[I_XORR] = XORR_handler;
  computer->instructions[I_ANDR] = ANDR_handler;
  computer->instructions[I_NOTR] = NOTR_handler;
  computer->instructions[I_ORR] = ORR_handler;
  computer->instructions[I_NORR] = NORR_handler;
  computer->instructions[I_NANDR] = NANDR_handler;
  computer->instructions[I_XNORR] = XNORR_handler;
  computer->instructions[I_LSHFT] = LSHFT_handler;
  computer->instructions[I_RSHFT] = RSHFT_handler;
  computer->instructions[I_XANOR] = XANOR_handler;
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

  set_register(core, register_id_1, ~core->registers[register_id_2]);

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

  set_register(
      core, register_id_1,
      ~(core->registers[register_id_1] | core->registers[register_id_2]));

  console_print_core(core_id);
  printf("NORR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void NANDR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(
      core, register_id_1,
      ~(core->registers[register_id_1] & core->registers[register_id_2]));

  console_print_core(core_id);
  printf("NANDR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void XNORR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(
      core, register_id_1,
      ~(core->registers[register_id_1] ^ core->registers[register_id_2]));

  console_print_core(core_id);
  printf("XNORR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void LSHFT_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t shift = memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(core, register_id, core->registers[register_id] << shift);
  console_print_core(core_id);
  printf("LSHFT SHIFT 0x%X, REG 0x%X\n", shift, register_id);
}

void RSHFT_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t shift = memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;

  set_register(core, register_id, core->registers[register_id] >> shift);
  console_print_core(core_id);
  printf("RSHFT SHIFT 0x%X, REG 0x%X\n", shift, register_id);
}

void XANOR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t flag = memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 2) >> 4;
  uint8_t register_id_3 =
      memory_get(computer, core->instruction_pointer + 2) & 0x0F;

  uint16_t result;

  switch (flag) {
  case 0: {
    result = core->registers[register_id_2] & core->registers[register_id_3];
    break;
  }
  case 1: {
    result = core->registers[register_id_2] | core->registers[register_id_3];
    break;
  }
  case 2: {
    result = core->registers[register_id_2] ^ core->registers[register_id_3];
    break;
  }
  case 3: {
    result = ~(core->registers[register_id_2] & core->registers[register_id_3]);
    break;
  }
  case 4: {
    result = ~(core->registers[register_id_2] | core->registers[register_id_3]);
    break;
  }
  case 5: {
    result = ~(core->registers[register_id_2] ^ core->registers[register_id_3]);
    break;
  }
  default:
    return;
  }

  set_register(core, register_id_1, result);
  console_print_core(core_id);
  printf("XANOR REG 0x%X, REG 0x%X, REG 0x%X\n", register_id_1, register_id_2,
         register_id_3);
}
