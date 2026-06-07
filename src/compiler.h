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
  TT_FUNCTION_END,
  TT_POSITIONING,
  TT_ARGUMENT,
  TT_HEX_VALUE,
  TT_STR_VALUE,
} TokenType;

typedef struct {
  uint8_t core;
  bool all_cores;
  uint8_t position;
  bool has_position;
} PositioningData;

typedef union TokenData {
  char *string;
  uint8_t register_id;
  uint16_t number;
  PositioningData positioning;
} TokenData;

typedef struct Token {
  TokenType type;
  TokenData *data;
} Token;

typedef struct Scanner {
  Token *tokens;
  size_t tokens_size;
  size_t tokens_maximum_size;
  char *source;
  size_t source_index;
  size_t line;
} Scanner;

void scan_scanner(Scanner *scanner);
char advance_scanner(Scanner *scanner);
size_t push_token_scanner(Scanner *scanner, TokenType token_type,
                          TokenData *token_data);
uint8_t char_to_hex(char character);
void error_scanner(Scanner *scanner, char *message);
void function_scanner(Scanner *scanner);
void print_tokens(Scanner *scanner);

#endif // INCLUDE_SRC_COMPILER_COMPILER_H_
