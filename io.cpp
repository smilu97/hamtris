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
