#include "core.h"
#include <stdbit.h>
#include <stdio.h>

uint8_t core_register_get_rx(uint16_t self) {
#if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE)
  return (uint8_t)(self >> 8);
#else
  return (uint8_t)(*self);
#endif /* if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE) */
}

uint8_t core_register_get_ry(uint16_t self) {
#if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE)
  return (uint8_t)(self);
#else
  return (uint8_t)(self->data >> 8);
#endif
}

uint16_t core_register_get_r(uint16_t self) {
#if (__STDC__ENDIAN__NATIVE__ == __STDC_ENDIAN_LITTLE)
  return self;
#else
  return ((((uint16_t)core_register_get_rx(self)) << 8) +
          core_register_get_ry(self));
#endif
}

void core_print(Core *self) {
  printf("Instruction Pointer: %d\n", self->instruction_pointer);
  for (uint8_t i = 0; i < 13; i++)
    printf("Register 0x%X: 0x%X\n", i,
           core_register_get_r(self->registers[i]));
  printf("Register 0xD: 0x%X => Status Register\n", self->status);
  printf("Register 0xE: 0x%X => Bank Register\n", self->bank);
  printf("Register 0xF: 0x0 => Zero Register\n");
  printf("Stack Pointer: %d\n", self->stack_pointer);
  printf("Base Pointer: %d\n", self->base_pointer);
}

void set_register(Core *self, uint8_t reg_id, uint16_t data) {
  if (reg_id <= 0xD) {
    self->registers[reg_id] = data;
  } else if (reg_id == 0xE) {
	self->bank = data;
  }
}
