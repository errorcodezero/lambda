#ifndef INCLUDE_SRC_ARITHMETIC_INSTRUCTIONS_H_
#define INCLUDE_SRC_ARITHMETIC_INSTRUCTIONS_H_

#include "computer.h"
#include "stdint.h"

void setup_arithmetic_instructions(Computer *computer);
void ADDI_handler(Computer *computer, uint8_t core_id);
void SUBI_handler(Computer *computer, uint8_t core_id);
void ADDINC_handler(Computer *computer, uint8_t core_id);
void SUBINC_handler(Computer *computer, uint8_t core_id);
void INC_handler(Computer *computer, uint8_t core_id);
void DEC_handler(Computer *computer, uint8_t core_id);
void ADDR_handler(Computer *computer, uint8_t core_id);
void SUBR_handler(Computer *computer, uint8_t core_id);
void ADDRR_handler(Computer *computer, uint8_t core_id);
void SUBRR_handler(Computer *computer, uint8_t core_id);

#endif
