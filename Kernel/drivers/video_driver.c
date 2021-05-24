#ifndef VIDEO_DRIVER
#define VIDEO_DRIVER
#include <video_driver.h>
#include <stdint.h>
#include <font.h>

static uint8_t legalCoordinates(uint64_t x, uint64_t y);

struct vbe_mode_info_structure {
	uint16_t attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;			// deprecated
	uint8_t window_b;			// deprecated
	uint16_t granularity;		// deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;			// number of bytes per horizontal line
	uint16_t width;			// width in pixels
	uint16_t height;			// height in pixels
	uint8_t w_char;			// unused...
	uint8_t y_char;			// ...
	uint8_t planes;
	uint8_t bpp;			// bits per pixel in this mode
	uint8_t banks;			// deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;

	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;

	uint32_t framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__ ((packed));

struct vbe_mode_info_structure * screenData = (struct vbe_mode_info_structure *)0x0000000000005C00;

uint16_t WIDTH, HEIGHT;
uint32_t FRAME_BUFFER;

void initVideoDriver() {
  WIDTH = screenData->width;
  HEIGHT = screenData->height;
  FRAME_BUFFER = screenData->framebuffer;
}

void clearDisplay(uint64_t col) {
  uint64_t totalPixels = WIDTH*HEIGHT;
  uint8_t * curpos = (uint8_t *) FRAME_BUFFER;
  uint8_t b = col & 0x0000FF;
	uint8_t g = (col >> 8) & 0x0000FF;
	uint8_t r = (col >> 16) & 0x0000FF;
  for (uint64_t i = 0; i < totalPixels; i++) {
    *curpos = b;
    curpos++;
    *curpos = g;
    curpos++;
    *curpos = r;
    curpos++;
  }
}

void drawRectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, uint64_t col) {
  if (legalCoordinates(x, y)) {
    uint8_t b = col & 0x0000FF;
  	uint8_t g = (col >> 8) & 0x0000FF;
  	uint8_t r = (col >> 16) & 0x0000FF;
    for (uint64_t i = 0; i < height; i++) {
      for (uint64_t j = 0; j < width; j++) {
        if (legalCoordinates(x+j, y+i)) {
          uint8_t * pos = (uint8_t*)(FRAME_BUFFER + ((y+i) * WIDTH + (x+j))*3);
          *pos = b;
          pos++;
          *pos = g;
          pos++;
          *pos = r;
        }
      }
    }
  }
}





static uint8_t legalCoordinates(uint64_t x, uint64_t y) {
  if (x>=WIDTH || y >= HEIGHT || x < 0 || y < 0){
		return 0;
	}
  return 1;
}

#endif
