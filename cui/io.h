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

  COLOR_RED_DARK = 52,
  COLOR_GREEN_DARK = 22,
  COLOR_YELLOW_DARK = 94,
  COLOR_BLUE_DARK = 4,
  COLOR_VIOLET_DARK = 5,
  COLOR_CYAN_DARK = 6,
  COLOR_ORANGE_DARK = 130,

  COLOR_BLACK = 232,
};

Color ToDarkColor(Color color);

void switchForeground(Color color);

void switchBackground(Color color);

void switchForeBackground(Color color);

#endif
