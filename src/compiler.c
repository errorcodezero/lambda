#include "compiler.h"
#include "byte_array.h"
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
    printf("[%zu] \"%s\" size=%zu", i, s->name, s->bytes.size);
    if (s->bytes.data) {
      printf(" data=");
      for (size_t j = 0; j < s->bytes.size; j++)
        printf("%02X", s->bytes.data[j]);
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
          .bytes = init_byte_array(),
      };
      token = advance_compiler(compiler);
      if (token == NULL || token->type != TT_STR_VALUE)
        break;
      for (size_t j = 0; j < token->data->size; j++)
        push_byte_array(&symbol.bytes, token->data->bytes[j]);
      push_symbol_compiler(compiler, symbol);
    } else if (token->type == TT_NUM_VARIABLE) {
      Symbol symbol = {
          .name = token->data->string,
          .bytes = init_byte_array(),
      };
      token = advance_compiler(compiler);
      if (token == NULL || token->type != TT_HEX_VALUE)
        break;
      for (size_t j = 0; j < token->data->size; j++)
        push_byte_array(&symbol.bytes, token->data->bytes[j]);
      push_symbol_compiler(compiler, symbol);
    }
  }

  // pass 2: text section
  reset_compiler(compiler);
  token = advance_compiler(compiler);

  while (token != NULL && token->type != TT_TEXT_SECTION)
    token = advance_compiler(compiler);

  while (token != NULL) {
    token = advance_compiler(compiler);
    if (token == NULL)
      break;
    if (token->type == TT_FUNCTION_START) {
      char *name = token->data->string;
      uint8_t core = 0;
      uint8_t interrupt = 0xFF;
      token = advance_compiler(compiler);
      if (token != NULL && token->type == TT_POSITIONING) {
        PositioningData *position = (PositioningData *)token->data->bytes;
        if (position->all_cores)
          core = 6;
        else
          core = position->core;
        interrupt = position->has_position ? position->position : 0xFF;
        token = advance_compiler(compiler);
      }
      ByteArray bytes = init_byte_array();
      while (token != NULL && token->type != TT_FUNCTION_END) {
        token_value_compiler(compiler, token, &bytes);
        token = advance_compiler(compiler);
      }
      Symbol symbol = {
          .name = name,
          .bytes = bytes,
          .function = true,
          .core = core,
          .interrupt = interrupt,
      };
      push_symbol_compiler(compiler, symbol);
    }
  }
}

void token_value_compiler(Compiler *compiler, Token *token, ByteArray *arr) {
  if (token->type == TT_HEX_VALUE) {
    for (size_t i = 0; i < token->data->size; i++)
      push_byte_array(arr, token->data->bytes[i]);
  } else if (token->type == TT_NUM_VARIABLE) {
    Instructions opcode = instruction_from_string(token->data->string);
    if (opcode != (Instructions)-1) {
      push_byte_array(arr, (uint8_t)opcode);
    } else {
      for (size_t i = 0; i < compiler->symbols_size; i++) {
        if (strcmp(compiler->symbols[i].name, token->data->string) == 0) {
          Symbol *symbol = &compiler->symbols[i];
          for (size_t j = 0; j < symbol->bytes.size; j++)
            push_byte_array(arr, symbol->bytes.data[j]);
          break;
        }
      }
    }
  } else if (token->type == TT_REGISTER) {
    push_byte_array(arr, token->data->bytes[0]);
  }
}

void free_compiler(Compiler *compiler) {
  for (size_t i = 0; i < compiler->symbols_size; i++)
    free_byte_array(&compiler->symbols[i].bytes);
  free(compiler->symbols);
  free(compiler);
}
