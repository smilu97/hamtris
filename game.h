#ifndef __GAME_H__
#define __GAME_H__

#include "tetris.h"
#include "screen.h"

#include <mutex>
namespace tetris {
    class TetrisGame {
        std::mutex mtx;
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
