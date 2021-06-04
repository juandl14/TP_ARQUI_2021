#ifndef SHELLS
#define SHELLS
#include <stdGraphics.h>
#include <colors.h>
#include <stdint.h>
#include <stdio.h>
#include <Shells.h>

#define TOTAL_LINES 63
#define MAX_LINE_LENGTH 65
void updateShell(char * buff, int dim);
void writeToLines(char * buff, int dim);
void changeActiveShell();
void addLine();
void keyPressedShell(char ch);
static void clearShellLine(int line);
static void drawShell0Lines();
static void drawBottomLine();
static void clearScreenLine(uint8_t line);

static char lines[2][TOTAL_LINES][MAX_LINE_LENGTH];
static char lines0[TOTAL_LINES][MAX_LINE_LENGTH];
static char lines1[TOTAL_LINES][MAX_LINE_LENGTH];
static int currentLine[] = {0, 0};
static int lineCursor[] = {0, 0};
static int activeShell = 0;

void init_shell() {
  for (int i = 0; i < TOTAL_LINES; i++) {
    for (int j = 0; j < TOTAL_LINES; j++) {
      lines[0][i][j] = 0;
      lines[1][i][j] = 0;
    }
  }
  setConsoleUpdateFunction(updateShell);
  writeToLines("Hola\nLa Mexicana con tremendo flow\n", 37);
  drawShellLines();

  while(1) {
    char ch = getChar();
    keyPressedShell(ch);
  }
}

void writeToLines(char * buff, int dim) {
  for (int i = 0; i < dim && buff[i] != 0 && i < MAX_LINE_LENGTH; i++) {
    if (buff[i] == '\n' || lineCursor[activeShell] == (MAX_LINE_LENGTH - 3)) { //El -3 es para que el ultimo elemento sea un 0 y no toma en cuanta los "> "
      if (lineCursor[activeShell] > 0) {
        addLine();
      }
    } else if (buff[i] == '\b' && lineCursor[activeShell] > 0) {
      lines[activeShell][currentLine[activeShell] % (TOTAL_LINES-1)][lineCursor[activeShell]-1] = lines[activeShell][currentLine[activeShell] % (TOTAL_LINES-1)][lineCursor[activeShell]];
      lineCursor[activeShell]-=lineCursor[activeShell]==0?0:1; //TODO ver si se puede mejorar
    } else {
      lines[activeShell][currentLine[activeShell] % (TOTAL_LINES-1)][lineCursor[activeShell]] = buff[i];
      lineCursor[activeShell]++;
    }
  }
  drawBottomLine();
  return;
}

void changeActiveShell() {
  if (activeShell == 0) {
    activeShell = 1;
    return;
  }
  activeShell = 0;
}

void updateShell(char * buff, int dim) {
  writeToLines(buff, dim);
}

void addLine() {
  currentLine[activeShell]++;
  clearShellLine(currentLine[activeShell]);
  lineCursor[activeShell] = 0;
  drawShellLines();
}

static void clearShellLine(int line) {
  for (int i = 0; i < MAX_LINE_LENGTH; i++) {
    lines[activeShell][line%(TOTAL_LINES-1)][i] = 0;
  }
}


void drawShellLines() {
  if (activeShell == 0) {
    drawShell0Lines();
  }
}

static void drawShell0Lines() {
  drawRect(0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, 0x5151A0);
  int y = SCREEN_HEIGHT;
  int x = 0;
  for (int i = 0; i >= -TOTAL_LINES && i >= -currentLine[0]; i--) {
    y-=BASE_CHAR_HEIGHT;
    if (i == 0) {
      drawString(0, y, "> ", 3, WHITE, BUTTERFLY_BUSH, 1, 0);
      x += BASE_CHAR_WIDTH*2;
    } else {
      x = 0;
    }
    if (lines[0][(i+currentLine[0])%(TOTAL_LINES-1)][0] == 0) continue;
    drawString(x, y, lines[0][(i+currentLine[0])%(TOTAL_LINES-1)], MAX_LINE_LENGTH-1, WHITE, BUTTERFLY_BUSH, 1, 0);
  }
}

static void clearScreenLine(uint8_t line){
  int x = 0;
  int color = BUTTERFLY_BUSH;
  if (activeShell == 1) {
    x = SCREEN_WIDTH/2 + 1;
    color = BLACK;
  }
  drawRect(x,SCREEN_HEIGHT-BASE_CHAR_HEIGHT*(line+1),SCREEN_WIDTH/2,BASE_CHAR_HEIGHT, color);
}

static void drawBottomLine() {
  clearScreenLine(0);
  int x = 0;
  int bkgColor = BUTTERFLY_BUSH;
  int fontColor = WHITE;
  if (activeShell == 1) {
    x = SCREEN_WIDTH/2 + 1;
    bkgColor = BLACK;
    fontColor = LIGHT_GRAY;
  }
  drawString(x, SCREEN_HEIGHT-BASE_CHAR_HEIGHT, "> ", 3, fontColor, bkgColor, 1, 0);
  drawString(x + BASE_CHAR_WIDTH*2, SCREEN_HEIGHT-BASE_CHAR_HEIGHT, lines[activeShell][(currentLine[activeShell])%(TOTAL_LINES-1)], MAX_LINE_LENGTH-1, fontColor, bkgColor, 1, 0);
}

void keyPressedShell(char ch) {
  if (ch) {
    // if (ch == '\n' && lineCursor > 0) {
    //   exeCommand(lines[(currentLineNumber)%(TOTAL_LINES-1)]);
    // }
    putChar(ch);
  }
}

#endif
