#include "core.h"
#include <stdbit.h>

CoreRegister init_core_register() {
  CoreRegister reg = {
      .reg_data.data = 0,
      .get_rx = core_register_get_rx,
      .get_ry = core_register_get_ry,
      .get_rxy = core_register_get_rxy,
  };

  return reg;
}

uint8_t core_register_get_rx(CoreRegister *self) {
#if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE)
  return self->reg_data.d2;
#else
  return self->reg_data.d1;
#endif /* if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE) */
}

uint8_t core_register_get_ry(CoreRegister *self) {
#if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE)
  return self->reg_data.d1;
#else
  return self->reg_data.d2;
#endif /* if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE) */
}


uint16_t core_register_get_rxy(CoreRegister *self) {
  return self->reg_data.data;
}
