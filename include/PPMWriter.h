#ifndef PPMWRITER_H_
#define PPMWRITER_H_

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

#include "Vector3.h"
#include "constants.h"

using uint = unsigned int;

class PPMWriter {
  private:
    std::ofstream outfile;
    uint pixels_written;
    uint image_width, image_height;

  public:
    PPMWriter(const std::string& filename, const uint iw, const uint ih)
        : pixels_written(0), image_width(iw), image_height(ih) {

        outfile.open(filename, std::ofstream::out);
        if (!outfile.is_open()) {
            std::cerr << "COULD NOT OPEN THE PPM FILE FOR WRITING. EXITING.\n";
            exit(EXIT_FAILURE);
        }
        outfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    }

    ~PPMWriter() { outfile.close(); }

    void write_color(const Color3& color, const uint samples_per_pixel) {
        if (!(pixels_written < image_height * image_width)) return;

        double r = color.x;
        double g = color.y;
        double b = color.z;

        double scale = 1.0 / samples_per_pixel;
        r = std::clamp(std::sqrt(r * scale), 0.0, 0.999);
        g = std::clamp(std::sqrt(g * scale), 0.0, 0.999);
        b = std::clamp(std::sqrt(b * scale), 0.0, 0.999);

        outfile << static_cast<int>(PPM_COLOR_SCALING * r) << ' '
                << static_cast<int>(PPM_COLOR_SCALING * g) << ' '
                << static_cast<int>(PPM_COLOR_SCALING * b) << '\n';
    }
};

#endif