#include "byte_array.h"
#include <stdlib.h>
#include <string.h>

ByteArray init_byte_array(void) {
  ByteArray arr = {
      .data = calloc(64, sizeof(uint8_t)),
      .size = 0,
      .max_size = 64,
      .index = 0,
  };
  return arr;
}

void push_byte_array(ByteArray *arr, uint8_t byte) {
  if (arr->size >= arr->max_size) {
    arr->max_size *= 2;
    arr->data = realloc(arr->data, arr->max_size);
  }
  arr->data[arr->size++] = byte;
}

void free_byte_array(ByteArray *arr) {
  free(arr->data);
}
