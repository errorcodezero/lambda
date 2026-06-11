#include "test.h"
#include "console.h"
#include <stdlib.h>
#include <stdio.h>

void test(Computer *computer) {
  uint32_t program_addr = 0x010000;
  uint32_t memory_data_addr = 0x020000;
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

  computer->memory[write_addr++] = 0x32; // LDI R14, 0x0002 (set bank=2)
  computer->memory[write_addr++] = 0x0E;
  computer->memory[write_addr++] = 0x02;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x39; // RLD R1, [bank:0x0000]
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x00;

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
      0x3A; // RLM MODE 0, R0, offset 0x1400 (1 byte, no indirection)
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x14;

  computer->memory[write_addr++] =
      0x3A; // RLM MODE 1, R1, offset 0x1401 (2 bytes, no indirection)
  computer->memory[write_addr++] = 0x11;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x14;

  computer->memory[write_addr++] =
      0x3A; // RLM MODE 2, R0, offset 0x1404 (1 byte, with indirection)
  computer->memory[write_addr++] = 0x20;
  computer->memory[write_addr++] = 0x04;
  computer->memory[write_addr++] = 0x14;

  computer->memory[write_addr++] =
      0x3A; // RLM MODE 3, R1, offset 0x1407 (2 bytes, with indirection)
  computer->memory[write_addr++] = 0x31;
  computer->memory[write_addr++] = 0x07;
  computer->memory[write_addr++] = 0x14;

  computer->memory[write_addr++] =
      0x2E; // MWR R4, R2 (stores R2 to mem[BANK:reg[R4]])
  computer->memory[write_addr++] = 0x42;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] =
      0x2F; // MIWR R12, R2 (stores R2 via indirect through mem[BANK:reg[R12]])
  computer->memory[write_addr++] = 0xC2;
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x32; // LDI R14, 0xAABB
  computer->memory[write_addr++] = 0x0E;
  computer->memory[write_addr++] = 0xBB;
  computer->memory[write_addr++] = 0xAA;

  computer->memory[write_addr++] =
      0x41; // ALM MODE 0, R14, 0x021000 (1 byte, no indirection)
  computer->memory[write_addr++] = 0x0E;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x10;
  computer->memory[write_addr++] = 0x02;

  computer->memory[write_addr++] =
      0x41; // ALM MODE 1, R14, 0x021001 (2 bytes, no indirection)
  computer->memory[write_addr++] = 0x1E;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x10;
  computer->memory[write_addr++] = 0x02;

  computer->memory[write_addr++] =
      0x41; // ALM MODE 2, R14, 0x021200 (1 byte, with indirection)
  computer->memory[write_addr++] = 0x2E;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x12;
  computer->memory[write_addr++] = 0x02;

  computer->memory[write_addr++] =
      0x41; // ALM MODE 3, R14, 0x021203 (2 bytes, with indirection)
  computer->memory[write_addr++] = 0x3E;
  computer->memory[write_addr++] = 0x03;
  computer->memory[write_addr++] = 0x12;
  computer->memory[write_addr++] = 0x02;

  // RJMPIZD: condition FALSE (Z=0) -> fall through
  computer->memory[write_addr++] = 0x22; // RJMPIZD
  computer->memory[write_addr++] = 0x00; // offset = 0 (irrelevant, won't jump)
  computer->memory[write_addr++] = 0x00;

  // RJMPIGD: condition TRUE (Z=0, S=0) -> jump forward to HLT
  computer->memory[write_addr++] = 0x24; // RJMPIGD
  computer->memory[write_addr++] = 0x03; // offset = +3 (past this instruction to HLT)
  computer->memory[write_addr++] = 0x00;

  computer->memory[write_addr++] = 0x00; // HLT (consumed by auto-increment)

  computer->memory[memory_data_addr] = 0xCD;
  computer->memory[memory_data_addr + 1] = 0xAB;

  // Indirection pointer for ALM MODE 2 -> 0x021300
  computer->memory[0x021200] = 0x00;
  computer->memory[0x021201] = 0x13;
  computer->memory[0x021202] = 0x02;

  // Indirection pointer for ALM MODE 3 -> 0x021302
  computer->memory[0x021203] = 0x02;
  computer->memory[0x021204] = 0x13;
  computer->memory[0x021205] = 0x02;

  // Indirection pointer for RLM MODE 2 -> 0x021500
  computer->memory[0x021404] = 0x00;
  computer->memory[0x021405] = 0x15;
  computer->memory[0x021406] = 0x02;

  // Indirection pointer for RLM MODE 3 -> 0x021502
  computer->memory[0x021407] = 0x02;
  computer->memory[0x021408] = 0x15;
  computer->memory[0x021409] = 0x02;

  // Indirection pointer for MIWR (R12=0x0003) -> 0x020700
  computer->memory[0x020003] = 0x00;
  computer->memory[0x020004] = 0x07;
  computer->memory[0x020005] = 0x02;

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
      computer->memory[0x021000] != 0xBB ||
      computer->memory[0x021001] != 0xBB ||
      computer->memory[0x021002] != 0x00 ||
      computer->memory[0x021300] != 0xBB ||
      computer->memory[0x021302] != 0xBB ||
      computer->memory[0x021303] != 0x00 ||
      computer->memory[0x021400] != 0x34 ||
      computer->memory[0x021401] != 0xCD ||
      computer->memory[0x021402] != 0xAB ||
      computer->memory[0x021500] != 0x34 ||
      computer->memory[0x021502] != 0xCD ||
      computer->memory[0x021503] != 0xAB ||
      computer->memory[0x02FF00] != 0xFF ||
      computer->memory[0x02FF01] != 0x00 ||
      computer->memory[0x020700] != 0xFF ||
      computer->memory[0x020701] != 0x00) {
    fprintf(
        stderr,
        "%sTest failed: R0=0x%X R1=0x%X R2=0x%X R3=0x%X R4=0x%X R5=0x%X "
        "R6=0x%X R7=0x%X R8=0x%X R9=0x%X R10=0x%X R11=0x%X R12=0x%X R13=0x%X "
        "R14=0x%X MEM[0x21000]=0x%X MEM[0x21001]=0x%X MEM[0x21002]=0x%X "
        "MEM[0x21300]=0x%X MEM[0x21302]=0x%X MEM[0x21303]=0x%X "
        "MEM[0x21400]=0x%X MEM[0x21401]=0x%X MEM[0x21402]=0x%X "
        "MEM[0x21500]=0x%X MEM[0x21502]=0x%X MEM[0x21503]=0x%X "
        "MEM[0x2FF00]=0x%X MEM[0x2FF01]=0x%X "
        "MEM[0x20700]=0x%X MEM[0x20701]=0x%X\n%s",
        CONSOLE_RED, computer->cores[0].registers[0],
        computer->cores[0].registers[1], computer->cores[0].registers[2],
        computer->cores[0].registers[3], computer->cores[0].registers[4],
        computer->cores[0].registers[5], computer->cores[0].registers[6],
        computer->cores[0].registers[7], computer->cores[0].registers[8],
        computer->cores[0].registers[9], computer->cores[0].registers[10],
        computer->cores[0].registers[11], computer->cores[0].registers[12],
        computer->cores[0].registers[13], computer->cores[0].registers[14],
        computer->memory[0x021000], computer->memory[0x021001],
        computer->memory[0x021002], computer->memory[0x021300],
        computer->memory[0x021302], computer->memory[0x021303],
        computer->memory[0x021400], computer->memory[0x021401],
        computer->memory[0x021402], computer->memory[0x021500],
        computer->memory[0x021502], computer->memory[0x021503],
        computer->memory[0x02FF00], computer->memory[0x02FF01],
        computer->memory[0x020700], computer->memory[0x020701], CONSOLE_RESET);
  }
  printf("%sTests passed%s\n", CONSOLE_GREEN, CONSOLE_RESET);
}

