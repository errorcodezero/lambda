#include "core.h"
#include "computer.h"
#include <stdbit.h>
#include <stdio.h>

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

void core_print(Core * self) {
  printf("Instruction Pointer: %d\n", self->instruction_pointer);
  for (uint8_t i = 0; i < 13; i++)
	  printf("Register 0x%X: 0x%X\n", i, core_register_get_r(&self->registers[i]));
  printf("Register 0xD: 0x%X => Status Register\n", self->status);
  printf("Register 0xE: 0x%X => Bank Register\n", self->bank);
  printf("Register 0xF: 0x0 => Zero Register\n");
  printf("Stack Pointer: %d\n", self->stack_pointer);
  printf("Base Pointer: %d\n", self->base_pointer);
}
