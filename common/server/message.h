#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "player.h"

namespace tetris {
    typedef int PlayerId;
    
    enum TetrisAction {
        TETRIS_ACTION_LEFT = 100,
        TETRIS_ACTION_RIGHT,
        TETRIS_ACTION_ROTATE,
        TETRIS_ACTION_DOWN,
        TETRIS_ACTION_UNROTATE,
        TETRIS_ACTION_SWAP,
        TETRIS_ACTION_HARDDROP,

        TETRIS_ACTION_START_GAME = 200,
    };

    struct TetrisMessage {
        PlayerId source;
        TetrisAction action;
    };
}

#endif
