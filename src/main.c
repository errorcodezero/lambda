#include "computer.h"
#include "console.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  Computer *computer = calloc(1, sizeof(Computer));
  (void) argc;
  (void) argv;
  if (!computer) {
    fprintf(stderr, "Failed to allocate memory for Computer\n");
    return EXIT_FAILURE;
  }
  computer_init(computer);
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

  computer->memory[write_addr++] = 0x00; // HLT

  computer->memory[memory_data_addr] = 0xCD;
  computer->memory[memory_data_addr + 1] = 0xAB;

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
      computer->cores[0].registers[3] != 0x00FF ||
      computer->cores[0].registers[4] != 0xFF00 ||
      computer->cores[0].registers[5] != 0xF000 ||
      computer->cores[0].registers[6] != 0xFFF0 ||
      computer->cores[0].registers[7] != 0xF00F) {
    fprintf(stderr,
            "Test failed: R0=0x%X R1=0x%X R2=0x%X R3=0x%X R4=0x%X R5=0x%X "
            "R6=0x%X R7=0x%X\n",
            computer->cores[0].registers[0], computer->cores[0].registers[1],
            computer->cores[0].registers[2], computer->cores[0].registers[3],
            computer->cores[0].registers[4], computer->cores[0].registers[5],
            computer->cores[0].registers[6], computer->cores[0].registers[7]);
    free(computer);
    return EXIT_FAILURE;
  }
  printf("%sTests passed%s\n", CONSOLE_GREEN, CONSOLE_RESET);

  free(computer);
  return EXIT_SUCCESS;
}
