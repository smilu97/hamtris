#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <utility>
#include <asio.hpp>

#include "message.h"

using namespace asio::ip;

namespace tetris {

    class TetrisPlayer {
        PlayerId id;
        tcp::socket socket;
    public:
        TetrisPlayer(tcp::socket socket);

        void Deliver(const TetrisMessage & msg);
    };

    typedef std::shared_ptr<TetrisPlayer> TetrisPlayerPtr;
}

#endif
