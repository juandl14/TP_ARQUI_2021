#ifndef STD_IO
#define STD_IO

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include <syscalls_asm.h>
#include <stdGraphics.h>

#define PRINTF_BUFFER_SIZE 128
#define STD_BUFFER_SIZE 256

char std_in[STD_BUFFER_SIZE] = {0};
char std_out[STD_BUFFER_SIZE] = {0};
static char std_io_initialized = 0;
static char buffered_std_out = 1;

void stdio_init() {
    if(!std_io_initialized)
    std_io_initialized = 1;
}

// Arreglar
int printf(char * fmt, ...) {
    va_list varList;
    int i = 0;
    int j = 0;
    char printBuffer[PRINTF_BUFFER_SIZE] = {0};
    // char tmpBuffer[32];

    while(fmt && fmt[i]) {
        printBuffer[j] = fmt[i];
        i++;
        j++;
    }

    int index;
    for(index = 0; printBuffer[j] != 0 && index < j && index < PRINTF_BUFFER_SIZE; index++) {
        std_out[index] = printBuffer[j];
    }
    std_out[index] = 0;
    if(index != 0) {
        buffered_std_out = 1;
    }
}

int readKeyboard(char * buffer, int size) {
    if(size == 0)
        return 0;
    uint64_t aux;
    isKeyboardEmptySyscall(&aux);
    if(aux) {
        readKeyboardSysCall(buffer, (uint8_t) size);
        return 1;
    }
}


#endif
