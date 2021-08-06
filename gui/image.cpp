#include "image.h"

#include <png.h>
#include <cstdlib>
#include <cstdarg>
#include <cstring>

void Abort(const char * s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

// ref: http://zarb.org/~gc/html/libpng.html
PngImage ReadPngFile(const char* file_name)
{
    PngImage image;
    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp)
        Abort("[read_png_file] File %s could not be opened for reading", file_name);
    fread(header, 1, 8, fp);
    if (png_sig_cmp((png_const_bytep) header, 0, 8))
        Abort("[read_png_file] File %s is not recognized as a PNG file", file_name);


    /* initialize stuff */
    image.png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image.png_ptr)
        Abort("[read_png_file] png_create_read_struct failed");

    image.info_ptr = png_create_info_struct(image.png_ptr);
    if (!image.info_ptr)
        Abort("[read_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(image.png_ptr)))
        Abort("[read_png_file] Error during init_io");

    png_init_io(image.png_ptr, fp);
    png_set_sig_bytes(image.png_ptr, 8);

    png_read_info(image.png_ptr, image.info_ptr);

    image.width = png_get_image_width(image.png_ptr, image.info_ptr);
    image.height = png_get_image_height(image.png_ptr, image.info_ptr);
    image.color_type = png_get_color_type(image.png_ptr, image.info_ptr);
    image.bit_depth = png_get_bit_depth(image.png_ptr, image.info_ptr);

    image.number_of_passes = png_set_interlace_handling(image.png_ptr);
    png_read_update_info(image.png_ptr, image.info_ptr);


    /* read file */
    if (setjmp(png_jmpbuf(image.png_ptr)))
        Abort("[read_png_file] Error during read_image");

    image.row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * image.height);
    uint row_sz = png_get_rowbytes(image.png_ptr,image.info_ptr);
    for (int y=0; y < image.height; y++) {
        image.row_pointers[y] = (png_byte*) malloc(row_sz);
    }

    png_read_image(image.png_ptr, image.row_pointers);

    image.data = (png_bytep) malloc(row_sz * image.height);
    for (int y = 0; y < image.height; y++) {
        memcpy(image.data + y * row_sz, image.row_pointers[y], row_sz);
    }

    image.row_sz = row_sz;

    fclose(fp);

    return image;
}

void FreePngImage(const PngImage * image) {
    for (int y = 0; y < image->height; y++) {
        free(image->row_pointers[y]);
    }
    free(image->row_pointers);
    free(image->data);
}
