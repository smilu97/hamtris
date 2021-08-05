#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
 
void PrepareInput();

enum Color {
  COLOR_RESET = 0,
  COLOR_GRAY = 7,
  COLOR_RED = 9,
  COLOR_GREEN = 10,
  COLOR_YELLOW = 11,
  COLOR_BLUE = 12,
  COLOR_VIOLET = 13,
  COLOR_CYAN = 14,
  COLOR_ORANGE = 202,
  COLOR_BLACK = 232,
};

void switchForeground(Color color);

void switchBackground(Color color);

void switchForeBackground(Color color);

#endif
