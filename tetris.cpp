#include "tetris.h"
#include "shape.h"

#include <algorithm>
#include <numeric>
#include <ctime>

using namespace tetris;

Tetris::Tetris(): board(BOARD_HEIGHT), swappable(true), swap(BOARD_EMPTY), score(0) {
    std::srand(std::time(0));

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        board[i] = std::vector<TetriminoType>(BOARD_WIDTH, BOARD_EMPTY);
    }
    
    // Initialize queue with random piece
    // Queue must be maintained to have more than 6 pieces
    AddBatchInQueue(); // Push 7 pieces in queue
    AddBatchInQueue();

    GoNextTetrimino(); // Pop the very first tetrimino of this game
}

/**
 * Add random batch of 7 pieces to the queue
 */
void Tetris::AddBatchInQueue() {
    std::vector<TetriminoType> batch(7);
    
    batch[0] = I_TETRIMINO;
    batch[1] = J_TETRIMINO;
    batch[2] = L_TETRIMINO;
    batch[3] = S_TETRIMINO;
    batch[4] = T_TETRIMINO;
    batch[5] = Z_TETRIMINO;
    batch[6] = O_TETRIMINO;
    
    std::random_shuffle(batch.begin(), batch.end());

    for (TetriminoType piece: batch)
        queue.push_back(piece);
}

/**
 * Move currTetrimino to desired direction
 */
bool Tetris::Move(int dx, int dy, int d_rot) {
    int x = currTetrimino.x + dx, y = currTetrimino.y + dy;
    int rot = (currTetrimino.rot + d_rot) % 4;
    
    if (CheckCollision(x, y, rot, currTetrimino.type)) {
        return false;
    }

    currTetrimino.x = x;
    currTetrimino.y = y;
    currTetrimino.rot = rot;

    return true;
}

/**
 * Materialize currTetrimino to board
 */
void Tetris::Materialize(Board & targetBoard, const Tetrimino & tetrimino) {
    const int x = tetrimino.x, y = tetrimino.y, rot = tetrimino.rot;
    const TetriminoType type = tetrimino.type;
    const int sz = sz_tetrimino_shape;
    const int * shape = tetrimino_shapes[type - 1][rot];
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if (shape[i*sz + j] == 0) continue;
            int tx = x + i, ty = y + j;
            targetBoard[tx][ty] = type;
        }
    }
}

bool Tetris::CheckCollision(int x, int y, int rot, TetriminoType type) const {
    if (type == 0) {
        return false;
    }

    const int sz = sz_tetrimino_shape;
    const int * shape = tetrimino_shapes[type - 1][rot];
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            if (shape[i*sz + j] == 0) continue;
            int tx = x + i, ty = y + j;
            if (tx < 0 || ty < 0 || tx >= BOARD_HEIGHT || ty >= BOARD_WIDTH)
                return true;
            if (board[tx][ty] != BOARD_EMPTY)
                return true;
        }
    }

    return false;
}

void Tetris::AddScore(int numRemovedLines) {
    if (numRemovedLines == 4) {
        score += 80;
    } else {
        score += 10 * numRemovedLines;
    }
}

bool Tetris::GoNextTetrimino() {
    AddScore(RemoveFullLines());

    TetriminoType nextType = PopQueue();

    const int ix = 0, iy = 3, irot = 0;
    if (CheckCollision(ix, iy, irot, nextType)) {
        return false;
    }

    currTetrimino = Tetrimino(ix, iy, irot, nextType);
    swappable = true;
    return true;
}

TetriminoType Tetris::PopQueue() {
    TetriminoType type = queue[0];
    queue.pop_front();
    if (queue.size() < 7) {
        AddBatchInQueue();
    }
    return type;
}

int Tetris::RemoveFullLines() {
    int lines = 0;
    for (int i = BOARD_HEIGHT - 1; i >= 0; i--) {
        if (IsFullLine(i)) {
            lines++;
        } else {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                board[i+lines][j] = board[i][j];
            }
        }
    }
    return lines;
}

bool Tetris::IsFullLine(int x) const {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (board[x][i] == BOARD_EMPTY)
            return false;
    }
    return true;
}

Tetris::~Tetris() {

}

bool Tetris::Drop() {
    return Move(1, 0, 0);
}

bool Tetris::TryWallKick(int dx, int dy, int d_rot) {
    int x = currTetrimino.x, y = currTetrimino.y, rot = currTetrimino.rot;
    TetriminoType type = currTetrimino.type;
    if (CheckCollision(x + dx, y + dy, (rot + d_rot) % 4, type)) return false;
    Move(dx, dy, d_rot);
    return true;
}

bool Tetris::Rotate(bool cw) {
    const int d_rot = cw ? 1 : 3;
    const TetriminoType type = currTetrimino.type;
    
    if (TryWallKick(0,  0, d_rot)) return true;

    if (type == O_TETRIMINO) return false;

    if (TryWallKick( 0,  1, d_rot)) return true;
    if (TryWallKick( 1,  1, d_rot)) return true;
    if (TryWallKick(-1,  1, d_rot)) return true;
    if (TryWallKick( 0,  2, d_rot)) return true;
    if (TryWallKick( 0, -1, d_rot)) return true;
    if (TryWallKick( 1, -1, d_rot)) return true;
    if (TryWallKick(-1, -1, d_rot)) return true;
    if (TryWallKick( 0, -2, d_rot)) return true;

    return false;
}

bool Tetris::Step() {
    if (Drop()) return true;

    Materialize(board, currTetrimino);

    return GoNextTetrimino();
}

bool Tetris::Move(bool right) {
    return Move(0, right ? 1 : -1, 0);
}

bool Tetris::Swap() {
    if (!swappable) return false;
    swappable = false;

    if (swap == 0) {
        swap = PopQueue();
    }
    
    const int ix = 0, iy = 3, irot = 0;
    TetriminoType currType = currTetrimino.type;
    currTetrimino = Tetrimino(ix, iy, irot, swap);
    swap = currType;

    return true;
}

bool Tetris::HardDrop() {
    while (Drop());

    Materialize(board, currTetrimino);

    return GoNextTetrimino();
}

const Board Tetris::GetBoardView() const {
    Board boardView(board);

    std::vector< std::pair<int, int> > shadow = GetShadow();
    for (std::pair<int, int> coord: shadow) {
        boardView[coord.first][coord.second] = SHADOW_BLOCK;
    }

    Materialize(boardView, currTetrimino);

    return boardView;
}

std::vector< std::pair<int, int> > Tetris::GetShadow() const {
    std::vector< std::pair<int, int> > shadow;

    int x = currTetrimino.x, y = currTetrimino.y, rot = currTetrimino.rot;
    TetriminoType type = currTetrimino.type;

    while (!CheckCollision(x, y, rot, type)) ++x;
    --x;

    for (int i = 0; i < sz_tetrimino_shape; i++) {
        for (int j = 0; j < sz_tetrimino_shape; j++) {
            if (tetrimino_shapes[type - 1][rot][i*sz_tetrimino_shape + j] == 0) continue;
            shadow.push_back(std::make_pair(x + i, y + j));
        }
    }

    return shadow;
}
