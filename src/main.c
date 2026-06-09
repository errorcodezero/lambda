#include "computer.h"
#include "compiler.h"
#include "console.h"
#include "core.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  Computer *computer = calloc(1, sizeof(Computer));
  if (argc != 3) {
    free(computer);
    printf("Usage\n%s test [test name]\n%s run [file]\n", argv[0], argv[0]);
    return EXIT_FAILURE;
  }
  if (!computer) {
    fprintf(stderr, "Failed to allocate memory for Computer\n");
    return EXIT_FAILURE;
  }
  computer_init(computer);

  if (strcmp(argv[1], "test") == 0) {
    if (strcmp(argv[2], "loop") == 0) {
      test_loop(computer);
    } else if (strcmp(argv[2], "fib") == 0) {
      test_fib(computer);
    } else if (strcmp(argv[2], "main")) {
      test(computer);
    }
  } else if (strcmp(argv[1], "compile") == 0) {
    FILE *file = fopen(argv[2], "rb");
    if (!file) {
      fprintf(stderr, "Could not open file: %s\n", argv[2]);
      free(computer);
      return EXIT_FAILURE;
    }
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    char *source = malloc(size + 1);
    fread(source, 1, size, file);
    source[size] = '\0';
    fclose(file);

    Scanner scanner = {
      .tokens = malloc(sizeof(Token) * 64),
      .tokens_size = 0,
      .tokens_maximum_size = 64,
      .source = source,
      .source_index = 0,
      .line = 1,
    };

    scan_scanner(&scanner);
    print_tokens(&scanner);

    for (size_t i = 0; i < scanner.tokens_size; i++) {
      TokenData *d = scanner.tokens[i].data;
      if (d) {
        free(d->data);
        free(d);
      }
    }
    free(scanner.tokens);
    free(source);
  } else if (strcmp(argv[1], "run") == 0) {
    if (argc != 3) {
printf("Usage\n%s test [test name]\n%s run [file]\n%s compile [file]\n", argv[0], argv[0], argv[0]);
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
    printf("Usage\n%s test [test name]\n%s run [file]\n", argv[0], argv[0]);
  }

  free(computer);
  return EXIT_SUCCESS;
}
