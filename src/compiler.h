#ifndef INCLUDE_SRC_COMPILER_COMPILER_H_
#define INCLUDE_SRC_COMPILER_COMPILER_H_

#include "instructions.h"
#include <stddef.h>

typedef enum TokenType {
  TT_VARIABLE_NUMBER,
  TT_REGISTER,
  TT_FUNCTION_START,
  TT_FUNCTION_END,
  TT_DATA_SECTION,
  TT_TEXT_SECTION
} TokenType;

typedef struct Token {
  TokenType type;
  uint8_t *data;
} Token;

typedef struct Scanner {
  Token *token;
  char *source;
  size_t size;
} Scanner;

#endif // INCLUDE_SRC_COMPILER_COMPILER_H_
