#include "core.h"
#include <stdbit.h>

CoreRegister init_core_register() {
  CoreRegister reg = {
      .get_rx = core_register_get_rx,
      .get_ry = core_register_get_ry,
      .get_r = core_register_get_r,
  };

  return reg;
}

