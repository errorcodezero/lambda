#include "compiler.h"
#include "console.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool is_name_char(char c) {
  return isalnum((unsigned char)c) || c == '_';
}

static TokenData *token_data_string(const char *str) {
  TokenData *td = calloc(1, sizeof(TokenData));
  td->size = strlen(str) + 1;
  td->bytes = malloc(td->size);
  memcpy(td->bytes, str, td->size);
  return td;
}

static TokenData *token_data_uint8(uint8_t val) {
  TokenData *td = calloc(1, sizeof(TokenData));
  td->size = 1;
  td->bytes = malloc(1);
  td->bytes[0] = val;
  return td;
}

static TokenData *token_data_uint16(uint16_t val) {
  TokenData *td = calloc(1, sizeof(TokenData));
  td->size = 2;
  td->bytes = malloc(2);
  td->bytes[0] = val & 0xFF;
  td->bytes[1] = (val >> 8) & 0xFF;
  return td;
}

static TokenData *token_data_positioning(PositioningData pos) {
  TokenData *td = calloc(1, sizeof(TokenData));
  td->size = sizeof(PositioningData);
  td->bytes = malloc(td->size);
  memcpy(td->bytes, &pos, td->size);
  return td;
}

size_t push_token_scanner(Scanner *scanner, TokenType token_type,
                          TokenData *token_data) {
  if (scanner->tokens_size >= scanner->tokens_maximum_size) {
    scanner->tokens_maximum_size *= 2;
    scanner->tokens = realloc(scanner->tokens, scanner->tokens_maximum_size);
  }

  Token token = {
      .data = token_data,
      .type = token_type,
  };

  scanner->tokens[scanner->tokens_size++] = token;
  return scanner->tokens_size;
}

Scanner *init_scanner(char *source) {
  Scanner *scanner = calloc(1, sizeof(Scanner));
  scanner->tokens = calloc(64, sizeof(Token));
  scanner->tokens_size = 0;
  scanner->tokens_maximum_size = 64;
  scanner->source = source;
  scanner->source_index = 0;
  scanner->line = 1;

  return scanner;
}

void scan_scanner(Scanner *scanner) {
  char character = advance_scanner(scanner);
  while (character != '\0') {
    switch (character) {
    case '/': {
      while (character != '\n' && character != '\0') {
        character = advance_scanner(scanner);
      }
      break;
    }
    case '\n':
      scanner->line++;
      break;
    case '#': {
      char string[5];
      for (uint8_t i = 0; i < 4; i++) {
        character = advance_scanner(scanner);
        string[i] = character;
      }
      string[4] = '\0';
      if (strcmp(string, "data") == 0) {
        push_token_scanner(scanner, TT_DATA_SECTION, NULL);
      } else if (strcmp(string, "text") == 0) {
        push_token_scanner(scanner, TT_TEXT_SECTION, NULL);
      } else {
        error_scanner(scanner, "Invalid section title");
      }
      break;
    }
    case '$': {
      uint8_t register_id = char_to_hex(advance_scanner(scanner));
      if (register_id >= 0xF) {
        error_scanner(scanner, "Invalid register");
      } else {
        push_token_scanner(scanner, TT_REGISTER, token_data_uint8(register_id));
      }
      break;
    }
    case '@': {
      char var_name[256];
      size_t i = 0;
      character = advance_scanner(scanner);
      bool is_addr = (character == '&');
      if (is_addr) {
        character = advance_scanner(scanner);
      }
      while (is_name_char(character) && i < 255) {
        var_name[i++] = character;
        character = advance_scanner(scanner);
      }
      var_name[i] = '\0';
      push_token_scanner(scanner,
                         is_addr ? TT_NUM_VARIABLE_ADDR : TT_NUM_VARIABLE,
                         token_data_string(var_name));
      continue;
    }
    case '\'': {
      char var_name[256];
      size_t i = 0;
      character = advance_scanner(scanner);
      while (is_name_char(character) && i < 255) {
        var_name[i++] = character;
        character = advance_scanner(scanner);
      }
      var_name[i] = '\0';
      push_token_scanner(scanner, TT_STR_VARIABLE, token_data_string(var_name));
      continue;
    }
    case '=':
    case '"': {
      char str_val[1024];
      size_t i = 0;
      character = advance_scanner(scanner);
      while (character != '"' && character != '\0' && i < 1023) {
        str_val[i++] = character;
        character = advance_scanner(scanner);
      }
      str_val[i] = '\0';
      if (character != '"') {
        error_scanner(scanner, "Unterminated string literal");
        break;
      }
      TokenData *data = token_data_string(str_val);
      push_token_scanner(scanner, TT_STR_VALUE, data);
      break;
    }
    case '0': {
      character = advance_scanner(scanner);
      if (character == 'x' || character == 'X') {
        uint16_t value = 0;
        character = advance_scanner(scanner);
        while (isxdigit((unsigned char)character)) {
          value = (value << 4) | char_to_hex(character);
          character = advance_scanner(scanner);
        }
        push_token_scanner(scanner, TT_HEX_VALUE, token_data_uint16(value));
        continue;
      }
      continue;
    }
    case '[':
      function_scanner(scanner);
      break;
    case ' ':
    case '\t':
      break;
    case '{':
    case '}':
    case '(':
    case ')':
    case ',':
      break;
    default: {
      char msg[64];
      snprintf(msg, sizeof(msg), "Unrecognized character: '%c' (0x%02X)",
               character, (unsigned char)character);
      error_scanner(scanner, msg);
      break;
    }
    }
    character = advance_scanner(scanner);
  }
}

