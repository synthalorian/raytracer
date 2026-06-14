#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class camera {
public:
    camera(double aspect_ratio = 16.0 / 9.0, int image_width = 400,
           int samples_per_pixel = 100, int max_depth = 50,
           double vfov = 20, point3 lookfrom = point3(-2,2,1),
           point3 lookat = point3(0,0,-1), vec3 vup = vec3(0,1,0),
           double defocus_angle = 0, double focus_dist = 10) {
        auto image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2 * h * focus_dist;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = viewport_width * u;
        vertical = viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

        auto defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle / 2));
        defocus_disk_u = u * defocus_radius;
        defocus_disk_v = v * defocus_radius;
    }

    ray get_ray(int i, int j) const {
        auto pixel_center = lower_left_corner + (i * horizontal) + (j * vertical);
        auto pixel_sample = pixel_center + pixel_sample_square();

        auto ray_origin = (defocus_angle <= 0) ? origin : defocus_disk_sample();
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    vec3 defocus_disk_u;
    vec3 defocus_disk_v;
    double defocus_angle;

    static double degrees_to_radians(double degrees) {
        return degrees * pi / 180.0;
    }

    static double pi;

    vec3 pixel_sample_square() const {
        auto px = -0.5 + random_double();
        auto py = -0.5 + random_double();
        return (px * horizontal) + (py * vertical);
    }

    point3 defocus_disk_sample() const {
        auto p = random_in_unit_disk();
        return origin + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }
};

double camera::pi = 3.1415926535897932385;

#endif