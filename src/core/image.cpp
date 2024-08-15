#include "image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

image::image(int width, double aspect_ratio)
    : image_width(width),
      image_height(int(image_width / aspect_ratio)),
      aspect_ratio(aspect_ratio)
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
double image::get_aspect_ratio() const { return aspect_ratio; }

int image::offset(int x, int y) const { return y * image_width + x; }

void image::set_pixel(int x, int y, const color &c) { pixels[offset(x, y)] = c; }

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
            const color &c = pixels[y * image_width + x];
            write_color(file, c);
        }
    }
}

void image::write_to_file_png(const std::string &filename) const
{
    assert(!filename.empty());
    assert(filename.find(".png") != std::string::npos);

    std::vector<unsigned char> data(image_width * image_height * 3);

    for (int y = image_height - 1; y >= 0; --y)
    {
        for (int x = 0; x < image_width; ++x)
        {
            const color &c = pixels[y * image_width + x];
            int index = offset(x, y) * 3;
            data[index + 0] = static_cast<unsigned char>(255.999 * c.r());
            data[index + 1] = static_cast<unsigned char>(255.999 * c.g());
            data[index + 2] = static_cast<unsigned char>(255.999 * c.b());
        }
    }

    stbi_write_png(filename.c_str(), image_width, image_height, 3, data.data(), 0);

    std::cout << "Image saved to " << filename << std::endl;
}
