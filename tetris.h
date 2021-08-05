#ifndef __TETRIS_H__
#define __TETRIS_H__

#include <vector>
#include <deque>

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

enum TetriminoType {
    BOARD_EMPTY = 0,
    I_TETRIMINO = 1,
    J_TETRIMINO = 2,
    L_TETRIMINO = 3,
    S_TETRIMINO = 4,
    T_TETRIMINO = 5,
    Z_TETRIMINO = 6,
    O_TETRIMINO = 7,
    SHADOW_BLOCK = 8,
};

namespace tetris {
    struct Tetrimino {
        int x, y;
        int rot; // 0-3
        TetriminoType type;
        Tetrimino(): x(0), y(0), rot(0), type(BOARD_EMPTY) {}
        Tetrimino(int x, int y, int rot, TetriminoType type): x(x),y(y),rot(rot),type(type) {}
    };

    typedef std::vector< std::vector<TetriminoType> > Board;
    typedef std::deque<TetriminoType> TetriminoQueue;

    class Tetris {
        Board board;
        TetriminoQueue queue; // queue of next tetriminos
        Tetrimino currTetrimino;
        TetriminoType swap;
        bool swappable;

        static void Materialize(Board & targetBoard, const Tetrimino & tetrimino);

        void AddBatchInQueue();
        bool Move(int dx, int dy, int rot);
        bool CheckCollision(int x, int y, int rot, TetriminoType type) const;        
        bool GoNextTetrimino();
        TetriminoType PopQueue();
        int RemoveFullLines();
        bool IsFullLine(int x) const;
        bool TryWallKick(int dx, int dy, int d_rot);

    public:
        Tetris();
        ~Tetris();
        bool Drop();
        bool Rotate(bool);
        bool Step();
        bool Move(bool);
        bool Swap();
        bool HardDrop();

        const TetriminoQueue& GetQueue() const { return queue; }
        const Board GetBoardView() const;
        std::vector< std::pair<int, int> > GetShadow() const;
    };
}

#endif
