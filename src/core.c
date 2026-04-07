#include "core.h"
#include <stdbit.h>

CoreRegister init_core_register() {
  CoreRegister reg = {
	  .data = 0,
      .get_rx = core_register_get_rx,
      .get_ry = core_register_get_ry,
      .get_r = core_register_get_r,
  };

  return reg;
}

uint8_t core_register_get_rx(CoreRegister *self) {
#if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE)
  return (uint8_t) (self->data >> 8);
#else
  return (uint8_t) (self->data);
#endif /* if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE) */
}

uint8_t core_register_get_ry(CoreRegister *self) {
#if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE)
  return (uint8_t) (self->data);
#else
  return (uint8_t) (self->data >> 8);
#endif 
}


uint16_t core_register_get_r(CoreRegister *self) {
#if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE)
  return self->data;
#else
  return ((((uint16_t) self->get_rx()) << 8) + self->get_ry());
#endif 
}
