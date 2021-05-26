#ifndef TIME_DRIVER
#define TIME_DRIVER

#include <stdint.h>
#include <timeDriver.h>

static uint64_t ticks = 0;

void timeHandler() {
  ticks++;
}

uint64_t getTicks() {
  return ticks;
}

int secondsElapsed() {
	return ticks / 18;
}

#endif
