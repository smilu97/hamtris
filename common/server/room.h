#ifndef __ROOM_H__
#define __ROOM_H__

#include <vector>
#include <utility>

#include "player.h"

namespace tetris {

    class TetrisRoom {
        std::vector<TetrisPlayerPtr> players;
        bool playing;
    public:
        void AddPlayer(TetrisPlayerPtr player);
        void Broadcast(const TetrisMessage & message);

        void Play();

        bool GetPlaying();
    };

    typedef std::shared_ptr<TetrisRoom> TetrisRoomPtr;
}

#endif
