#ifndef INCLUDE_SRC_INSTRUCTIONS_H_
#define INCLUDE_SRC_INSTRUCTIONS_H_

#include "core.h"
typedef struct Computer Computer;

typedef enum Instructions {
  // 1 Byte Instructions
  I_HLT = 0x00,
  I_RET = 0x01,

  // 2 Byte Instructions
  I_INC = 0x10,
  I_DEC = 0x11,
  I_TJMP = 0x12,
  I_LSHFT = 0x13,
  I_RSHFT = 0x14,
  I_ADDR = 0x15,
  I_SUBR = 0x16,
  I_XORR = 0x17,
  I_ANDR = 0x18,
  I_NOTR = 0x19,
  I_ORR = 0x1A,
  I_NORR = 0x1B,
  I_NANDR = 0x1C,
  I_XNORR = 0x1D,
  I_PSHI = 0x1E,
  I_POP = 0x1F,
  I_CMP = 0xA0,
  I_CJIZ = 0xA1,
  I_CJIG = 0xA2,
  I_CJIL = 0xA3,
  I_DMUTI = 0xA4,

  // 3 Byte Instructions
  I_ADDB = 0x20,
  I_SUBB = 0x21,
  I_RJMPIZD = 0x22,
  I_RJMPIZI = 0x23,
  I_RJMPIGD = 0x24,
  I_RJMPIGI = 0x25,
  I_RJMPILD = 0x26,
  I_RJMPILI = 0x27,
  I_ADDRR = 0x2A,
  I_SUBRR = 0x2B,
  I_XANOR = 0x2C,
  I_MMUTMOI = 0x2D,
  I_MWR = 0x2E,
  I_MIWR = 0x2F,

  // 4 Byte Instructions
  I_ADDI = 0x30,
  I_SUBI = 0x31,
  I_LDI = 0x32,
  I_AJMPIZD = 0x33,
  I_AJMPIZI = 0x34,
  I_AJMPIGD = 0x35,
  I_AJMPIGI = 0x36,
  I_AJMPILD = 0x37,
  I_AJMPILI = 0x38,
  I_RLD = 0x39,
  I_RLM = 0x3A,
  I_DMUTAM = 0xC0,
  I_ADDINC = 0xC1,
  I_SUBINC = 0xC2,

  // 5 Byte Instructions
  I_ALD = 0x40,
  I_ALM = 0x41,

  // 6 Byte Instructions
  I_MMUTMRI = 0x50,

  // 8 Byte Instructions
  I_MMUTMAI = 0x70
} Instructions;

typedef void (*InstructionHandler)(Computer *computer, uint8_t core_id);
void setup_instructions(Computer *computer);

#endif // INCLUDE_SRC_INSTRUCTIONS_H_
