#pragma once

#include <fstream>
#include <cassert>
#include <string>
#include <vector>

#include "utils/color.h"

class image
{
public:
    image(int width, double aspect_ratio);
    ~image();

    int width() const;
    int height() const;
    double get_aspect_ratio() const;

    int offset(int x, int y) const;

    void set_pixel(int x, int y, const color &c);

    void write_to_file_ppm(const std::string &filename) const;
    void write_to_file_png(const std::string &filename) const;

private:
    int image_width;
    int image_height;
    double aspect_ratio;
    color *pixels;
};
