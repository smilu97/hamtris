#include "message.h"

using namespace tetris;

PlayerId::PlayerId(int value): value(value) {}

PlayerId PlayerId::next() const {
    return PlayerId(value + 1);
}

TetrisMessage::TetrisMessage(PlayerId source, TetrisAction action):
    source(source),
    action(action) {

}

