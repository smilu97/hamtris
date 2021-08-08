#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>

#include <asio.hpp>

#include "room.h"
#include "player.h"

using namespace asio::ip;

namespace tetris {
    
    class TetrisServer {
        std::vector<TetrisRoomPtr> rooms;
        std::vector<TetrisPlayerPtr> players;

        tcp::acceptor acceptor;
    public:
        TetrisServer(asio::io_service& io_context, tcp::endpoint& endpoint);
        void Accept();
    };

}

#endif
