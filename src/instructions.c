#include "instructions.h"
#include "computer.h"
#include <assert.h>

InstructionHandler instructions[0x100];

void setup_instructions(Computer * computer) {
	// add instructions here

	assert(computer != 0);
	// computer->instructions = instructions;
}
