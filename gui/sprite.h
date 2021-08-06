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

    void Load(const char* filename, GLint format, float alpha);
    void Draw(float x, float y, float w, float h, float tx, float ty, float tw, float th) const;

    int GetWidth() const { return image.width; }
    int GetHeight() const { return image.height; }
};

#endif