char advance_scanner(Scanner *scanner) {
  if (scanner->source[scanner->source_index] == '\0') {
    return '\0';
  }
  return scanner->source[scanner->source_index++];
}

static void skip_whitespace(Scanner *scanner) {
  char c = scanner->source[scanner->source_index];
  while (c == ' ' || c == '\t') {
    advance_scanner(scanner);
    c = scanner->source[scanner->source_index];
  }
}

void function_scanner(Scanner *scanner) {
  char name[256];
  size_t i = 0;
  char character = advance_scanner(scanner);

  bool is_end = (character == '/');
  if (is_end) {
    character = advance_scanner(scanner);
  }

  while (character != ']' && character != '\0' && i < 255) {
    name[i++] = character;
    character = advance_scanner(scanner);
  }
  name[i] = '\0';

  if (character != ']') {
    error_scanner(scanner, "Unterminated function bracket");
    return;
  }

  TokenData *data = token_data_string(name);
  push_token_scanner(scanner, is_end ? TT_FUNCTION_END : TT_FUNCTION_START,
                     data);

  if (is_end)
    return;

  skip_whitespace(scanner);
  character = scanner->source[scanner->source_index];

  if (character == '{') {
    advance_scanner(scanner);
    PositioningData pos = {0};
    character = scanner->source[scanner->source_index];

    if (character == '*') {
      advance_scanner(scanner);
      pos.all_cores = true;
    } else {
      uint8_t core = char_to_hex(character);
      if (core >= 0xF) {
        error_scanner(scanner, "Invalid core in positioning");
        return;
      }
      pos.core = core;
      advance_scanner(scanner);
    }

    skip_whitespace(scanner);
    character = scanner->source[scanner->source_index];

    if (character >= '0' && character <= '9') {
      pos.position = char_to_hex(character);
      pos.has_position = true;
      advance_scanner(scanner);
    }

    skip_whitespace(scanner);
    character = scanner->source[scanner->source_index];
    if (character != '}') {
      error_scanner(scanner, "Unterminated positioning brace");
      return;
    }
    advance_scanner(scanner);

    TokenData *pos_data = token_data_positioning(pos);
    push_token_scanner(scanner, TT_POSITIONING, pos_data);
  }

  skip_whitespace(scanner);
  character = scanner->source[scanner->source_index];

  if (character == '[') {
    advance_scanner(scanner);
    PositioningData pos = {0};
    character = scanner->source[scanner->source_index];

    if (character == '*') {
      advance_scanner(scanner);
      pos.all_cores = true;
    } else {
      uint8_t core = char_to_hex(character);
      if (core >= 0xF) {
        error_scanner(scanner, "Invalid core in positioning");
        return;
      }
      pos.core = core;
      advance_scanner(scanner);
    }

    skip_whitespace(scanner);
    character = scanner->source[scanner->source_index];

    if (character >= '0' && character <= '9') {
      pos.position = char_to_hex(character);
      pos.has_position = true;
      advance_scanner(scanner);
    }

    skip_whitespace(scanner);
    character = scanner->source[scanner->source_index];
    if (character != ']') {
      error_scanner(scanner, "Unterminated positioning bracket");
      return;
    }
    advance_scanner(scanner);

    TokenData *pos_data = token_data_positioning(pos);
    push_token_scanner(scanner, TT_POSITIONING, pos_data);
  }

  skip_whitespace(scanner);
  character = scanner->source[scanner->source_index];

  if (character == '(') {
    advance_scanner(scanner);
    skip_whitespace(scanner);
    character = scanner->source[scanner->source_index];

    while (character != ')' && character != '\0') {
      char arg_name[64];
      size_t j = 0;

      if (character == ',') {
        advance_scanner(scanner);
        skip_whitespace(scanner);
        character = scanner->source[scanner->source_index];
        continue;
      }

      while (character != ',' && character != ')' && character != '\0' &&
             j < 63) {
        arg_name[j++] = character;
        advance_scanner(scanner);
        character = scanner->source[scanner->source_index];
      }
      arg_name[j] = '\0';

      push_token_scanner(scanner, TT_ARGUMENT, token_data_string(arg_name));
    }

    if (character != ')') {
      error_scanner(scanner, "Unterminated argument parens");
      return;
    }
    advance_scanner(scanner);
  }
}

