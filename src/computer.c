#include "computer.h"
#include "instructions.h"

Computer computer_init() {
	Computer computer = {
		.cores = {{}, {}, {}, {}}
	};
	computer.instructions = get_instructions();

	return computer;
}

void computer_reset(Computer *self) {
  self->cores[0].instruction_pointer = memory_get(self->memory, 0);
}

void computer_step_core(Computer *self, Core *core) {
  self->instructions[memory_get(self->memory, self->cores[0].instruction_pointer)](self);
}
