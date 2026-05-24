#ifndef INCLUDE_SRC_COMPUTER_H_
#define INCLUDE_SRC_COMPUTER_H_

#include "core.h"
#include "display.h"
#include "instructions.h"
#include "memory.h"
#include <stdint.h>

#define MEMORY_WIDTH 0xA000000
#define COMPUTER_CORES 4
#define DISPLAY_WIDTH 500
#define DISPLAY_HEIGHT 300

typedef struct Computer {
  Core cores[COMPUTER_CORES];
  Color display[DISPLAY_WIDTH][DISPLAY_HEIGHT];
  uint8_t memory[MEMORY_WIDTH];
  InstructionHandler instructions[0x100];
} Computer;

void computer_init(Computer *self);
void computer_start(Computer *self);
void computer_reset(Computer *self);
void computer_step_core(Computer *self, uint8_t core_id);
void computer_step(Computer *self);
uint8_t memory_get(Computer *self, uint32_t index);
uint16_t memory_get_12(Computer *self, uint32_t index);
uint16_t memory_get_16(Computer *self, uint32_t index);
uint32_t memory_get_24(Computer *self, uint32_t index);
uint32_t memory_get_32(Computer *self, uint32_t index);
void computer_print(Computer *self);

#endif // INCLUDE_SRC_COMPUTER_H_
