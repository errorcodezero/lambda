#include "core.h"

CoreRegister init_core_register() {
  CoreRegister reg = {
      .reg_data.data = 0,
      .get_rx = core_register_get_rx,
      .get_ry = core_register_get_ry,
      .get_rxy = core_register_get_rxy,
  };

  return reg;
}

uint8_t core_register_get_rx(CoreRegister *self) { return self->reg_data.d1; }
uint8_t core_register_get_ry(CoreRegister *self) { return self->reg_data.d2; }
uint16_t core_register_get_rxy(CoreRegister *self) { return self->reg_data.data; }
