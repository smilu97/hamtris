#ifndef __MESSAGE_H__
#define __MESSAGE_H__

namespace tetris {

    struct Id {
        int value;
    public:
        Id(int value);
        Id next() const;
        bool operator==(const Id& other) const;
        bool operator<(const Id& other) const;
    };

    typedef Id PlayerId;
    typedef Id RoomId;

    enum MessageType {
        MESSAGE_TETRIS = 100,

        MESSAGE_CREATE_ROOM = 200,
        MESSAGE_JOIN_ROOM,
    };

    struct HeaderMessage {
        MessageType type;
    };
    
    enum TetrisAction {
        TETRIS_ACTION_LEFT = 100,
        TETRIS_ACTION_RIGHT,
        TETRIS_ACTION_ROTATE,
        TETRIS_ACTION_DOWN,
        TETRIS_ACTION_UNROTATE,
        TETRIS_ACTION_SWAP,
        TETRIS_ACTION_HARDDROP,

        TETRIS_ACTION_START_GAME = 200,
        TETRIS_ACTION_DROP_ALL,
    };

    struct TetrisMessage {
        PlayerId source;
        TetrisAction action;
        TetrisMessage(PlayerId source, TetrisAction action);
    };

    struct JoinRoomMessage {
        int roomId;
    };
}

#endif
