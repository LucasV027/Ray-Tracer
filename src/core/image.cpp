#include "image.h"

#ifdef LIB_STB_IMAGE_WRITE
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#endif

image::image()
    : image_width(0),
      image_height(0),
      aspect_ratio(0),
      pixels(nullptr) {
}

image::image(int width, double aspect_ratio)
    : image_width(width),
      image_height(int(image_width / aspect_ratio)),
      aspect_ratio(aspect_ratio) {
    assert(image_width > 0);
    assert(image_height > 0);
    pixels = new uint8_t[image_width * image_height * 4]{};
}

image::~image() {
    delete[] pixels;
}

int image::width() const { return image_width; }
int image::height() const { return image_height; }
double image::get_aspect_ratio() const { return aspect_ratio; }
uint8_t *image::get_pixels() const { return pixels; }

void image::set_pixel(int x, int y, const color &c) {
    pixels[offset(x, y) + 0] = static_cast<unsigned char>(255.999 * c.r());
    pixels[offset(x, y) + 1] = static_cast<unsigned char>(255.999 * c.g());
    pixels[offset(x, y) + 2] = static_cast<unsigned char>(255.999 * c.b());
    pixels[offset(x, y) + 3] = 255;
}

void image::set_pixel(int x, int y, const color &c, int samples) {
    if (samples == 0) {
        set_pixel(x, y, c);
    } else {
        auto actual = get_pixel(x, y);
        auto new_mean = (actual * samples + c) / (samples + 1);
        set_pixel(x, y, new_mean);
    }
}

color image::get_pixel(int x, int y) const {
    double r = pixels[offset(x, y) + 0] / 255.0;
    double g = pixels[offset(x, y) + 1] / 255.0;
    double b = pixels[offset(x, y) + 2] / 255.0;

    return color{r, g, b};
}

void image::clear(const color &c) {
    for (int y = 0; y < image_height; ++y) {
        for (int x = 0; x < image_width; ++x) {
            set_pixel(x, y, c);
        }
    }
}

void image::write_to_file(const std::string &filename) const {
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

bool image::write_to_file_ppm(const std::string &filename) const {
    assert(!filename.empty());
    assert(filename.find(".ppm") != std::string::npos);

    std::ofstream file(filename, std::ios::binary);

    file << "P3\n"
            << image_width << ' ' << image_height << "\n255\n";

    for (int y = image_height - 1; y >= 0; --y) {
        for (int x = 0; x < image_width; ++x) {
            const color &c = get_pixel(x, y);

            file << int(255.999 * c.r()) << ' ' << int(255.999 * c.g()) << ' ' << int(255.999 * c.b()) << '\n';
        }
    }

    file.close();
    return true;
}

bool image::write_to_file_png(const std::string &filename) const {
#ifdef LIB_STB_IMAGE_WRITE
    assert(!filename.empty());
    assert(filename.find(".png") != std::string::npos);

    stbi_write_png(filename.c_str(), image_width, image_height, 4, pixels, 0);
    return true;
#else
    std::cout << "Cannot write to file " << filename << ". STB_IMAGE_WRITE is not enable in Cmake config." << std::endl;
    return false;
#endif
}

int image::offset(int x, int y) const { return (y * image_width + x) * 4; }
