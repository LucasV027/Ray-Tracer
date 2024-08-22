#include "image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

image::image()
    : image_width(0),
      image_height(0),
      aspect_ratio(0),
      pixels(nullptr)
{
}

image::image(int width, double aspect_ratio)
    : image_width(width),
      image_height(int(image_width / aspect_ratio)),
      aspect_ratio(aspect_ratio)
{
    assert(image_width > 0);
    assert(image_height > 0);
    pixels = new uint8_t[image_width * image_height * 4]{};
}

image::~image()
{
    delete[] pixels;
}

int image::width() const { return image_width; }
int image::height() const { return image_height; }
double image::get_aspect_ratio() const { return aspect_ratio; }

int image::offset(int x, int y) const { return (y * image_width + x) * 4; }

void image::set_pixel(int x, int y, const color &c)
{
    pixels[offset(x, y) + 0] = static_cast<unsigned char>(255.999 * c.r());
    pixels[offset(x, y) + 1] = static_cast<unsigned char>(255.999 * c.g());
    pixels[offset(x, y) + 2] = static_cast<unsigned char>(255.999 * c.b());
    pixels[offset(x, y) + 3] = 255;
}
color image::get_pixel(int x, int y) const
{
    double r = pixels[offset(x, y) + 0] / 255.0;
    double g = pixels[offset(x, y) + 1] / 255.0;
    double b = pixels[offset(x, y) + 2] / 255.0;

    return color{r, g, b};
}

uint8_t *image::get_pixels() const { return pixels; }

void image::write_to_file_ppm(const std::string &filename) const
{
    assert(!filename.empty());
    assert(filename.find(".ppm") != std::string::npos);

    std::ofstream file(filename, std::ios::binary);

    file << "P3\n"
         << image_width << ' ' << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y)
    {
        for (int x = 0; x < image_width; ++x)
        {
            const color &c = get_pixel(x, y);

            file << int(255.999 * c.r()) << ' ' << int(255.999 * c.g()) << ' ' << int(255.999 * c.b()) << '\n';
        }
    }
}

void image::write_to_file_png(const std::string &filename) const
{
    assert(!filename.empty());
    assert(filename.find(".png") != std::string::npos);

    stbi_write_png(filename.c_str(), image_width, image_height, 4, pixels, 0);

    std::cout << "Image saved to " << filename << std::endl;
}
