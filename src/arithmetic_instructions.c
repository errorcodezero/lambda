#include "arithmetic_instructions.h"
#include "computer.h"
#include "console.h"
#include "instructions.h"
#include "stdint.h"
#include <stdio.h>

void setup_arithmetic_instructions(Computer *computer) {
  computer->instructions[I_ADDI] = ADDI_handler;
  computer->instructions[I_SUBI] = SUBI_handler;
  computer->instructions[I_ADDINC] = ADDINC_handler;
  computer->instructions[I_SUBINC] = SUBINC_handler;
  computer->instructions[I_INC] = INC_handler;
  computer->instructions[I_DEC] = DEC_handler;
  computer->instructions[I_ADDR] = ADDR_handler;
  computer->instructions[I_SUBR] = SUBR_handler;
  computer->instructions[I_ADDB] = ADDB_handler;
  computer->instructions[I_SUBB] = SUBB_handler;
}

void ADDI_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t registers = memory_get(computer, core->instruction_pointer + 1);
  uint16_t immediate = memory_get_16(computer, core->instruction_pointer + 2);
  uint16_t operand = core->registers[registers & 0x0F];

  // See if the carry flag is used and if so, add 1 to the result
  uint8_t carry = (core->registers[STATUS_REGISTER] & 0x08) ? 1 : 0;

  uint32_t result = (uint32_t)operand + (uint32_t)immediate + carry;

  // Carry flag
  if (result > 0xFFFF) {
    core->registers[STATUS_REGISTER] |= 0x08;
  } else {
    core->registers[STATUS_REGISTER] &= ~0x08;
  }

  set_register(core, registers >> 4, (uint16_t)result);

  console_print_core(core_id);
  printf("ADDI REG 0x%X, REG 0x%X, IMMEDIATE 0x%X\n", registers >> 4,
         registers & 0x0F, immediate);
}

void SUBI_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t registers = memory_get(computer, core->instruction_pointer + 1);
  uint16_t immediate = memory_get_16(computer, core->instruction_pointer + 2);
  uint16_t operand = core->registers[registers & 0x0F];

  // See if the carry flag is used and if so, subtract 1 from the result
  uint8_t carry = (core->registers[STATUS_REGISTER] & 0x08) ? 1 : 0;

  uint32_t result = (uint32_t)operand - (uint32_t)immediate - carry;

  // Carry flag
  if (result > 0xFFFF) {
    core->registers[STATUS_REGISTER] |= 0x08;
  } else {
    core->registers[STATUS_REGISTER] &= ~0x08;
  }

  set_register(core, registers >> 4, (uint16_t)result);

  console_print_core(core_id);
  printf("SUBI REG 0x%X, REG 0x%X, IMMEDIATE 0x%X\n", registers >> 4,
         registers & 0x0F, immediate);
}

void ADDINC_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t registers = memory_get(computer, core->instruction_pointer + 1);
  uint16_t immediate = memory_get_16(computer, core->instruction_pointer + 2);
  uint16_t operand = core->registers[registers & 0x0F];

  uint32_t result = (uint32_t)operand + (uint32_t)immediate;

  set_register(core, registers >> 4, (uint16_t)result);

  console_print_core(core_id);
  printf("ADDINC REG 0x%X, REG 0x%X, IMMEDIATE 0x%X\n", registers >> 4,
         registers & 0x0F, immediate);
}

void SUBINC_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t registers = memory_get(computer, core->instruction_pointer + 1);
  uint16_t immediate = memory_get_16(computer, core->instruction_pointer + 2);
  uint16_t operand = core->registers[registers & 0x0F];

  uint32_t result = (uint32_t)operand - (uint32_t)immediate;

  set_register(core, registers >> 4, (uint16_t)result);

  console_print_core(core_id);
  printf("SUBINC REG 0x%X, REG 0x%X, IMMEDIATE 0x%X\n", registers >> 4,
         registers & 0x0F, immediate);
}

void INC_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t increment =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
  uint16_t operand = core->registers[register_id];
  uint32_t result = (uint32_t)operand + (uint32_t)increment;

  if (result > 0xFFFF) {
    core->registers[STATUS_REGISTER] |= 0x02;
  } else {
    core->registers[STATUS_REGISTER] &= ~0x02;
  }

  set_register(core, register_id, (uint16_t)result);
  console_print_core(core_id);
  printf("INC REG 0x%X, IMMEDIATE 0x%X\n", register_id, increment);
}

