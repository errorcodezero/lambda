#include "console.h"
#include <stdio.h>

void console_print_core(uint8_t id, uint32_t instruction_pointer) {
  printf("%sCORE %d%s | %s0x%06X%s | ", CONSOLE_YELLOW, id, CONSOLE_RESET,
         CONSOLE_CYAN, instruction_pointer, CONSOLE_RESET);
}
