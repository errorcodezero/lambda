#ifndef INCLUDE_SRC_CORE_H_
#define INCLUDE_SRC_CORE_H_

#include <stdint.h>

typedef struct CoreRegister CoreRegister;

typedef struct CoreRegister {
  uint16_t data;
  uint8_t (*get_rx)(CoreRegister *self);
  uint8_t (*get_ry)(CoreRegister *self);
  uint16_t (*get_r)(CoreRegister *self);

} CoreRegister;

typedef struct Core {
  uint32_t instruction_pointer;
  CoreRegister registers[16];
} Core;

uint8_t core_register_get_rx(CoreRegister *self);
uint8_t core_register_get_ry(CoreRegister *self);
uint16_t core_register_get_r(CoreRegister *self);

#endif // INCLUDE_SRC_CORE_H_
