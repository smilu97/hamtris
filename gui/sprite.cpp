#include "sprite.h"
#include "image.h"

SpriteSheet::SpriteSheet(const char* filename) {
    image = ReadPngFile("./static/sprite.png");

    printf("sprite width: %d\n", image.width);
    printf("sprite row size: %d\n", image.row_sz);
    printf("sprite bit depth: %d\n", image.bit_depth);

    // ref: https://stackoverflow.com/questions/30488155/opengl-fastest-way-to-draw-2d-image

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0,
    //          GL_RGBA, GL_UNSIGNED_BYTE, image.data);
    
    // // One time during setup.
    // GLuint readFboId = 0;
    // glGenFramebuffers(1, &readFboId);
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
    // glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
    //                     GL_TEXTURE_2D, tex, 0);
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    // // Every time you want to copy the texture to the default framebuffer.
    
}

SpriteSheet::~SpriteSheet() {
    FreePngImage(&image);
}

void SpriteSheet::Draw() const {
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
    // glBlitFramebuffer(0, 0, texWidth, texHeight,
    //                 0, 0, winWidth, winHeight,
    //                 GL_COLOR_BUFFER_BIT, GL_LINEAR);
    // glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}
