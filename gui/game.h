#ifndef __GAME_H__
#define __GAME_H__

#include "tetris.h"
#include "color.h"
#include "image.h"
#include "sprite.h"

using namespace tetris;

typedef void (*DisplayFunc)();
typedef void (*UpdateFunc)(int);
typedef void (*KeyboardFunc)(unsigned char, int, int);
typedef void (*SpecialFunc)(int, int ,int);

class TetrisGame {
    Tetris tetris;

    float screenWidth, screenHeight;

    int boxSize;

    int oldTime;
    int stepTimer;
    int stepTimeThreshold;

    SpriteSheet blockSprite;
    SpriteSheet shadowSprite;

    int GetDt(); // Get delta time in milliseconds
    bool StepTimer(int dt);

    void DrawTetriminoBox(TetriminoType type, int x, int y);
    void DrawTetrimino(TetriminoType type, int x, int y);
public:
    TetrisGame();
    ~TetrisGame();
    void Init(int * argc, char ** argv,
        DisplayFunc displayFunc,
        UpdateFunc updateFunc,
        KeyboardFunc keyboardFunc,
        SpecialFunc specialFunc
    );

    void Update();
    void Render();
    void OnKeyboard(unsigned char key, int x, int y);
    void OnSpecial(int key, int x, int y);
};

#endif
