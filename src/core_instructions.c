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
  computer->instructions[I_TJMP] = TJMP_handler;
  computer->instructions[I_ALM] = ALM_handler;
  computer->instructions[I_RLM] = RLM_handler;
  computer->instructions[I_MWR] = MWR_handler;
  computer->instructions[I_MIWR] = MIWR_handler;
  computer->instructions[I_AJMPIZD] = AJMPIZD_handler;
  computer->instructions[I_AJMPIZI] = AJMPIZI_handler;
  computer->instructions[I_AJMPIGD] = AJMPIGD_handler;
  computer->instructions[I_AJMPIGI] = AJMPIGI_handler;
  computer->instructions[I_AJMPILD] = AJMPILD_handler;
  computer->instructions[I_AJMPILI] = AJMPILI_handler;
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
  uint8_t register_id =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
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

void TJMP_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  int8_t index = memory_get(computer, core->instruction_pointer + 1);

  core->instruction_pointer += index;
  core->jumped = true;

  console_print_core(core_id);
  printf("TJMP 0x%X %s\n", (index >= 0) ? index : (index * -1),
         (index >= 0) ? "FORWARDS" : "BACKWARDS");
}

void ALM_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t flag = memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
  uint32_t memory = memory_get_24(computer, core->instruction_pointer + 2);

  switch (flag) {
  case 0:
    computer->memory[memory] =
        core_register_get_ry(core->registers[register_id]);
    break;
  case 1:
    computer->memory[memory] =
        core_register_get_ry(core->registers[register_id]);
    computer->memory[memory + 1] =
        core_register_get_rx(core->registers[register_id]);
    break;
  case 2: {
    uint32_t indirect = memory_get_24(computer, memory);
    computer->memory[indirect] =
        core_register_get_ry(core->registers[register_id]);
    break;
  }
  case 3: {
    uint32_t indirect = memory_get_24(computer, memory);
    computer->memory[indirect] =
        core_register_get_ry(core->registers[register_id]);
    computer->memory[indirect + 1] =
        core_register_get_rx(core->registers[register_id]);
    break;
  }
  default:
    return;
  }

  console_print_core(core_id);
  printf(
      "ALM %s, %s, REG 0x%X, MEMORY ADDRESS 0x%X\n",
      ((flag == 2 || flag == 3) ? "WITH INDIRECTION" : "WITHOUT INDIRECTION"),
      ((flag == 0 || flag == 2) ? "1 BYTE" : "2 BYTES"), register_id, memory);
}

void RLM_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t flag = memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
  uint32_t memory = memory_get_16(computer, core->instruction_pointer + 2) +
                    ((uint32_t)core->registers[BANK_REGISTER] << 16);

  switch (flag) {
  case 0:
    computer->memory[memory] =
        core_register_get_ry(core->registers[register_id]);
    break;
  case 1:
    computer->memory[memory] =
        core_register_get_ry(core->registers[register_id]);
    computer->memory[memory + 1] =
        core_register_get_rx(core->registers[register_id]);
    break;
  case 2: {
    uint32_t indirect = memory_get_24(computer, memory);
    computer->memory[indirect] =
        core_register_get_ry(core->registers[register_id]);
    break;
  }
  case 3: {
    uint32_t indirect = memory_get_24(computer, memory);
    computer->memory[indirect] =
        core_register_get_ry(core->registers[register_id]);
    computer->memory[indirect + 1] =
        core_register_get_rx(core->registers[register_id]);
    break;
  }
  default:
    return;
  }

  console_print_core(core_id);
  printf(
      "RLM %s, %s, REG 0x%X, MEMORY ADDRESS 0x%X\n",
      ((flag == 2 || flag == 3) ? "WITH INDIRECTION" : "WITHOUT INDIRECTION"),
      ((flag == 0 || flag == 2) ? "1 BYTE" : "2 BYTES"), register_id, memory);
}

