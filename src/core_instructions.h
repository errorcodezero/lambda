#ifndef INCLUDE_SRC_CORE_INSTRUCTIONS_H_
#define INCLUDE_SRC_CORE_INSTRUCTIONS_H_

#include "computer.h"

void setup_core_instructions(Computer *computer);
void HLT_handler(Computer *computer, uint8_t core_id);
void LDI_handler(Computer *computer, uint8_t core_id);
void RLD_handler(Computer *computer, uint8_t core_id);
void ALD_handler(Computer *computer, uint8_t core_id);
void TJMP_handler(Computer *computer, uint8_t core_id);
void ALM_handler(Computer *computer, uint8_t core_id);
void RLM_handler(Computer *computer, uint8_t core_id);
void MWR_handler(Computer *computer, uint8_t core_id);
void MIWR_handler(Computer *computer, uint8_t core_id);
void AJMPIZD_handler(Computer *computer, uint8_t core_id);
void AJMPIZI_handler(Computer *computer, uint8_t core_id);
void AJMPIGD_handler(Computer *computer, uint8_t core_id);
void AJMPIGI_handler(Computer *computer, uint8_t core_id);
void AJMPILD_handler(Computer *computer, uint8_t core_id);
void AJMPILI_handler(Computer *computer, uint8_t core_id);

void absolute_jump_helper(Computer *computer, Core *core, uint32_t memory,
                          bool indirection, bool condition);

#endif // INCLUDE_SRC_CORE_INSTRUCTIONS_H_
