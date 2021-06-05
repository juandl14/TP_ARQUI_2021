#ifndef STD_IO_H
#define STD_IO_H value

void printf(char * fmt, ...);
void setConsoleUpdateFunction(void (*f)(char *, int));
void putChar(char ch);
void setFunctionKey(int index, void(*func)());
char getChar();

#endif
