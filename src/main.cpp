#include <iostream>

#include "core/image.h"

int main(void)
{
    image img(256, 256);

    for (int j = 0; j < img.height(); j++)
    {
        std::clog << "\rScanlines remaining: " << (img.height() - j) << ' ' << std::flush;
        for (int i = 0; i < img.width(); i++)
        {
            auto pixel_color = color(double(i) / (img.width() - 1), double(j) / (img.height() - 1), 0);
            img.set_pixel(i, j, pixel_color);
        }
    }

    std::clog << "\rDone.                 \n";
}
