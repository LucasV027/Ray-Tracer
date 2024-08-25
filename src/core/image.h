#pragma once

#include <fstream>
#include <cassert>
#include <string>
#include <vector>
#include <stdint.h>

#include "utils/color.h"

class image
{
public:
    image();
    image(int width, double aspect_ratio);
    ~image();

    int width() const;
    int height() const;
    double get_aspect_ratio() const;
    uint8_t *get_pixels() const;

    void set_pixel(int x, int y, const color &c);
    void set_pixel(int x, int y, const color &c, int samples);
    color get_pixel(int x, int y) const;

    void clear(const color &c);

    void write_to_file(const std::string &filename) const;

private:
    void write_to_file_ppm(const std::string &filename) const;
    void write_to_file_png(const std::string &filename) const;
    int offset(int x, int y) const;

private:
    int image_width;
    int image_height;
    double aspect_ratio;
    uint8_t *pixels;
};