void MWR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
  uint32_t memory = (((uint32_t)core->registers[BANK_REGISTER]) << 16) +
                    core->registers[register_id_1];
  computer->memory[memory] =
      core_register_get_ry(core->registers[register_id_2]);
  computer->memory[memory + 1] =
      core_register_get_rx(core->registers[register_id_2]);

  console_print_core(core_id);
  printf("MWR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void MIWR_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t register_id_1 =
      memory_get(computer, core->instruction_pointer + 1) >> 4;
  uint8_t register_id_2 =
      memory_get(computer, core->instruction_pointer + 1) & 0x0F;
  uint32_t memory = (((uint32_t)core->registers[BANK_REGISTER]) << 16) +
                    core->registers[register_id_1];
  uint32_t new_memory = memory_get_24(computer, memory);
  computer->memory[new_memory] =
      core_register_get_ry(core->registers[register_id_2]);
  computer->memory[new_memory + 1] =
      core_register_get_rx(core->registers[register_id_2]);

  console_print_core(core_id);
  printf("MIWR REG 0x%X, REG 0x%X\n", register_id_1, register_id_2);
}

void absolute_jump_helper(Computer *computer, Core *core, uint32_t memory,
                          bool indirection, bool condition) {
  if (!condition)
    return;
  if (indirection)
    memory = memory_get_24(computer, memory);

  core->instruction_pointer = memory;
  core->jumped = true;
}

void AJMPIZD_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t zero_flag = core->registers[STATUS_REGISTER] & ZERO_FLAG;
  uint8_t sign_flag = core->registers[STATUS_REGISTER] & SIGN_FLAG;
  uint32_t memory = memory_get_24(computer, core->instruction_pointer + 1);

  absolute_jump_helper(computer, core, memory, false,
                       (zero_flag && !sign_flag));

  console_print_core(core_id);
  printf("AJMPIZD MEMORY ADDRESS 0x%X\n", memory);
}

void AJMPIZI_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t zero_flag = core->registers[STATUS_REGISTER] & ZERO_FLAG;
  uint8_t sign_flag = core->registers[STATUS_REGISTER] & SIGN_FLAG;
  uint32_t memory = memory_get_24(computer, core->instruction_pointer + 1);

  absolute_jump_helper(computer, core, memory, true, (zero_flag && !sign_flag));

  console_print_core(core_id);
  printf("AJMPIZI MEMORY ADDRESS 0x%X\n", memory);
}

void AJMPIGD_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t zero_flag = core->registers[STATUS_REGISTER] & ZERO_FLAG;
  uint8_t sign_flag = core->registers[STATUS_REGISTER] & SIGN_FLAG;
  uint32_t memory = memory_get_24(computer, core->instruction_pointer + 1);

  absolute_jump_helper(computer, core, memory, false,
                       (!zero_flag && !sign_flag));

  console_print_core(core_id);
  printf("AJMPIGD MEMORY ADDRESS 0x%X\n", memory);
}

void AJMPIGI_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t zero_flag = core->registers[STATUS_REGISTER] & ZERO_FLAG;
  uint8_t sign_flag = core->registers[STATUS_REGISTER] & SIGN_FLAG;
  uint32_t memory = memory_get_24(computer, core->instruction_pointer + 1);

  absolute_jump_helper(computer, core, memory, true,
                       (!zero_flag && !sign_flag));

  console_print_core(core_id);
  printf("AJMPIGI MEMORY ADDRESS 0x%X\n", memory);
}

void AJMPILD_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t zero_flag = core->registers[STATUS_REGISTER] & ZERO_FLAG;
  uint8_t sign_flag = core->registers[STATUS_REGISTER] & SIGN_FLAG;
  uint32_t memory = memory_get_24(computer, core->instruction_pointer + 1);

  absolute_jump_helper(computer, core, memory, false,
                       (!zero_flag && sign_flag));

  console_print_core(core_id);
  printf("AJMPILD MEMORY ADDRESS 0x%X\n", memory);
}

void AJMPILI_handler(Computer *computer, uint8_t core_id) {
  Core *core = &computer->cores[core_id];
  uint8_t zero_flag = core->registers[STATUS_REGISTER] & ZERO_FLAG;
  uint8_t sign_flag = core->registers[STATUS_REGISTER] & SIGN_FLAG;
  uint32_t memory = memory_get_24(computer, core->instruction_pointer + 1);

  absolute_jump_helper(computer, core, memory, true, (!zero_flag && sign_flag));

  console_print_core(core_id);
  printf("AJMPILI MEMORY ADDRESS 0x%X\n", memory);
}
