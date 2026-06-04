#ifndef INCLUDE_SRC_COMPILER_COMPILER_H_
#define INCLUDE_SRC_COMPILER_COMPILER_H_

#include "instructions.h"
#include <stddef.h>

typedef enum TokenType {
  TT_NUM_VARIABLE,
  TT_STR_VARIABLE,
  TT_EQUALS,
  TT_REGISTER,
  TT_DATA_SECTION,
  TT_TEXT_SECTION,
  TT_FUNCTION_START,
  TT_FUNCTION_END
} TokenType;

typedef struct Token {
  TokenType type;
  union {
    char *name;
    uint8_t number;
  } data;
} Token;

typedef struct Scanner {
  Token *tokens;
  size_t tokens_size;
  size_t tokens_maximum_size;
  char *source;
  size_t source_index;
} Scanner;

void scan(Scanner *scanner);
char advance(Scanner *scanner);

#endif // INCLUDE_SRC_COMPILER_COMPILER_H_
