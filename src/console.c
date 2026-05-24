#include "console.h"
#include <stdio.h>

void console_print_core(uint8_t id) {
  printf("%sCORE %d%s ", CONSOLE_YELLOW, id, CONSOLE_RESET);
}
