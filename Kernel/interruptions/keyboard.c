#include <keyboard.h>
#include <./../include/naiveConsole.h>
void keyboard_handler() {
    unsigned int key = _getKey();
    // aca podría hacer un mapeo, desp en el tpe lo haremos
    ncPrintHex(key);
    return;
}