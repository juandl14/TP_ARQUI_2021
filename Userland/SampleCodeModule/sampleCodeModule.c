/* sampleCodeModule.c */

// includes de prueba
#include <syscalls_asm.h>
#include <colors.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	// init_shell();
	// clearScreen(0xFFFFFF);
	// drawString(0, 0, "Hola", 4, 0xFFFFFF, 0x000000, 1, 0);
	// drawRect(2, 2, 5, 5, 0xFFFFFF);
	return 0;
}
