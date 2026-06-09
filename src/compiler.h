#ifndef INCLUDE_SRC_COMPILER_COMPILER_H_
#define INCLUDE_SRC_COMPILER_COMPILER_H_

#include "instructions.h"
#include <stddef.h>

typedef enum TokenType {
  TT_NUM_VARIABLE,
  TT_NUM_VARIABLE_ADDR,
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
  TT_EOF,
} TokenType;

typedef struct {
  uint8_t core;
  bool all_cores;
  uint8_t position;
  bool has_position;
} PositioningData;

typedef struct TokenData {
  union {
    uint8_t *bytes;
    char *string;
  };
  size_t size;
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

Scanner *init_scanner(char *source);
void scan_scanner(Scanner *scanner);
char advance_scanner(Scanner *scanner);
size_t push_token_scanner(Scanner *scanner, TokenType token_type,
                          TokenData *token_data);
uint8_t char_to_hex(char character);
void error_scanner(Scanner *scanner, char *message);
void function_scanner(Scanner *scanner);
void print_tokens_scanner(Scanner *scanner);

typedef struct Symbol {
  char *name;
  uint8_t *data;
  uint32_t size;
} Symbol;

typedef struct Compiler {
  Token *tokens;
  size_t tokens_size;
  size_t tokens_index;
  Symbol *symbols;
  size_t symbols_size;
  size_t symbols_maximum_size;
} Compiler;

Compiler *init_compiler(Scanner *scanner);
size_t push_symbol_compiler(Compiler *compiler, Symbol symbol);
Token *advance_compiler(Compiler *compiler);
void reset_compiler(Compiler *compiler);
void compile_compiler(Compiler *compiler);
void print_symbols_compiler(Compiler *compiler);
void free_scanner(Scanner *scanner);
void free_compiler(Compiler *compiler);

#endif // INCLUDE_SRC_COMPILER_COMPILER_H_
