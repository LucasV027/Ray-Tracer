#pragma once

#include <fstream>
#include <cassert>

#include "utils/color.h"

class image
{
public:
    image(int width, double aspect_ratio);
    ~image();

    int width() const;
    int height() const;

    void set_pixel(int x, int y, const color &c);
    void write_to_file(const char *filename);

private:
    int image_width;
    int image_height;
    color *pixels;
};
