#include "room.h"

using namespace tetris;

void TetrisRoom::AddPlayer(TetrisPlayerPtr player) {
    players.push_back(player);
}

void TetrisRoom::Broadcast(const char * buf, int len) {
    for (auto player: players) {
        player->Deliver(buf, len);
    }
}

void TetrisRoom::Play() {
    for (auto player: players) {
        player->alive = true;
    }

    TetrisMessage startMessage(PlayerId(0), TETRIS_ACTION_START_GAME);
    Broadcast((const char*) &startMessage, sizeof(TetrisMessage));
}
        
bool TetrisRoom::GetPlaying() {
    return playing;
}
