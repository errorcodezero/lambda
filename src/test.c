#include "test.h"
#include "console.h"
#include <stdlib.h>
#include <stdio.h>

void test(Computer *computer) {
  uint32_t program_addr = 0x010000;
  uint32_t memory_data_addr = 0x002000;
  uint32_t write_addr = program_addr;

  computer->memory[0] = (uint8_t)(program_addr & 0xFF);
  computer->memory[1] = (uint8_t)((program_addr >> 8) & 0xFF);
  computer->memory[2] = (uint8_t)((program_addr >> 16) & 0xFF);

  computer->memory[write_addr++] = 0x32; // LDI R0, 0x1234
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x34;
  computer->memory[write_addr++] = 0x12;

  computer->memory[write_addr++] = 0xC1; // ADDINC R0, R0, 0x0001
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0xC2; // SUBINC R0, R0, 0x0001
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x30; // ADDI R0, R0, 0x0001
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x31; // SUBI R0, R0, 0x0001
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x39; // RLD R1, [bank:0x2000]
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x20;

  computer->memory[write_addr++] = 0x10; // INC R1, 1
  computer->memory[write_addr++] = 0x11;

  computer->memory[write_addr++] = 0x11; // DEC R1, 1
  computer->memory[write_addr++] = 0x11;

  computer->memory[write_addr++] = 0x32; // LDI R2, 0x0F0F
  computer->memory[write_addr++] = 0x02;
  computer->memory[write_addr++] = 0x0F;
  computer->memory[write_addr++] = 0x0F;

  computer->memory[write_addr++] = 0x32; // LDI R3, 0x00FF
  computer->memory[write_addr++] = 0x03;
  computer->memory[write_addr++] = 0xFF;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x32; // LDI R5, 0x0F0F
  computer->memory[write_addr++] = 0x05;
  computer->memory[write_addr++] = 0x0F;
  computer->memory[write_addr++] = 0x0F;

  computer->memory[write_addr++] = 0x32; // LDI R6, 0x0F0F
  computer->memory[write_addr++] = 0x06;
  computer->memory[write_addr++] = 0x0F;
  computer->memory[write_addr++] = 0x0F;

  computer->memory[write_addr++] = 0x32; // LDI R7, 0x0F0F
  computer->memory[write_addr++] = 0x07;
  computer->memory[write_addr++] = 0x0F;
  computer->memory[write_addr++] = 0x0F;

  computer->memory[write_addr++] = 0x32; // LDI R8, 0x1234
  computer->memory[write_addr++] = 0x08;
  computer->memory[write_addr++] = 0x34;
  computer->memory[write_addr++] = 0x12;

  computer->memory[write_addr++] = 0x32; // LDI R9, 0x0101
  computer->memory[write_addr++] = 0x09;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x01;

  computer->memory[write_addr++] = 0x32; // LDI R10, 0x2222
  computer->memory[write_addr++] = 0x0A;
  computer->memory[write_addr++] = 0x22;
  computer->memory[write_addr++] = 0x22;

  computer->memory[write_addr++] = 0x32; // LDI R11, 0x4000
  computer->memory[write_addr++] = 0x0B;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x40;

  computer->memory[write_addr++] = 0x12; // TJMP +4 (skip INC)
  computer->memory[write_addr++] = 0x04;

  computer->memory[write_addr++] = 0x10; // INC R10, 1 (skipped by TJMP)
  computer->memory[write_addr++] = 0xA1;

  computer->memory[write_addr++] = 0x20; // ADDB R10, 0x0100
  computer->memory[write_addr++] = 0xA1;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x21; // SUBB R11, 0x1000
  computer->memory[write_addr++] = 0xB1;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x32; // LDI R12, 0x0001
  computer->memory[write_addr++] = 0x0C;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x32; // LDI R13, 0x0002
  computer->memory[write_addr++] = 0x0D;
  computer->memory[write_addr++] = 0x02;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] =
      0x2A; // ADDRR R12, R12, R13 (flag=0, no carry)
  computer->memory[write_addr++] = 0x0C;
  computer->memory[write_addr++] = 0xCD;

  computer->memory[write_addr++] =
      0x2B; // SUBRR R13, R12, R13 (flag=0, no borrow)
  computer->memory[write_addr++] = 0x0D;
  computer->memory[write_addr++] = 0xCD;

  computer->memory[write_addr++] = 0x15; // ADDR R8, R9
  computer->memory[write_addr++] = 0x89;

  computer->memory[write_addr++] = 0x16; // SUBR R8, R9
  computer->memory[write_addr++] = 0x89;

  computer->memory[write_addr++] = 0x17; // XORR R2, R3
  computer->memory[write_addr++] = 0x23;

  computer->memory[write_addr++] = 0x18; // ANDR R2, R3
  computer->memory[write_addr++] = 0x23;

  computer->memory[write_addr++] = 0x1A; // ORR R2, R3
  computer->memory[write_addr++] = 0x23;

  computer->memory[write_addr++] = 0x19; // NOTR R4, R3
  computer->memory[write_addr++] = 0x43;

  computer->memory[write_addr++] = 0x1B; // NORR R5, R3
  computer->memory[write_addr++] = 0x53;

  computer->memory[write_addr++] = 0x1C; // NANDR R6, R3
  computer->memory[write_addr++] = 0x63;

  computer->memory[write_addr++] = 0x1D; // XNORR R7, R3
  computer->memory[write_addr++] = 0x73;

  computer->memory[write_addr++] = 0x13; // LSHFT R3, 4
  computer->memory[write_addr++] = 0x43;

  computer->memory[write_addr++] = 0x14; // RSHFT R3, 2
  computer->memory[write_addr++] = 0x23;

  computer->memory[write_addr++] =
      0x3A; // RLM MODE 0, R0, offset 0x3100 (1 byte, no indirection)
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x31;

  computer->memory[write_addr++] =
      0x3A; // RLM MODE 1, R1, offset 0x3101 (2 bytes, no indirection)
  computer->memory[write_addr++] = 0x11;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x31;

  computer->memory[write_addr++] =
      0x3A; // RLM MODE 2, R0, offset 0x3104 (1 byte, with indirection)
  computer->memory[write_addr++] = 0x20;
  computer->memory[write_addr++] = 0x04;
  computer->memory[write_addr++] = 0x31;

  computer->memory[write_addr++] =
      0x3A; // RLM MODE 3, R1, offset 0x3107 (2 bytes, with indirection)
  computer->memory[write_addr++] = 0x31;
  computer->memory[write_addr++] = 0x07;
  computer->memory[write_addr++] = 0x31;

  computer->memory[write_addr++] =
      0x2E; // MWR R0, R2 (stores R2 to mem[BANK:reg[R0]])
  computer->memory[write_addr++] = 0x02;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] =
      0x2F; // MIWR R3, R2 (stores R2 via indirect through mem[BANK:reg[R3]])
  computer->memory[write_addr++] = 0x32;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x32; // LDI R14, 0xAABB
  computer->memory[write_addr++] = 0x0E;
  computer->memory[write_addr++] = 0xBB;
  computer->memory[write_addr++] = 0xAA;

  computer->memory[write_addr++] =
      0x41; // ALM MODE 0, R14, 0x002100 (1 byte, no indirection)
  computer->memory[write_addr++] = 0x0E;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x21;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] =
      0x41; // ALM MODE 1, R14, 0x002101 (2 bytes, no indirection)
  computer->memory[write_addr++] = 0x1E;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x21;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] =
      0x41; // ALM MODE 2, R14, 0x002200 (1 byte, with indirection)
  computer->memory[write_addr++] = 0x2E;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x22;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] =
      0x41; // ALM MODE 3, R14, 0x002203 (2 bytes, with indirection)
  computer->memory[write_addr++] = 0x3E;
  computer->memory[write_addr++] = 0x03;
  computer->memory[write_addr++] = 0x22;
  computer->memory[write_addr++] = 0x00;

  // AJMPIZD: condition FALSE (Z=0) -> fall through
  computer->memory[write_addr++] = 0x33; // AJMPIZD
  computer->memory[write_addr++] = 0x00; // target = 0x300000
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x30;

  // AJMPIGD: condition TRUE (Z=0, S=0) -> jump to uninit memory -> HLT
  computer->memory[write_addr++] = 0x35; // AJMPIGD
  computer->memory[write_addr++] = 0x00; // target = 0x300100
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x30;

  computer->memory[write_addr++] = 0x00; // HLT (consumed by auto-increment)

  computer->memory[memory_data_addr] = 0xCD;
  computer->memory[memory_data_addr + 1] = 0xAB;

  // Indirection pointer for ALM MODE 2 -> 0x003000
  computer->memory[0x002200] = 0x00;
  computer->memory[0x002201] = 0x30;
  computer->memory[0x002202] = 0x00;

  // Indirection pointer for ALM MODE 3 -> 0x003002
  computer->memory[0x002203] = 0x02;
  computer->memory[0x002204] = 0x30;
  computer->memory[0x002205] = 0x00;

  // Indirection pointer for RLM MODE 2 -> 0x003200
  computer->memory[0x003104] = 0x00;
  computer->memory[0x003105] = 0x32;
  computer->memory[0x003106] = 0x00;

  // Indirection pointer for RLM MODE 3 -> 0x003202
  computer->memory[0x003107] = 0x02;
  computer->memory[0x003108] = 0x32;
  computer->memory[0x003109] = 0x00;

  // Indirection pointer for MIWR (R3=0x03FC) -> 0x003300
  computer->memory[0x0003FC] = 0x00;
  computer->memory[0x0003FD] = 0x33;
  computer->memory[0x0003FE] = 0x00;

  computer_start(computer);
  while (!computer->halted) {
    computer_step(computer);
    if (getenv("DEBUG") != NULL) {
      computer_print(computer);
    }
  }

  if (computer->cores[0].registers[0] != 0x1234 ||
      computer->cores[0].registers[1] != 0xABCD ||
      computer->cores[0].registers[2] != 0x00FF ||
      computer->cores[0].registers[3] != 0x03FC ||
      computer->cores[0].registers[4] != 0xFF00 ||
      computer->cores[0].registers[5] != 0xF000 ||
      computer->cores[0].registers[6] != 0xFFF0 ||
      computer->cores[0].registers[7] != 0xF00F ||
      computer->cores[0].registers[8] != 0x1234 ||
      computer->cores[0].registers[9] != 0x0101 ||
      computer->cores[0].registers[10] != 0x2322 ||
      computer->cores[0].registers[11] != 0x3F00 ||
      computer->cores[0].registers[12] != 0x0003 ||
      computer->cores[0].registers[13] != 0x0001 ||
      computer->cores[0].registers[14] != 0x00BB ||
      computer->memory[0x002100] != 0xBB ||
      computer->memory[0x002101] != 0xBB ||
      computer->memory[0x002102] != 0x00 ||
      computer->memory[0x003000] != 0xBB ||
      computer->memory[0x003002] != 0xBB ||
      computer->memory[0x003003] != 0x00 ||
      computer->memory[0x003100] != 0x34 ||
      computer->memory[0x003101] != 0xCD ||
      computer->memory[0x003102] != 0xAB ||
      computer->memory[0x003200] != 0x34 ||
      computer->memory[0x003202] != 0xCD ||
      computer->memory[0x003203] != 0xAB ||
      computer->memory[0x001234] != 0xFF ||
      computer->memory[0x001235] != 0x00 ||
      computer->memory[0x003300] != 0xFF ||
      computer->memory[0x003301] != 0x00) {
    fprintf(
        stderr,
        "%sTest failed: R0=0x%X R1=0x%X R2=0x%X R3=0x%X R4=0x%X R5=0x%X "
        "R6=0x%X R7=0x%X R8=0x%X R9=0x%X R10=0x%X R11=0x%X R12=0x%X R13=0x%X "
        "R14=0x%X MEM[0x2100]=0x%X MEM[0x2101]=0x%X MEM[0x2102]=0x%X "
        "MEM[0x3000]=0x%X MEM[0x3002]=0x%X MEM[0x3003]=0x%X "
        "MEM[0x3100]=0x%X MEM[0x3101]=0x%X MEM[0x3102]=0x%X "
        "MEM[0x3200]=0x%X MEM[0x3202]=0x%X MEM[0x3203]=0x%X "
        "MEM[0x1234]=0x%X MEM[0x1235]=0x%X "
        "MEM[0x3300]=0x%X MEM[0x3301]=0x%X\n%s",
        CONSOLE_RED, computer->cores[0].registers[0],
        computer->cores[0].registers[1], computer->cores[0].registers[2],
        computer->cores[0].registers[3], computer->cores[0].registers[4],
        computer->cores[0].registers[5], computer->cores[0].registers[6],
        computer->cores[0].registers[7], computer->cores[0].registers[8],
        computer->cores[0].registers[9], computer->cores[0].registers[10],
        computer->cores[0].registers[11], computer->cores[0].registers[12],
        computer->cores[0].registers[13], computer->cores[0].registers[14],
        computer->memory[0x002100], computer->memory[0x002101],
        computer->memory[0x002102], computer->memory[0x003000],
        computer->memory[0x003002], computer->memory[0x003003],
        computer->memory[0x003100], computer->memory[0x003101],
        computer->memory[0x003102], computer->memory[0x003200],
        computer->memory[0x003202], computer->memory[0x003203],
        computer->memory[0x001234], computer->memory[0x001235],
        computer->memory[0x003300], computer->memory[0x003301], CONSOLE_RESET);
  }
  printf("%sTests passed%s\n", CONSOLE_GREEN, CONSOLE_RESET);
}