void test_loop(Computer *computer) {
  uint32_t write_addr = 0x010100;
  // LDI R0, 10
  computer->memory[write_addr++] = 0x32;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x0A;
  computer->memory[write_addr++] = 0x00;
  // LDI R1, 0
  computer->memory[write_addr++] = 0x32;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x00;
  // Loop: INC R1, 1
  uint32_t loop_start = write_addr;
  computer->memory[write_addr++] = 0x10;
  computer->memory[write_addr++] = 0x11;
  // DEC R0, 1
  computer->memory[write_addr++] = 0x11;
  computer->memory[write_addr++] = 0x01;
  // AJMPIGD loop_start
  computer->memory[write_addr++] = 0x35;
  computer->memory[write_addr++] = loop_start & 0xFF;
  computer->memory[write_addr++] = (loop_start >> 8) & 0xFF;
  computer->memory[write_addr++] = (loop_start >> 16) & 0xFF;
  // HLT
  computer->memory[write_addr++] = 0x00;

  computer->memory[0] = 0x00;
  computer->memory[1] = 0x01;
  computer->memory[2] = 0x01;

  computer_start(computer);
  while (!computer->halted) {
    computer_step(computer);
    if (getenv("DEBUG") != NULL) {
      computer_print(computer);
    }
  }

  if (computer->cores[0].registers[0] != 0 ||
      computer->cores[0].registers[1] != 10) {
    fprintf(stderr,
            "%sLoop test failed: R0=0x%X (expected 0) R1=0x%X (expected 10)%s\n",
            CONSOLE_RED, computer->cores[0].registers[0],
            computer->cores[0].registers[1], CONSOLE_RESET);
    return;
  }
  printf("%sLoop test passed%s\n", CONSOLE_GREEN, CONSOLE_RESET);
}

