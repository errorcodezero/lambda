#ifndef INCLUDE_SRC_CORE_H_
#define INCLUDE_SRC_CORE_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct CoreRegister CoreRegister;

typedef struct CoreRegister {
  union {
    struct {
      uint8_t d1;
      uint8_t d2;
    };
    uint16_t data;
  } reg_data;
  uint8_t (*get_rx)(CoreRegister *self);
  uint8_t (*get_ry)(CoreRegister *self);
  uint16_t (*get_rxy)(CoreRegister *self);
} CoreRegister;

CoreRegister init_core_register();
uint8_t core_register_get_rx(CoreRegister *self);
uint8_t core_register_get_ry(CoreRegister *self);
uint16_t core_register_get_rxy(CoreRegister *self);

typedef struct Core {
  uint32_t instruction_pointer;
  CoreRegister registers[16];
  uint8_t flags;
} Core;

#endif // INCLUDE_SRC_CORE_H_
