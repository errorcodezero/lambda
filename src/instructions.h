#ifndef INCLUDE_SRC_INSTRUCTIONS_H_
#define INCLUDE_SRC_INSTRUCTIONS_H_

#include "core.h"
typedef struct Computer Computer;

#define INSTRUCTION_LIST(X)                                                    \
  X(HLT, 0x00)                                                                 \
  X(RET, 0x01)                                                                 \
  X(BNKS, 0x02)                                                                \
  X(INC, 0x10)                                                                 \
  X(DEC, 0x11)                                                                 \
  X(TJMP, 0x12)                                                                \
  X(LSHFT, 0x13)                                                               \
  X(RSHFT, 0x14)                                                               \
  X(ADDR, 0x15)                                                                \
  X(SUBR, 0x16)                                                                \
  X(XORR, 0x17)                                                                \
  X(ANDR, 0x18)                                                                \
  X(NOTR, 0x19)                                                                \
  X(ORR, 0x1A)                                                                 \
  X(NORR, 0x1B)                                                                \
  X(NANDR, 0x1C)                                                               \
  X(XNORR, 0x1D)                                                               \
  X(PSHI, 0x1E)                                                                \
  X(POP, 0x1F)                                                                 \
  X(CMP, 0xA0)                                                                 \
  X(CJIZ, 0xA1)                                                                \
  X(CJIG, 0xA2)                                                                \
  X(CJIL, 0xA3)                                                                \
  X(DMUTI, 0xA4)                                                               \
  X(ADDB, 0x20)                                                                \
  X(SUBB, 0x21)                                                                \
  X(RJMPIZD, 0x22)                                                             \
  X(RJMPIZI, 0x23)                                                             \
  X(RJMPIGD, 0x24)                                                             \
  X(RJMPIGI, 0x25)                                                             \
  X(RJMPILD, 0x26)                                                             \
  X(RJMPILI, 0x27)                                                             \
  X(ADDRR, 0x2A)                                                               \
  X(SUBRR, 0x2B)                                                               \
  X(XANOR, 0x2C)                                                               \
  X(MMUTMOI, 0x2D)                                                             \
  X(MWR, 0x2E)                                                                 \
  X(MIWR, 0x2F)                                                                \
  X(ADDI, 0x30)                                                                \
  X(SUBI, 0x31)                                                                \
  X(LDI, 0x32)                                                                 \
  X(AJMPIZD, 0x33)                                                             \
  X(AJMPIZI, 0x34)                                                             \
  X(AJMPIGD, 0x35)                                                             \
  X(AJMPIGI, 0x36)                                                             \
  X(AJMPILD, 0x37)                                                             \
  X(AJMPILI, 0x38)                                                             \
  X(RLD, 0x39)                                                                 \
  X(RLM, 0x3A)                                                                 \
  X(DMUTAM, 0xC0)                                                              \
  X(ADDINC, 0xC1)                                                              \
  X(SUBINC, 0xC2)                                                              \
  X(ALD, 0x40)                                                                 \
  X(ALM, 0x41)                                                                 \
  X(MMUTMRI, 0x50)                                                             \
  X(MMUTMAI, 0x70)

typedef enum Instructions {
#define ENUM_ENTRY(name, val) I_##name = val,
  INSTRUCTION_LIST(ENUM_ENTRY)
#undef ENUM_ENTRY
} Instructions;

typedef void (*InstructionHandler)(Computer *computer, uint8_t core_id);
void setup_instructions(Computer *computer);
Instructions instruction_from_string(const char *name);

#endif // INCLUDE_SRC_INSTRUCTIONS_H_
