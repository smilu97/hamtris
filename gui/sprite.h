#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "image.h"

#include <GL/glut.h>
class SpriteSheet {
    PngImage image;
    GLuint texture;
public:
    SpriteSheet();
    ~SpriteSheet();

    void Load(const char* filename, float alpha);
    void Draw(float x, float y, float w, float h, float tx, float ty, float tw, float th) const;
};

#endif
