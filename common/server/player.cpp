#include "player.h"

using namespace tetris;

TetrisPlayer::TetrisPlayer(tcp::socket socket):
    socket (std::move(socket)) {

}

void TetrisPlayer::Deliver(const TetrisMessage & msg) {
    
}
