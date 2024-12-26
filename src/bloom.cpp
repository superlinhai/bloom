#include <iostream>
#include <ostream>
#include <sys/types.h>

int main(){


  uint image_width {256};
  uint image_height {256};

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int y{0}; y < image_height; y++) {
    std::clog << "\rScaling remaining: " << (image_height - y) << ' ' << std::flush;
    for (int x{0}; x < image_width; x++) {

      // Calculate the color of the pixels.
      double r = double(x) / (image_width-1);
      double g = double(y) / (image_height-1);
      double b = 0.0;

      uint ir = int(255.999 * r);
      uint ig = int(255.999 * g);
      uint ib = int(255.999 * b);

      std::cout << ir << "  " << ig << "  " << ib << '\n';
    }
  }
    std::clog << "Done!\n";
}
