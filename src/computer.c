#include "computer.h"
#include "instructions.h"
#include "core.h"
#include <stdio.h>

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
  self->instructions[memory_get(self, core->instruction_pointer)](self, core);
}

uint8_t memory_get(Computer *self, uint32_t index) { return self->memory[index]; }

void computer_print(Computer *self) {
	for (uint8_t i = 0; i < COMPUTER_CORES; i++) {
		printf("--- CORE %d ---\n", i);
		core_print(&self->cores[i]);
	}
}
