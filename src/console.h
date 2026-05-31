#ifndef INCLUDE_SRC_CONSOLE_H_
#define INCLUDE_SRC_CONSOLE_H_

#include <stdint.h>

#define CONSOLE_RED "\033[31m"
#define CONSOLE_GREEN "\033[32m"
#define CONSOLE_YELLOW "\033[33m"
#define CONSOLE_BLUE "\033[34m"
#define CONSOLE_MAGENTA "\033[35m"
#define CONSOLE_CYAN "\033[36m"
#define CONSOLE_WHITE "\033[37m"
#define CONSOLE_RESET "\033[0m"

void console_print_core(uint8_t id, uint32_t instruction_pointer);
#endif
