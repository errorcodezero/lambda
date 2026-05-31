#include "computer.h"
#include "console.h"
#include "core.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  Computer *computer = calloc(1, sizeof(Computer));
  if (argc < 2) {
    printf("Usage\n%s test\n%s run [file]\n", argv[0], argv[0]);
    return EXIT_FAILURE;
  }
  if (!computer) {
    fprintf(stderr, "Failed to allocate memory for Computer\n");
    return EXIT_FAILURE;
  }
  computer_init(computer);

  if (strcmp(argv[1], "test") == 0) {
    test(computer);
  } else if (strcmp(argv[1], "run") == 0) {
    if (argc != 3) {
      printf("Usage\n%s test\n%s run [file]\n", argv[0], argv[0]);
      return EXIT_FAILURE;
    }
    FILE *file = fopen(argv[2], "rb");
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    uint8_t *buffer = malloc(size * sizeof(uint8_t));
    fread(buffer, 1, size, file);
    fclose(file);

    memcpy(computer->memory, buffer, size);
    free(buffer);

    computer_start(computer);
    while (!computer->halted) {
      computer_step(computer);
      if (getenv("DEBUG") != NULL) {
        computer_print(computer);
      }
    }

  } else {
    printf("Usage\n%s test\n%s run [file]\n", argv[0], argv[0]);
  }

  free(computer);
  return EXIT_SUCCESS;
}
