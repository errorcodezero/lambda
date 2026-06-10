#ifndef INCLUDE_SRC_COMPILER_H_
#define INCLUDE_SRC_COMPILER_H_

#include "scanner.h"

typedef struct Symbol {
  char *name;
  uint8_t *data;
  uint32_t size;
  // if this is false, core and interrupt are useless.
  bool function;
  // value above 5 means it applies to all cores
  uint8_t core;
  // value above 64 instead becomes start function
  uint8_t interrupt;
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
void free_compiler(Compiler *compiler);

#endif // INCLUDE_SRC_COMPILER_H_
