#include "player.h"

using namespace tetris;

TetrisPlayer::TetrisPlayer(PlayerId id, tcp::socket socket):
    id(id),
    socket (std::move(socket)) {

}

void TetrisPlayer::Deliver(const TetrisMessage & msg) {
    
}
