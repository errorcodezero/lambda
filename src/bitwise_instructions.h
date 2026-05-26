#ifndef INCLUDE_SRC_BITWISE_INSTRUCTIONS_H_
#define INCLUDE_SRC_BITWISE_INSTRUCTIONS_H_

#include "computer.h"

void setup_bitwise_instructions(Computer *computer);
void XORR_handler(Computer *computer, uint8_t core_id);
void ANDR_handler(Computer *computer, uint8_t core_id);
void NOTR_handler(Computer *computer, uint8_t core_id);
void ORR_handler(Computer *computer, uint8_t core_id);
void NORR_handler(Computer *computer, uint8_t core_id);
void NANDR_handler(Computer *computer, uint8_t core_id);
void XNORR_handler(Computer *computer, uint8_t core_id);
void LSHFT_handler(Computer *computer, uint8_t core_id);
void RSHFT_handler(Computer *computer, uint8_t core_id);
void XANOR_handler(Computer *computer, uint8_t core_id);

#endif
