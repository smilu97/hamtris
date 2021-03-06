#include "game.h"
#include "shape.h"

#include <cstdio>
#include <GL/glut.h>

TetrisGame::TetrisGame():
    stepTimeThreshold(1000),
    screenWidth(600.f),
    screenHeight(600.f),
    boxSize(50) {

}

TetrisGame::~TetrisGame() {
    
}

void TetrisGame::Init(int * argc, char ** argv,
    DisplayFunc displayFunc,
    UpdateFunc updateFunc,
    KeyboardFunc keyboardFunc,
    SpecialFunc specialFunc
) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tetris");

    blockSprite.Load("./static/sprite.png", GL_RGBA, 1.0f);
    shadowSprite.Load("./static/sprite.png", GL_RGBA, 0.5f);
    backgroundSprite.Load("./static/underwater.png", GL_RGB, 1.0f);

    glutDisplayFunc(displayFunc);
    glutTimerFunc(0, updateFunc, 0);
    glutKeyboardFunc(keyboardFunc);
    glutSpecialFunc(specialFunc);
    glutMainLoop();
}

void TetrisGame::Update() {
    int dt = GetDt();

    StepTimer(dt);
}

void TetrisGame::Render() {
    glClear(GL_COLOR_BUFFER_BIT);

    const float bgZoomOut = 2.0;
    const float bgWidth = screenWidth / (float) backgroundSprite.GetWidth() / 2 * bgZoomOut;
    const float bgHeight = screenHeight / (float) backgroundSprite.GetHeight() / 2 * bgZoomOut;
    backgroundSprite.Draw(-1, -1, 2, 2, 0.5-bgWidth, 0.5-bgHeight, 2*bgWidth, 2*bgHeight);
    
    for (int i = 1; i <= 22; i++) {
        DrawTetriminoBox(WALL_TETRIMINO, i, 6);
        DrawTetriminoBox(WALL_TETRIMINO, i, 17);
    }
    for (int i = 7; i <= 16; i++) {
        DrawTetriminoBox(WALL_TETRIMINO, 1, i);
        DrawTetriminoBox(WALL_TETRIMINO, 22, i);
    }

    auto view = tetris.GetBoardView();
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (view[i][j] != 0) {
                DrawTetriminoBox(view[i][j], i+2, j+7);
            }
        }
    }

    auto queue = tetris.GetQueue();
    for (int i = 0; i < 5; i++) {
        TetriminoType type = queue[i];
        DrawTetrimino(type, (i << 2) + 1, 19);
    }

    auto swap = tetris.GetSwap();
    if (swap != BOARD_EMPTY) {
        DrawTetrimino(swap, 2, 1);
    }

    glFlush();
    glutSwapBuffers();
}

void TetrisGame::OnKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'z':
            tetris.Rotate(false);
            break;
        case 'c':
            tetris.Swap();
            break;
        case ' ':
            tetris.HardDrop();
            break;
    }
}

void TetrisGame::OnSpecial(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT:
            tetris.Move(false);
            break; 
        case GLUT_KEY_RIGHT:
            tetris.Move(true);
            break;
        case GLUT_KEY_UP:
            tetris.Rotate(true);
            break; 
        case GLUT_KEY_DOWN:
            tetris.Drop();
            stepTimer = 0;
            break;
    }
}

int TetrisGame::GetDt() {
    int time = glutGet(GLUT_ELAPSED_TIME);
    int dt = time - oldTime;
    oldTime = time;
    return dt;
}

bool TetrisGame::StepTimer(int dt) {
    stepTimer += dt;
    if (stepTimer > stepTimeThreshold) {
        stepTimer -= stepTimeThreshold;
        tetris.Step();
        return true;
    }
    return false;
}

void TetrisGame::DrawTetriminoBox(TetriminoType type, int x, int y) {
    float boxWidth = boxSize / screenWidth;
    float boxHeight = boxSize / screenHeight;
    float gl_x1 = -1.0 + y * boxWidth;
    float gl_y1 = 1.0 - (x+1) * boxHeight;
    (type >= I_TETRIMINO_SHADOW && type <= O_TETRIMINO_SHADOW ? shadowSprite : blockSprite)
        .Draw(gl_x1, gl_y1, boxWidth, boxHeight, tetrimino_sprite_x[type]/512.,4./512.,36./512.,36./512.);
}

void TetrisGame::DrawTetrimino(TetriminoType type, int x, int y) {
    auto shape = tetris.GetTetriminoShape(type);
    for (int i = 0; i < sz_tetrimino_shape; i++) {
        for (int j = 0; j < sz_tetrimino_shape; j++) {
            if (shape[i][j] == 0) continue;
            DrawTetriminoBox(type, x + i, y + j);
        }
    }
}
