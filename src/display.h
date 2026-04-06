#ifndef INCLUDE_SRC_DISPLAY_H_
#define INCLUDE_SRC_DISPLAY_H_

#include <stdint.h>

typedef union Color {
  struct {
    uint8_t red;
    uint8_t blue;
    uint8_t green;
  };
  uint8_t raw[3];
} Color;

#define COLOR_WHITE {.raw = {0xFF, 0xFF, 0xFF}};
#define COLOR_BLACK {.raw = {0, 0, 0}};

#endif // INCLUDE_SRC_DISPLAY_H_
