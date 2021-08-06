#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "image.h"

class SpriteSheet {
    PngImage image;
public:
    SpriteSheet(const char* filename);
    ~SpriteSheet();

    void Draw() const;
};

#endif
