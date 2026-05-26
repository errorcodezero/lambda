#ifndef INCLUDE_SRC_CORE_INSTRUCTIONS_H_
#define INCLUDE_SRC_CORE_INSTRUCTIONS_H_

#include "computer.h"

void setup_core_instructions(Computer *computer);
void HLT_handler(Computer *computer, uint8_t core_id);
void LDI_handler(Computer *computer, uint8_t core_id);
void RLD_handler(Computer *computer, uint8_t core_id);
void ALD_handler(Computer *computer, uint8_t core_id);
void TJMP_handler(Computer *computer, uint8_t core_id);

#endif // INCLUDE_SRC_CORE_INSTRUCTIONS_H_
