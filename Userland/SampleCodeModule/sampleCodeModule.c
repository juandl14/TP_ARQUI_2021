/* sampleCodeModule.c */

// includes de prueba
#include <syscalls_asm.h>
#include <colors.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	// init_shell();
	clearDisplaySyscall(0xFFFFFF);
	return 0;
}
