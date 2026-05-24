#include "computer.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  Computer *computer = calloc(1, sizeof(Computer));
  if (!computer) {
    fprintf(stderr, "Failed to allocate memory for Computer\n");
    return EXIT_FAILURE;
  }
  computer_init(computer);
  uint32_t program_addr = 0x010000; // Instruction Vector
  computer->memory[0] = (uint8_t)(program_addr & 0xFF);
  computer->memory[1] = (uint8_t)((program_addr >> 8) & 0xFF);
  computer->memory[2] = (uint8_t)((program_addr >> 16) & 0xFF);

  computer->memory[program_addr++] = 0x32; // LDI
  computer->memory[program_addr++] = 0x00; // Register 0
  computer->memory[program_addr++] = 0x34; // 0x1234
  computer->memory[program_addr++] = 0x12;

  computer->memory[program_addr++] = 0xC1; // ADDINC
  computer->memory[program_addr++] = 0x00; // Register 0x0 and 0x0
  computer->memory[program_addr++] = 0x01; // 0x0001
  computer->memory[program_addr++] = 0x00;

  computer->memory[program_addr++] = 0xC2; // SUBINC
  computer->memory[program_addr++] = 0x00; // Register 0x0 and 0x0
  computer->memory[program_addr++] = 0x01; // 0x0001
  computer->memory[program_addr++] = 0x00;

  computer->memory[program_addr++] = 0x00; // HLT

  computer_start(computer);
  while(!computer->halted) {
	computer_step(computer);
	// at least before all the multi-core instructions are implemented, core_print will be used instead to print only what's relevant
	core_print(&computer->cores[0]);
  }

  free(computer);
  return EXIT_SUCCESS;
}
