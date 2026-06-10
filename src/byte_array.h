#ifndef INCLUDE_SRC_BYTE_ARRAY_H_
#define INCLUDE_SRC_BYTE_ARRAY_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct ByteArray {
  uint8_t *data;
  size_t size;
  size_t max_size;
  size_t index;
} ByteArray;

ByteArray init_byte_array(void);
void push_byte_array(ByteArray *arr, uint8_t byte);
void free_byte_array(ByteArray *arr);

#endif // INCLUDE_SRC_BYTE_ARRAY_H_
