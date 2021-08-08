#include "message.h"

using namespace tetris;

Id::Id(int value): value(value) {}

Id Id::next() const {
    return Id(value + 1);
}

bool Id::operator==(const Id& other) const { return value == other.value; }
bool Id::operator<(const Id& other) const { return value < other.value; }

TetrisMessage::TetrisMessage(PlayerId source, TetrisAction action):
    source(source),
    action(action) {

}

