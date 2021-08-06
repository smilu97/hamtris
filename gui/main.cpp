#include "game.h"

#include <GL/glut.h>

TetrisGame g_game;

void displayFunc(void) {
    g_game.Render();
}

void timerFunc(int value) {
    g_game.Update();
    glutPostRedisplay();
    glutTimerFunc(10, timerFunc, 0);
}

void keyboardFunc(unsigned char key, int x, int y) {
    g_game.OnKeyboard(key, x, y);
}

void specialFunc(int key, int x, int y) {
    g_game.OnSpecial(key, x, y);
}

int main(int argc, char** argv)
{
    g_game.Init(&argc, argv,
        displayFunc,
        timerFunc,
        keyboardFunc,
        specialFunc
    );
    return 0;
}
