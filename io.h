// ref: https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
 
void PrepareKbhit() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
}

int kbhit(void)
{
    int ch = getchar();
 
    if(ch != EOF)
    {
      ungetc(ch, stdin);
      return 1;
    }
  
    return 0;
}

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
