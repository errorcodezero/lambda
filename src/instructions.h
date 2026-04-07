#ifndef INCLUDE_SRC_INSTRUCTIONS_H_
#define INCLUDE_SRC_INSTRUCTIONS_H_

typedef enum Instructions {
  // 1 Byte
  I_HLT = 0x00,
  I_RET = 0x01,

  // 2 Byte
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
  I_CMP = 0x60,
  I_CJIZ = 0x61,
  I_CJIG = 0x62,
  I_CJIL = 0x63,

  // 3 Byte
  I_ADDB = 0x20,
  I_SDDB = 0x21,
  I_RJMPIZD = 0x22,
  I_RJMPIZI = 0x23,
  I_RJMPIGD = 0x24,
  I_RJMPIGI = 0x25,
  I_RJMPILD = 0x26,
  I_RJMPIL = 0x27,
  I_ADDRR = 0x2A,
  I_SUBRR = 0x2B,
  I_XANOR = 0x2C,

  // 4 Byte
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

  // 5 Byte
  I_ALD = 0x40,
} Instructions;

#endif // INCLUDE_SRC_INSTRUCTIONS_H_
