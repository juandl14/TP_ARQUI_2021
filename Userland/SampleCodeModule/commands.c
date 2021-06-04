#include <stdio.h>
#include <commands.h>
#include <stdlib.h>
#include <stdGraphics.h>
#include <time.h>
// #include <inforeg.h>
// #include <Shells.h>
#include <stdint.h>
#include <syscalls_asm.h>
// #include <forcedExceptions.h>

void dateTime(char args[MAX_ARGS][MAX_ARG_LEN]) {
    putChar('\n');
    printf("%d:%d:%d %d/%d/%d", getHours(), getMinutes(), getSeconds(), getDays(), getMonth(), getYear());
}
