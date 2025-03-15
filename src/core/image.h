#pragma once

#include <string>
#include <cstdint>

#include "utils/color.h"

class image {
public:
    image();
    image(unsigned int width, double aspect_ratio);
    ~image();

    unsigned int width() const;
    unsigned int height() const;
    double get_aspect_ratio() const;
    uint8_t* get_pixels() const;
    color get_pixel(unsigned int x, unsigned int y) const;

    void set_pixel(unsigned int x, unsigned int y, const color& c) const;
    void set_pixel(unsigned int x, unsigned int y, const color& c, int samples) const;

    void clear(const color& c) const;
    void write_to_file(const std::string& filename) const;

private:
    bool write_to_file_ppm(const std::string& filename) const;
    bool write_to_file_png(const std::string& filename) const;
    unsigned int offset(unsigned int x, unsigned int y) const;

private:
    unsigned int image_width;
    unsigned int image_height;
    double aspect_ratio;
    uint8_t* pixels;
};
