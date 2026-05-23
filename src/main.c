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
  computer->memory[0x010000] = 0x00;
  computer->memory[0x0] = 0x00;
  computer->memory[0x1] = 0x00;
  computer->memory[0x2] = 0x01;
  // computer_print(computer);
  computer_start(computer);
  computer_step(computer);

  free(computer);
  return EXIT_SUCCESS;
}
