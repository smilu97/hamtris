#include "game.h"
#include "shape.h"
#include "io.h"

#include <iostream>
#include <termio.h>
#include <thread>

using namespace tetris;

Color TetriminoTypeToColor(TetriminoType type) {
    if (type == BOARD_EMPTY) return COLOR_RESET;
    if (type == I_TETRIMINO) return COLOR_CYAN;
    if (type == J_TETRIMINO) return COLOR_BLUE;
    if (type == L_TETRIMINO) return COLOR_ORANGE;
    if (type == S_TETRIMINO) return COLOR_GREEN;
    if (type == T_TETRIMINO) return COLOR_VIOLET;
    if (type == Z_TETRIMINO) return COLOR_RED;
    if (type == O_TETRIMINO) return COLOR_YELLOW;
    if (type == I_TETRIMINO_SHADOW) return COLOR_CYAN_DARK;
    if (type == J_TETRIMINO_SHADOW) return COLOR_BLUE_DARK;
    if (type == L_TETRIMINO_SHADOW) return COLOR_ORANGE_DARK;
    if (type == S_TETRIMINO_SHADOW) return COLOR_GREEN_DARK;
    if (type == T_TETRIMINO_SHADOW) return COLOR_VIOLET_DARK;
    if (type == Z_TETRIMINO_SHADOW) return COLOR_RED_DARK;
    if (type == O_TETRIMINO_SHADOW) return COLOR_YELLOW_DARK;
    return COLOR_RESET;
}

TetrisGame::TetrisGame():
    screen(22, 60),
    stepTimerCount(0),
    gameOver(false) {

}

TetrisGame::~TetrisGame() {

}

void TetrisGame::Run() {
    PrepareInput();
    Render();

    ResetTimer();
    std::thread th_input(&TetrisGame::InputThreadFunc, this);
    std::thread th_timer(&TetrisGame::TimerThreadFunc, this);

    th_input.join();
    th_timer.join();
}

void TetrisGame::TimerThreadFunc() {
    while (true) {
        if (gameOver) break;

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        stepTimerCount--;
        if (stepTimerCount <= 0) {
            ResetTimer();
            mtx.lock();
            if (false == tetris.Step()) {
                gameOver = true;
                break;
            }
            Render();
            mtx.unlock();
        }
    }
}

void TetrisGame::InputThreadFunc() {
    while (true) {
        int ch = getchar();
        
        mtx.lock();
        switch (ch) {
            case 27:
                if (getchar() == 91) {
                    int b = getchar();
                    if (b == 65) { // up
                        tetris.Rotate(true);
                    } else if (b == 66) { // right
                        if (tetris.Drop()) {
                            ResetTimer();
                        }
                    } else if (b == 67) { // down
                        tetris.Move(true);
                    } else if (b == 68) { // left
                        tetris.Move(false);
                    }
                }
                break;
            case 122: // z
                tetris.Rotate(false);
                break;
            case 99: // c
                tetris.Swap();
                break;
            case 32: // space
                if (false == tetris.HardDrop()) {
                    gameOver = true;
                    break;
                }
                break;
        }
        Render();
        mtx.unlock();
    }
}

void TetrisGame::ResetTimer() {
    stepTimerCount = 100;
}

void TetrisGame::Render() {
    screen.Reset();

    const int swapOffsetX = 0;
    const int swapOffsetY = 0;

    const int boardOffsetX = 0;
    const int boardOffsetY = swapOffsetY + 10;

    const int queueOffsetX = 0;
    const int queueOffsetY = boardOffsetY + 26;

    const int scoreOffsetX = 21;
    const int scoreOffsetY = boardOffsetY + 25;

    TetriminoType swap = tetris.GetSwap();
    auto swapShape = tetris.GetTetriminoShape(swap);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (swapShape[i][j] == 0) continue;
            screen.DrawBox(TetriminoTypeToColor(swap), swapOffsetX + i, swapOffsetY + (j << 1));
        }
    }

    for (int i = 0; i < BOARD_WIDTH + 2; i++) {
        screen.DrawBox(COLOR_BLACK, boardOffsetX, boardOffsetY + (i << 1));
        screen.DrawBox(COLOR_BLACK, boardOffsetX + 21, boardOffsetY + (i << 1));
    }
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        screen.DrawBox(COLOR_BLACK, boardOffsetX + i + 1, boardOffsetY);
        screen.DrawBox(COLOR_BLACK, boardOffsetX + i + 1, boardOffsetY + ((BOARD_WIDTH + 1) << 1));
    }

    tetris::Board view = tetris.GetBoardView();

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            screen.DrawBox(TetriminoTypeToColor(view[i][j]), boardOffsetX + i + 1, boardOffsetY + ((j + 1) << 1));
        }
    }

    const tetris::TetriminoQueue& queue = tetris.GetQueue();

    for (int k = 0; k < 4; k++) {
        const int * shape = tetrimino_shapes[queue[k]-1][0];
        for (int i = 0; i < sz_tetrimino_shape; i++) {
            for (int j = 0; j < sz_tetrimino_shape; j++) {
                if (!shape[i*sz_tetrimino_shape+j]) continue;
                screen.DrawBox(TetriminoTypeToColor(queue[k]), queueOffsetX + k*4 + i, queueOffsetY + (j << 1));
            }
        }
    }

    screen.DrawString(COLOR_RESET, scoreOffsetX, scoreOffsetY, "SCORE: " + std::to_string(tetris.GetScore()));
    
    screen.Render();
}