void DEC_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t decrement =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
  uint16_t operand = core->registers[register_id];
  uint32_t result = (uint32_t)operand - (uint32_t)decrement;

  if (result > 0xFFFF) {
    core->registers[STATUS_REGISTER] |= 0x02;
  } else {
    core->registers[STATUS_REGISTER] &= ~0x02;
  }

  set_register(core, register_id, (uint16_t)result);
  console_print_core(core_id);
  printf("DEC REG 0x%X, IMMEDIATE 0x%X\n", register_id, decrement);
}

void ADDR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t registers = memory_get(computer, core->instruction_pointer + 1);

  // See if the carry flag is used and if so, add 1 to the result
  uint8_t carry = (core->registers[STATUS_REGISTER] & 0x08) ? 1 : 0;
  uint32_t result = ((uint32_t)core->registers[registers >> 4]) +
                    ((uint32_t)core->registers[registers & 0x0F]) + carry;

  // Carry flag
  if (result > 0xFFFF) {
    core->registers[STATUS_REGISTER] |= 0x08;
  } else {
    core->registers[STATUS_REGISTER] &= ~0x08;
  }

  set_register(core, registers >> 4, (uint16_t)result);

  console_print_core(core_id);
  printf("ADDR REG 0x%X, REG 0x%X\n", registers >> 4, registers & 0x0F);
}

void SUBR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t registers = memory_get(computer, core->instruction_pointer + 1);

  // See if the carry flag is used and if so, subtract 1 from the result
  uint8_t carry = (core->registers[STATUS_REGISTER] & 0x08) ? 1 : 0;
  uint32_t result = ((uint32_t)core->registers[registers >> 4]) -
                    ((uint32_t)core->registers[registers & 0x0F]) - carry;

  // Carry flag
  if (result > 0xFFFF) {
    core->registers[STATUS_REGISTER] |= 0x08;
  } else {
    core->registers[STATUS_REGISTER] &= ~0x08;
  }

  set_register(core, registers >> 4, (uint16_t)result);

  console_print_core(core_id);
  printf("SUBR REG 0x%X, REG 0x%X\n", registers >> 4, registers & 0x0F);
}

void ADDB_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_immediate = memory_get(computer, core->instruction_pointer + 1);
  uint8_t register_id = register_immediate >> 4;
  uint8_t immediate_high = register_immediate & 0x0F;
  uint8_t immediate_low = memory_get(computer, core->instruction_pointer + 2);
  uint16_t immediate = (immediate_high << 8) | immediate_low;

  // See if the carry flag is used and if so, add 1 to the result
  uint8_t carry = (core->registers[STATUS_REGISTER] & 0x08) ? 1 : 0;

  uint32_t result = (uint32_t)core->registers[register_id] + (uint32_t)immediate + carry;

  // Carry flag
  if (result > 0xFFFF) {
    core->registers[STATUS_REGISTER] |= 0x08;
  } else {
    core->registers[STATUS_REGISTER] &= ~0x08;
  }

  set_register(core, register_id, (uint16_t)result);

  console_print_core(core_id);
  printf("ADDB REG 0x%X, IMMEDIATE 0x%X\n", register_id, immediate);
}

void SUBB_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_immediate = memory_get(computer, core->instruction_pointer + 1);
  uint8_t register_id = register_immediate >> 4;
  uint8_t immediate_high = register_immediate & 0x0F;
  uint8_t immediate_low = memory_get(computer, core->instruction_pointer + 2);
  uint16_t immediate = (immediate_high << 8) | immediate_low;

  // See if the carry flag is used and if so, subtract 1 from the result
  uint8_t carry = (core->registers[STATUS_REGISTER] & 0x08) ? 1 : 0;

  uint32_t result = (uint32_t)core->registers[register_id] - (uint32_t)immediate - carry;

  // Carry flag
  if (result > 0xFFFF) {
    core->registers[STATUS_REGISTER] |= 0x08;
  } else {
    core->registers[STATUS_REGISTER] &= ~0x08;
  }

  set_register(core, register_id, (uint16_t)result);

  console_print_core(core_id);
  printf("SUBB REG 0x%X, IMMEDIATE 0x%X\n", register_id, immediate);
}
