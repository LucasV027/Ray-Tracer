#include "image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <fstream>
#include <cassert>
#include <vector>

image::image() :
    image_width(0),
    image_height(0),
    aspect_ratio(0),
    pixels(nullptr) {
}

image::image(const unsigned int width, const double aspect_ratio) :
    image_width(width),
    image_height(static_cast<unsigned int>(image_width / aspect_ratio)),
    aspect_ratio(aspect_ratio) {
    assert(image_width > 0);
    assert(image_height > 0);
    pixels = new uint8_t[image_width * image_height * 4]{};
}

image::~image() {
    delete[] pixels;
}

unsigned int image::width() const { return image_width; }
unsigned int image::height() const { return image_height; }
double image::get_aspect_ratio() const { return aspect_ratio; }
uint8_t* image::get_pixels() const { return pixels; }

void image::set_pixel(unsigned int x, unsigned int y, const color& c) const {
    pixels[offset(x, y) + 0] = static_cast<unsigned char>(255.999 * c.r());
    pixels[offset(x, y) + 1] = static_cast<unsigned char>(255.999 * c.g());
    pixels[offset(x, y) + 2] = static_cast<unsigned char>(255.999 * c.b());
    pixels[offset(x, y) + 3] = 255;
}

void image::set_pixel(const unsigned int x, const unsigned int y, const color& c, const int samples) const {
    if (samples == 0) {
        set_pixel(x, y, c);
    } else {
        const auto actual = get_pixel(x, y);
        const auto new_mean = (actual * samples + c) / (samples + 1);
        set_pixel(x, y, new_mean);
    }
}

color image::get_pixel(unsigned int x, unsigned int y) const {
    const double r = pixels[offset(x, y) + 0] / 255.0;
    const double g = pixels[offset(x, y) + 1] / 255.0;
    const double b = pixels[offset(x, y) + 2] / 255.0;

    return color{r, g, b};
}

void image::clear(const color& c) const {
    for (unsigned int y = 0; y < image_height; ++y) {
        for (unsigned int x = 0; x < image_width; ++x) {
            set_pixel(x, y, c);
        }
    }
}

void image::write_to_file(const std::string& filename) const {
    bool sucess = false;
    if (filename.find(".ppm") != std::string::npos) {
        sucess = write_to_file_ppm(filename);
    } else if (filename.find(".png") != std::string::npos) {
        sucess = write_to_file_png(filename);
    } else {
        std::cerr << "Cannot write to file " << filename << ". Unsupported file format." << std::endl;
        return;
    }

    if (sucess)
        std::cout << "Image saved to " << filename << std::endl;
}

bool image::write_to_file_ppm(const std::string& filename) const {
    assert(!filename.empty());
    assert(filename.find(".ppm") != std::string::npos);

    std::ofstream file(filename, std::ios::binary);

    file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int y = static_cast<int>(image_height) - 1; y >= 0; --y) {
        for (unsigned int x = 0; x < image_width; ++x) {
            const color& c = get_pixel(x, y);

            file << static_cast<int>(255.999 * c.r()) << ' '
                << static_cast<int>(255.999 * c.g()) << ' '
                << static_cast<int>(255.999 * c.b()) << '\n';
        }
    }

    file.close();
    return true;
}

bool image::write_to_file_png(const std::string& filename) const {
    assert(!filename.empty());
    assert(filename.find(".png") != std::string::npos);

    stbi_write_png(filename.c_str(), static_cast<int>(image_width), static_cast<int>(image_height), 4, pixels, 0);
    return true;

}

unsigned int image::offset(const unsigned int x, const unsigned int y) const { return (y * image_width + x) * 4; }
