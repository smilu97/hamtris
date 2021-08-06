#include "sprite.h"
#include "image.h"

#include <GL/glut.h>

SpriteSheet::SpriteSheet() {
}

SpriteSheet::~SpriteSheet() {
    FreePngImage(&image);
}

void SpriteSheet::Load(const char* filename) {
    image = ReadPngFile(filename);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    glEnable(GL_TEXTURE_2D);
}

void SpriteSheet::Draw(float x, float y, float w, float h, float tx, float ty, float tw, float th) const {
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
    glTexCoord2f(tx, ty);
    glVertex2f(x, y);
    glTexCoord2f(tx+tw, ty);
    glVertex2f(x+w, y); 
    glTexCoord2f(tx+tw, ty+th);
    glVertex2f(x+w, y+h);
    glTexCoord2f(tx, ty+th);
    glVertex2f(x, y+h); 
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}
