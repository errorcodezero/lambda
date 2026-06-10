#include "compiler.h"
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Compiler *init_compiler(Scanner *scanner) {
  Compiler *compiler = calloc(1, sizeof(Compiler));

  compiler->tokens = scanner->tokens;
  compiler->tokens_size = scanner->tokens_size;
  compiler->symbols = calloc(64, sizeof(Symbol));
  compiler->symbols_maximum_size = 64;

  return compiler;
}

Token *advance_compiler(Compiler *compiler) {
  if (compiler->tokens_index >= compiler->tokens_size) {
    return NULL;
  }
  return &compiler->tokens[compiler->tokens_index++];
}

void reset_compiler(Compiler *compiler) { compiler->tokens_index = 0; }

void print_symbols_compiler(Compiler *compiler) {
  for (size_t i = 0; i < compiler->symbols_size; i++) {
    Symbol *s = &compiler->symbols[i];
    printf("[%zu] \"%s\" size=%u", i, s->name, s->size);
    if (s->data) {
      printf(" data=");
      for (uint32_t j = 0; j < s->size; j++)
        printf("%02X", s->data[j]);
    }
    printf("\n");
  }
}

size_t push_symbol_compiler(Compiler *compiler, Symbol symbol) {
  if (compiler->symbols_size >= compiler->symbols_maximum_size) {
    compiler->symbols_maximum_size *= 2;
    compiler->symbols =
        realloc(compiler->symbols, compiler->symbols_maximum_size);
  }

  compiler->symbols[compiler->symbols_size++] = symbol;
  return compiler->symbols_size;
}

void compile_compiler(Compiler *compiler) {
  // pass 1: data section
  Token *token = advance_compiler(compiler);

  while (token != NULL && token->type != TT_DATA_SECTION)
    token = advance_compiler(compiler);

  while (token != NULL && token->type != TT_TEXT_SECTION) {
    token = advance_compiler(compiler);
    if (token == NULL)
      break;
    if (token->type == TT_STR_VARIABLE) {
      Symbol symbol = {
          .name = token->data->string,
      };
      token = advance_compiler(compiler);
      if (token == NULL || token->type != TT_STR_VALUE)
        break;
      symbol.data = token->data->bytes;
      symbol.size = token->data->size;
      push_symbol_compiler(compiler, symbol);
    } else if (token->type == TT_NUM_VARIABLE) {
      Symbol symbol = {
          .name = token->data->string,
      };
      token = advance_compiler(compiler);
      if (token == NULL || token->type != TT_HEX_VALUE)
        break;
      symbol.data = token->data->bytes;
      symbol.size = token->data->size;
      push_symbol_compiler(compiler, symbol);
    }
  }

  // pass 2: text section
  reset_compiler(compiler);

  while (token != NULL && token->type != TT_TEXT_SECTION)
    token = advance_compiler(compiler);

  while (token != NULL && token->type != TT_DATA_SECTION) {
    token = advance_compiler(compiler);
  }
}

void free_compiler(Compiler *compiler) {
  free(compiler->symbols);
  free(compiler);
}
