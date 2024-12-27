#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <iostream>
#include <ostream>
#include <sys/types.h>

color ray_color(const ray &r) {
  vec3 unit_direction{unit_vector(r.direction())};
  double a{0.5 * (unit_direction.y() + 1.0)};
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
  double const aspect_ratio{16.0 / 9.0};
  uint image_width{256};

  // Ensure that the image height is at least one.
  uint image_height{uint(image_width / aspect_ratio)};
  image_height = image_height < 1 ? 1 : image_height;

  // Viewport
  double viewport_height{2.0};
  double viewport_width{viewport_height * (double(image_width) / image_height)};

  // Camera
  double focal_length{1.0};
  point3 camera_center{0, 0, 0};

  // Calculate the vectors across the viewport.
  vec3 viewport_u{viewport_width, 0, 0};
  vec3 viewport_v{0, -viewport_height, 0};

  // Calculate the horizontal and vertical delta from pixel to pixel.
  vec3 pixel_delta_u{viewport_u / image_width};
  vec3 pixel_delta_v{viewport_v / image_height};

  // Calculate the location of the upper left pixel.
  vec3 viewport_upper_left{camera_center - vec3(0, 0, focal_length) -
                           viewport_u / 2 - viewport_v / 2};
  vec3 pixel00_loc{viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v)};

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int y{0}; y < image_height; y++) {
    std::clog << "\rScaling remaining: " << (image_height - y) << ' '
              << std::flush;
    for (int x{0}; x < image_width; x++) {
      vec3 pixel_center{pixel00_loc + (x * pixel_delta_u) +
                        (y * pixel_delta_v)};
      vec3 ray_direction{pixel_center - camera_center};

      ray r(camera_center, ray_direction);
      color pixel_color{ray_color(r)};

      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "Done!\n";
}