uint8_t char_to_hex(char character) {
  if (character >= '0' && character <= '9') {
    return character - '0';
  } else if (character >= 'A' && character <= 'F') {
    return 10 + character - 'A';
  } else if (character >= 'a' && character <= 'f') {
    return 10 + character - 'a';
  } else {
    // easy error checking which is just to see if the returned value is >= 0xF
    return 0xFF;
  }
}

void error_scanner(Scanner *scanner, char *message) {
  printf("%s%zu | %s%s\n", CONSOLE_RED, scanner->line, message, CONSOLE_RESET);
}

static const char *token_type_name(TokenType type) {
  switch (type) {
  case TT_NUM_VARIABLE:
    return "TT_NUM_VARIABLE";
  case TT_NUM_VARIABLE_ADDR:
    return "TT_NUM_VARIABLE_ADDR";
  case TT_STR_VARIABLE:
    return "TT_STR_VARIABLE";
  case TT_EQUALS:
    return "TT_EQUALS";
  case TT_REGISTER:
    return "TT_REGISTER";
  case TT_DATA_SECTION:
    return "TT_DATA_SECTION";
  case TT_TEXT_SECTION:
    return "TT_TEXT_SECTION";
  case TT_FUNCTION_START:
    return "TT_FUNCTION_START";
  case TT_FUNCTION_END:
    return "TT_FUNCTION_END";
  case TT_POSITIONING:
    return "TT_POSITIONING";
  case TT_ARGUMENT:
    return "TT_ARGUMENT";
  case TT_HEX_VALUE:
    return "TT_HEX_VALUE";
  case TT_STR_VALUE:
    return "TT_STR_VALUE";
  case TT_EOF:
    return "TT_EOF";
  }
  return "UNKNOWN";
}

void print_tokens(Scanner *scanner) {
  for (size_t i = 0; i < scanner->tokens_size; i++) {
    Token *token = &scanner->tokens[i];
    printf("[%zu] %s", i, token_type_name(token->type));

    if (token->data) {
      switch (token->type) {
      case TT_NUM_VARIABLE:
      case TT_NUM_VARIABLE_ADDR:
      case TT_STR_VARIABLE:
      case TT_FUNCTION_START:
      case TT_FUNCTION_END:
      case TT_ARGUMENT:
      case TT_STR_VALUE:
        printf(" \"%s\"", token->data->string);
        break;
      case TT_REGISTER:
        printf(" $%X", token->data->bytes[0]);
        break;
      case TT_HEX_VALUE:
        printf(" 0x%04X",
               (uint16_t)(token->data->bytes[0] | (token->data->bytes[1] << 8)));
        break;
      case TT_POSITIONING: {
        PositioningData *p = (PositioningData *)token->data->bytes;
        printf(" {");
        if (p->all_cores)
          printf("*");
        else
          printf("%X", p->core);
        if (p->has_position)
          printf(" %X", p->position);
        printf("}");
        break;
      }
      default:
        break;
      }
    }
    printf("\n");
  }
}

Compiler *init_compiler(Scanner *scanner) {
  Compiler *compiler = calloc(1, sizeof(Compiler));

  compiler->tokens = scanner->tokens;
  compiler->tokens_size = scanner->tokens_size;

  return compiler;
}

Token *advance_compiler(Compiler *compiler) {
  if (compiler->tokens_index >= compiler->tokens_size) {
    return NULL;
  }
  return &compiler->tokens[compiler->tokens_index++];
}

void reset_compiler(Compiler *compiler) { compiler->tokens_index = 0; }

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

  // move into the data section
  while (token->type != TT_DATA_SECTION || token->type != TT_EOF)
    token = advance_compiler(compiler);

  // parse the text section into the symbol table
  // TODO: add actual error handling
  while (token->type != TT_TEXT_SECTION || token->type != TT_EOF) {
    token = advance_compiler(compiler);
    if (token->type != TT_NUM_VARIABLE || token->type != TT_STR_VARIABLE) {
      return;
    } else if (token->type == TT_STR_VARIABLE) {
      Symbol symbol = {
          .name = token->data->string,
      };
      token = advance_compiler(compiler);
      if (token->type == TT_STR_VALUE)
        return;
      symbol.data = token->data->bytes;
      symbol.size = token->data->size;
      push_symbol_compiler(compiler, symbol);
    } else if (token->type == TT_NUM_VARIABLE) {
      Symbol symbol = {
          .name = token->data->string,
      };
      token = advance_compiler(compiler);
      if (token->type == TT_HEX_VALUE)
        return;
      symbol.data = token->data->bytes;
      symbol.size = token->data->size;
      push_symbol_compiler(compiler, symbol);
    }
  }
}
