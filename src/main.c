#include "computer.h"
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

  computer->memory[program_addr + 0] = 0x32; // LDI
  computer->memory[program_addr + 1] = 0x00; // Register 0
  computer->memory[program_addr + 2] = 0x34; // 0x1234
  computer->memory[program_addr + 3] = 0x12;
  computer->memory[program_addr + 4] = 0x00; // HLT

  computer_start(computer);
  computer_step(computer);
  computer_step(computer);

  free(computer);
  return EXIT_SUCCESS;
}
