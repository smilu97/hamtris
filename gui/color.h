#ifndef __COLOR_H__
#define __COLOR_H__

const float tetrimino_colors[][3] = {
    {0.0, 0.0, 0.0}, // BOARD_EMPTY

    {0.0, 1.0, 1.0}, // I_TETRIMINO CYAN
    {0.0, 0.0, 1.0}, // J_TETRIMINO BLUE
    {1.0, 0.647, 0.0}, // L_TETRIMINO ORANGE
    {0.0, 1.0, 0.0}, // S_TETRIMINO GREEN
    {0.56, 0.0, 1.0}, // T_TETRIMINO VIOLET
    {1.0, 0.0, 0.0}, // Z_TETRIMINO RED
    {1.0, 1.0, 0.0}, // O_TETRIMINO YELLOW
    
    {0.0, 0.5, 0.5}, // I_TETRIMINO_SHADOW
    {0.0, 0.0, 0.5}, // J_TETRIMINO_SHADOW
    {0.5, 0.32, 0.0}, // L_TETRIMINO_SHADOW
    {0.0, 0.5, 0.0}, // S_TETRIMINO_SHADOW
    {0.28, 0.0, 0.5}, // T_TETRIMINO_SHADOW
    {0.5, 0.0, 0.0}, // Z_TETRIMINO_SHADOW
    {0.5, 0.5, 0.0}, // O_TETRIMINO_SHADOW
    
    {0.2, 0.2, 0.2}, // WALL_TETRIMINO
};

const float tetrimino_sprite_x[] = {
    312.0,

    268.0,
    92.0,
    136.0,
    4.0,
    180.0,
    48.0,
    224.0,

    268.0,
    92.0,
    136.0,
    4.0,
    180.0,
    48.0,
    224.0,

    312.0,
};

#endif
