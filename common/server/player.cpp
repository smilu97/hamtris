#include "player.h"

using namespace tetris;

TetrisPlayer::TetrisPlayer(PlayerId id, tcp::socket socket):
    id(id),
    socket (std::move(socket)) {
    
}

void TetrisPlayer::Start() {
    ReadHeader();
}

void TetrisPlayer::Deliver(const char* buf, int len) {
    socket.async_write_some(boost::asio::buffer(buf, len), [this](std::error_code err, std::size_t){
        if (err) {
            return;
        }
        return;
    });
}

void TetrisPlayer::ReadMessage(int len, ReadHandler readHandler) {
    socket.async_read_some(boost::asio::buffer(readBuffer, len), readHandler);
}

void TetrisPlayer::ReadHeader() {
    ReadMessage(sizeof(HeaderMessage), [this](std::error_code err, std::size_t) {
        if (err) {
            return;
        } else {
            HeaderMessage * msg = (HeaderMessage*) readBuffer;
            switch (msg->type) {
                case MESSAGE_TETRIS:
                    ReadTetrisMessage();
                    break;
                case MESSAGE_CREATE_ROOM:
                    CreateRoom();
                    break;
                case MESSAGE_JOIN_ROOM:
                    ReadJoinRoomMessage();
                    break;
            }
        }
    });
}

void TetrisPlayer::ReadTetrisMessage() {

}

void TetrisPlayer::ReadJoinRoomMessage() {

}

void TetrisPlayer::CreateRoom() {

}