void test_fib(Computer *computer) {
  uint32_t write_addr = 0x010200;
  // LDI R0, 0 (fibo n-2)
  computer->memory[write_addr++] = 0x32;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x00;
  // LDI R1, 1 (fibo n-1)
  computer->memory[write_addr++] = 0x32;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;
  // LDI R2, 10 (counter)
  computer->memory[write_addr++] = 0x32;
  computer->memory[write_addr++] = 0x02;
  computer->memory[write_addr++] = 0x0A;
  computer->memory[write_addr++] = 0x00;
  // Loop: ADDRR R3, R0, R1  -> R3 = R0 + R1
  uint32_t loop_start = write_addr;
  computer->memory[write_addr++] = 0x2A;
  computer->memory[write_addr++] = 0x03;
  computer->memory[write_addr++] = 0x01;
  // ADDI R0, R1, 0  -> R0 = R1
  computer->memory[write_addr++] = 0x30;
  computer->memory[write_addr++] = 0x01;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x00;
  // ADDI R1, R3, 0  -> R1 = R3
  computer->memory[write_addr++] = 0x30;
  computer->memory[write_addr++] = 0x13;
  computer->memory[write_addr++] = 0x00;
  computer->memory[write_addr++] = 0x00;
  // DEC R2, 1
  computer->memory[write_addr++] = 0x11;
  computer->memory[write_addr++] = 0x21;
  // AJMPIGD loop_start
  computer->memory[write_addr++] = 0x35;
  computer->memory[write_addr++] = loop_start & 0xFF;
  computer->memory[write_addr++] = (loop_start >> 8) & 0xFF;
  computer->memory[write_addr++] = (loop_start >> 16) & 0xFF;
  // HLT
  computer->memory[write_addr++] = 0x00;

  computer->memory[0] = 0x00;
  computer->memory[1] = 0x02;
  computer->memory[2] = 0x01;

  computer_start(computer);
  while (!computer->halted) {
    computer_step(computer);
    if (getenv("DEBUG") != NULL) {
      computer_print(computer);
    }
  }

  // After 10 iterations, R0 = F(10) = 55, R1 = F(11) = 89
  if (computer->cores[0].registers[0] != 0x0037 ||
      computer->cores[0].registers[1] != 0x0059) {
    fprintf(stderr,
            "%sFib test failed: R0=0x%X (expected 0x37) R1=0x%X (expected "
            "0x59)%s\n",
            CONSOLE_RED, computer->cores[0].registers[0],
            computer->cores[0].registers[1], CONSOLE_RESET);
    return;
  }
  printf("%sFib test passed%s\n", CONSOLE_GREEN, CONSOLE_RESET);
}
