#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <png.h>

int x, y;

struct PngImage {
    int width, height;
    png_byte color_type;
    png_byte bit_depth;

    png_structp png_ptr;
    png_infop info_ptr;
    int number_of_passes;
    png_bytep * row_pointers;
};

void abort_(const char * s, ...);

PngImage read_png_file(char* file_name);

#endif
