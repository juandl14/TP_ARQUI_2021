#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H
#include <stdint.h>

void initVideoDriver();
void clearDisplay(uint64_t color);
void drawRectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint64_t col);

#endif
