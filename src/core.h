#ifndef INCLUDE_SRC_CORE_H_
#define INCLUDE_SRC_CORE_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct Core {
  uint32_t instruction_pointer;
  uint16_t registers[13];
  uint8_t status;
  uint8_t zero;
  uint8_t bank;
  uint16_t stack_pointer;
  uint16_t base_pointer;
  uint8_t interrupt_vector_table[12];
  bool awake;
} Core;

uint8_t core_register_get_rx(uint16_t self);
uint8_t core_register_get_ry(uint16_t self);
uint16_t core_register_get_r(uint16_t self);
void core_print(Core *self);
void set_register(Core *self, uint8_t reg_id, uint16_t data);

#endif // INCLUDE_SRC_CORE_H_
