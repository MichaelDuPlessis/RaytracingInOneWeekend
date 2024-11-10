#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "rtweekend.h"
#include "vec3.h"

class camera {
public:
  double aspect_ratio = 1.0;
  int image_width = 100;
  int samples_per_pixel = 10;
  int max_depth = 10;

  void render(const hittable &world) {
    initialize();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
      std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
                << std::flush;
      for (int i = 0; i < image_width; i++) {
        color pixel_color(0, 0, 0);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, max_depth, world);
        }
        write_color(std::cout, pixel_samples_scale * pixel_color);
      }
    }

    std::clog << "\rDone.                 \n";
  }

private:
  int image_height;
  double pixel_samples_scale;
  point3 center;
  point3 pixel00_loc;
  vec3 pixel_delta_u;
  vec3 pixel_delta_v;

  void initialize() {
    // calculate image height from width and aspect ratio
    image_height = int(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    // color scale factor for sum of pixel samples
    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = point3(0, 0, 0);

    // camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width =
        viewport_height * (double(image_width) / image_height);

    // viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // delta vectors
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // location of upper left pixel
    auto viewport_upper_left =
        center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc =
        viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  ray get_ray(int i, int j) const {
    // Create a camera ray from the origin to a randomly sampled point around some locatoin i,j

    auto offset = sample_square();
    auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
  }

  vec3 sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }

  color ray_color(const ray &r, int depth, const hittable &world) {
    if (depth <= 0) {
      return color(0, 0, 0);
    }
     
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
      vec3 direction = random_on_hemisphere(rec.normal);
      return 0.5 * ray_color((ray(rec.p, direction)), depth - 1, world);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
};

#endif