#ifndef __SERVER_H__
#define __SERVER_H__

#include <vector>

#include <boost/asio.hpp>

#include "room.h"
#include "player.h"

using boost::asio::ip::tcp;

namespace tetris {
    
    class TetrisServer {
        std::vector<TetrisRoomPtr> rooms;
        std::vector<TetrisPlayerPtr> players;

        tcp::acceptor acceptor;

        PlayerId latestPlayerId;
        PlayerId AllocPlayerId();
    public:
        TetrisServer(boost::asio::io_service& io_context, tcp::endpoint& endpoint);
        void Accept();
    };

}

#endif
