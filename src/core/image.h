#pragma once

#include <fstream>

#include "utils/color.h"

class image
{
public:
    image(int width, int height);
    ~image();

    int width() const;
    int height() const;

    void set_pixel(int x, int y, const color &c);
    void write_to_file(const char *filename);

private:
    int image_width = 256;
    int image_height = 256;
    color *pixels;
};
