#include "io.h"

// ref: https://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
void PrepareInput() {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
}

void switchForeground(Color color) {
  if (color == COLOR_RESET) {
    printf("\e[0m");
    return;
  }

  printf("\e[38;5;%dm", (int) color);
}

void switchBackground(Color color) {
  if (color == COLOR_RESET) {
    printf("\e[0m");
    return;
  }
  
  printf("\e[48;5;%dm", (int) color);
}

void switchForeBackground(Color color) {
  switchForeground(color);
  switchBackground(color);
}

Color ToDarkColor(Color color) {
  if (color == COLOR_RED) return COLOR_RED_DARK;
  if (color == COLOR_GREEN) return COLOR_GREEN_DARK;
  if (color == COLOR_YELLOW) return COLOR_YELLOW_DARK;
  if (color == COLOR_BLUE) return COLOR_BLUE_DARK;
  if (color == COLOR_VIOLET) return COLOR_VIOLET_DARK;
  if (color == COLOR_CYAN) return COLOR_CYAN_DARK;
  if (color == COLOR_ORANGE) return COLOR_ORANGE_DARK;
  
  return COLOR_RESET;
}
