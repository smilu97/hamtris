#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <utility>
#include <asio.hpp>

#include "message.h"

using namespace asio::ip;

namespace tetris {

    typedef std::function<void(std::error_code, std::size_t)> ReadHandler;

    class TetrisPlayer: std::enable_shared_from_this<TetrisPlayer> {
        PlayerId id;
        tcp::socket socket;
        
        char readBuffer[128];

        void ReadMessage(int len, ReadHandler readHandler);

        void ReadHeader();
        void ReadTetrisMessage();
        void ReadJoinRoomMessage();

        void CreateRoom();

    public:
        TetrisPlayer(PlayerId id, tcp::socket socket);

        void Start();

        void Deliver(const char* buf, int len);
        bool alive;
    };

    typedef std::shared_ptr<TetrisPlayer> TetrisPlayerPtr;
}

#endif
