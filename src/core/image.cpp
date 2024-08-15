#include "image.h"

image::image(int width, double aspect_ratio)
    : image_width(width), image_height(int(image_width / aspect_ratio))
{
    assert(image_width > 0);
    assert(image_height > 0);
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
    std::ofstream file(filename, std::ios::binary);

    file << "P3\n"
         << image_width << ' ' << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y)
    {
        for (int x = 0; x < image_width; ++x)
        {
            const color &c = pixels[y * image_width + x];
            write_color(file, c);
        }
    }
}
