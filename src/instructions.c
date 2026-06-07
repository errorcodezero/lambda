#include "instructions.h"
#include "arithmetic_instructions.h"
#include "bitwise_instructions.h"
#include "computer.h"
#include "core_instructions.h"
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  const char *name;
  Instructions opcode;
} InstructionMap;

static const InstructionMap instruction_map[] = {
  {"HLT", I_HLT},
  {"RET", I_RET},
  {"INC", I_INC},
  {"DEC", I_DEC},
  {"TJMP", I_TJMP},
  {"LSHFT", I_LSHFT},
  {"RSHFT", I_RSHFT},
  {"ADDR", I_ADDR},
  {"SUBR", I_SUBR},
  {"XORR", I_XORR},
  {"ANDR", I_ANDR},
  {"NOTR", I_NOTR},
  {"ORR", I_ORR},
  {"NORR", I_NORR},
  {"NANDR", I_NANDR},
  {"XNORR", I_XNORR},
  {"PSHI", I_PSHI},
  {"POP", I_POP},
  {"CMP", I_CMP},
  {"CJIZ", I_CJIZ},
  {"CJIG", I_CJIG},
  {"CJIL", I_CJIL},
  {"DMUTI", I_DMUTI},
  {"ADDB", I_ADDB},
  {"SUBB", I_SUBB},
  {"RJMPIZD", I_RJMPIZD},
  {"RJMPIZI", I_RJMPIZI},
  {"RJMPIGD", I_RJMPIGD},
  {"RJMPIGI", I_RJMPIGI},
  {"RJMPILD", I_RJMPILD},
  {"RJMPILI", I_RJMPILI},
  {"ADDRR", I_ADDRR},
  {"SUBRR", I_SUBRR},
  {"XANOR", I_XANOR},
  {"MMUTMOI", I_MMUTMOI},
  {"MWR", I_MWR},
  {"MIWR", I_MIWR},
  {"ADDI", I_ADDI},
  {"SUBI", I_SUBI},
  {"LDI", I_LDI},
  {"AJMPIZD", I_AJMPIZD},
  {"AJMPIZI", I_AJMPIZI},
  {"AJMPIGD", I_AJMPIGD},
  {"AJMPIGI", I_AJMPIGI},
  {"AJMPILD", I_AJMPILD},
  {"AJMPILI", I_AJMPILI},
  {"RLD", I_RLD},
  {"RLM", I_RLM},
  {"DMUTAM", I_DMUTAM},
  {"ADDINC", I_ADDINC},
  {"SUBINC", I_SUBINC},
  {"ALD", I_ALD},
  {"ALM", I_ALM},
  {"MMUTMRI", I_MMUTMRI},
  {"MMUTMAI", I_MMUTMAI},
};

Instructions instruction_from_string(const char *name) {
  for (size_t i = 0; i < sizeof(instruction_map) / sizeof(instruction_map[0]); i++) {
    if (strcmp(instruction_map[i].name, name) == 0) {
      return instruction_map[i].opcode;
    }
  }
  return -1;
}

void setup_instructions(Computer *computer) {
  // add instructions here
  setup_arithmetic_instructions(computer);
  setup_core_instructions(computer);
  setup_bitwise_instructions(computer);
}
