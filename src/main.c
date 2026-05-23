#include <stdio.h>
#include <stdlib.h>
#include "computer.h"

int main() {
  Computer *computer = calloc(1, sizeof(Computer));
  computer_print(computer);

  free(computer);
  return EXIT_SUCCESS;
}
