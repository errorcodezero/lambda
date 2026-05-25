#include "computer.h"
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
      computer->cores[0].registers[1] != 0xABCD) {
    fprintf(stderr, "Test failed: R0=0x%X R1=0x%X\n",
            computer->cores[0].registers[0], computer->cores[0].registers[1]);
    free(computer);
    return EXIT_FAILURE;
  }

  free(computer);
  return EXIT_SUCCESS;
}
