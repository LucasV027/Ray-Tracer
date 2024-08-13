#include "image.h"

image::image(int width, int height)
    : image_width(width), image_height(height)
{
    pixels = new color[image_width * image_height]{};
}

image::~image()
{
    delete[] pixels;
}

int image::width() const { return image_width; }
int image::height() const { return image_height; }

void image::set_pixel(int x, int y, const color &c) { pixels[y * image_width + x] = c; }

void image::write_to_file(const char *filename)
{
    (void)filename;
    // TODO: Implement this function
}
