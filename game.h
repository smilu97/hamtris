#ifndef __GAME_H__
#define __GAME_H__

#include "tetris.h"
#include "screen.h"

namespace tetris {
    class TetrisGame {
        Tetris tetris;
        Screen screen;
        int stepTimerCount;
        bool gameOver;

        void TimerThreadFunc();
        void InputThreadFunc();
        void ResetTimer();
        void Render();
    public:
        TetrisGame();
        ~TetrisGame();

        void Run();
    };
}

#endif
