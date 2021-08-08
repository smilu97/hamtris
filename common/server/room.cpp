#include "room.h"

using namespace tetris;

void TetrisRoom::AddPlayer(TetrisPlayerPtr player) {
    players.push_back(player);
}

void TetrisRoom::Broadcast(const TetrisMessage & message) {
    for (auto player: players) {
        player->Deliver(message);
    }
}

void TetrisRoom::Play() {
    for (auto player: players) {
        player->alive = true;
    }

    TetrisMessage startMessage(PlayerId(0), TETRIS_ACTION_START_GAME);
    Broadcast(startMessage);
}
        
bool TetrisRoom::GetPlaying() {
    return playing;
}
