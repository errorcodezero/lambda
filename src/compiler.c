#include "compiler.h"
#include <stdlib.h>
#include <string.h>

size_t push_token(Scanner *scanner, Token token) {
  if (scanner->tokens_size >= scanner->tokens_maximum_size) {
    scanner->tokens_maximum_size *= 2;
    scanner->tokens = realloc(scanner->tokens, scanner->tokens_maximum_size);
  }
  scanner->tokens[scanner->tokens_size++] = token;
  return scanner->tokens_size;
}

void scan(Scanner *scanner) { 
	char character = advance(scanner);
	while (character != '\0') {
		character = advance(scanner);
	}
}

char advance(Scanner *scanner) {
  if (scanner->source[scanner->source_index] == '\0') {
	return '\0';
  }
  return scanner->source[scanner->source_index++];
}
