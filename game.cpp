#include "game.h"
#include "shape.h"

#include <iostream>
#include <termio.h>
#include <thread>

using namespace tetris;

void PrepareSystem() {
    PrepareKbhit();
}

Color TetriminoTypeToColor(TetriminoType type) {
    if (type == BOARD_EMPTY) return COLOR_RESET;
    if (type == I_TETRIMINO) return COLOR_CYAN;
    if (type == J_TETRIMINO) return COLOR_BLUE;
    if (type == L_TETRIMINO) return COLOR_ORANGE;
    if (type == S_TETRIMINO) return COLOR_GREEN;
    if (type == T_TETRIMINO) return COLOR_VIOLET;
    if (type == Z_TETRIMINO) return COLOR_RED;
    if (type == O_TETRIMINO) return COLOR_YELLOW;
    if (type == SHADOW_BLOCK) return COLOR_GRAY;
    return COLOR_RESET;
}

TetrisGame::TetrisGame():
    screen(22, 34),
    stepTimerCount(0),
    gameOver(false) {

}

TetrisGame::~TetrisGame() {

}

void TetrisGame::Run() {
    PrepareSystem();
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
            if (false == tetris.Step()) {
                gameOver = true;
                break;
            }
            Render();
        }
    }
}

void TetrisGame::InputThreadFunc() {
    while (true) {
        if (kbhit() == false) {
            if (gameOver) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(15));
            continue;
        }

        int ch = getchar();
        
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
    }
}

void TetrisGame::ResetTimer() {
    stepTimerCount = 100;
}

void TetrisGame::Render() {
    screen.Reset();

    for (int i = 0; i < BOARD_WIDTH + 2; i++) {
        screen.DrawBox(COLOR_BLACK, 0, i << 1);
        screen.DrawBox(COLOR_BLACK, 21, i << 1);
    }
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        screen.DrawBox(COLOR_BLACK, i + 1, 0);
        screen.DrawBox(COLOR_BLACK, i + 1, (BOARD_WIDTH + 1) << 1);
    }

    tetris::Board view = tetris.GetBoardView();

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            screen.DrawBox(TetriminoTypeToColor(view[i][j]), i + 1, (j + 1) << 1);
        }
    }

    const tetris::TetriminoQueue& queue = tetris.GetQueue();

    for (int k = 0; k < 4; k++) {
        const int * shape = tetrimino_shapes[queue[k]-1][0];
        for (int i = 0; i < sz_tetrimino_shape; i++) {
            for (int j = 0; j < sz_tetrimino_shape; j++) {
                if (!shape[i*sz_tetrimino_shape+j]) continue;
                screen.DrawBox(TetriminoTypeToColor(queue[k]), k*4 + i, (13 + j) << 1);
            }
        }
    }
    
    screen.Render();
}
