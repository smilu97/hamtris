#ifndef __GAME_H__
#define __GAME_H__

#include "tetris.h"

namespace tetris {
    class TetrisGame {
        Tetris tetris;
        int stepTimerCount;
        bool gameOver;

        void TimerThreadFunc();
        void InputThreadFunc();
        void ResetTimer();
        void Render();
    public:
        void Run();
    };
}

#endif
