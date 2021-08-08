#ifndef __ROOM_H__
#define __ROOM_H__

#include <vector>
#include <utility>

#include "player.h"

namespace tetris {

    class TetrisRoom {
        std::vector<TetrisPlayerPtr> players;
    public:
        void AddPlayer(TetrisPlayerPtr player);
        void Broadcast(TetrisMessage & message);
    };

    typedef std::shared_ptr<TetrisRoom> TetrisRoomPtr;
}

#endif
