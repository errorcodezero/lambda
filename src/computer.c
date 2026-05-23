#include "computer.h"
#include "instructions.h"
#include "memory.h"

Computer computer_init() {
	Computer computer = {
	};
	setup_instructions(&computer);

	return computer;
}

void computer_reset(Computer *self) {
  self->cores[0].instruction_pointer = memory_get(self, 0);
}

void computer_step_core(Computer *self, Core *core) {
  self->instructions[memory_get(self, core->instruction_pointer)](self);
}
