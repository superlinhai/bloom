#pragma once

#include "vec3.h"
#include <iostream>

using color = vec3;

inline void write_color(std::ostream &out, const color &pixel_color) {
  double r{pixel_color.x()};
  double g{pixel_color.y()};
  double b{pixel_color.z()};

  // Convert from the range [0, 1] to [0, 255]
  // We multiply by 255.9999 instead of 255.0 in order to avoid rounding errors
  // where values close to 1 such as 0.999 are rounded to 254 instead of 255.

  int rbyte = int(255.9999 * r);
  int gbyte = int(255.9999 * g);
  int bbyte = int(255.9999 * b);

  out << rbyte << " " << gbyte << " " << bbyte << '\n';
}
