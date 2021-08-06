#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <png.h>

struct PngImage {
    int width, height;
    int x, y;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    int row_sz;
    png_bytep * row_pointers;
    png_bytep data;
};

void Abort(const char * s, ...);

PngImage ReadPngFile(const char* file_name);

void FreePngImage(const PngImage * image);

#endif
