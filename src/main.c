#include <stdio.h>
#include <stdlib.h>
#include "computer.h"

int main() {
  Computer *computer = calloc(1, sizeof(Computer));
  printf("Core 0 IP: %d\n", computer->cores[0].instruction_pointer);
  printf("Core 1 IP: %d\n", computer->cores[1].instruction_pointer);
  printf("Core 2 IP: %d\n", computer->cores[2].instruction_pointer);
  printf("Core 3 IP: %d\n", computer->cores[3].instruction_pointer);

  free(computer);
  return EXIT_SUCCESS;
}
