#include "instructions.h"
#include "computer.h"
#include <assert.h>

InstructionHandler instructions[0x100];

void setup_instructions(Computer * computer) {
	// add instructions here
	instructions[I_HLT] = HLT_handler;

	computer->instructions = instructions;
}

void HLT_handler(Computer *computer, Core* core) {
	assert(computer != 0);
	assert(core != 0);
}
