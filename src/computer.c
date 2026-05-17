#include "computer.h"

void computer_reset(Computer *self) {
  self->cores[0]->instruction_pointer = self->memory[0];
}
