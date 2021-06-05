#include <stdio.h>
#include <commands.h>
#include <stdlib.h>
#include <stdGraphics.h>
#include <time.h>
#include <inforeg.h>
// #include <Shells.h>
#include <stdint.h>
#include <syscalls_asm.h>
// #include <forcedExceptions.h>

void dateTime(char args[MAX_ARGS][MAX_ARG_LEN]) {
    putChar('\n');
    printf("%d:%d:%d %d/%d/%d", getHours(), getMinutes(), getSeconds(), getDays(), getMonth(), getYear());
}

// void help(char args[MAX_ARGS][MAX_ARG_LEN])

void infoReg(char args[MAX_ARGS][MAX_ARG_LEN]) {
    uint64_t registers[19];
    getRegisters(registers);
    putChar('\n');
    printf("R15: %X - R14: %X\n", registers[18], registers[17]);
    printf("R13: %X - R12: %X\n", registers[16], registers[15]);
    printf("R11: %X - R10: %X\n", registers[14], registers[13]);
    printf("R9: %X - R8: %X\n", registers[12], registers[11]);
    printf("RSI: %X - RDI: %X\n", registers[10], registers[9]);
    printf("RBP: %X - RDX: %X\n", registers[8], registers[7]);
    printf("RCX: %X - RBX: %X\n", registers[6], registers[5]);
    printf("RAX: %X - RIP: %X\n", registers[4], registers[3]);
    printf("CS: %X - FLAGS: %X\n", registers[2], registers[1]);
    printf("RSP: %X\n", registers[0]);
}
