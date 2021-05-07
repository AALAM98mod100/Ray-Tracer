#include <iostream>

#include "vec3.h"
#include "color.h"
#include "ray.h"

color ray_color(const ray &r)
{
    vec3 dir_hat = unit_vector(r.direction());
    float t = 0.5 * (dir_hat.y() + 1.0);
    return (1.0 - t) * color(1, 1.0, 1) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    // Image
    const float aspect_ratio = 16 / 9;
    const int height = 400;
    const int width = static_cast<int>(height * aspect_ratio);
    ;

    // Camera
    float viewport_height = 2.0;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0;

    point3 origin = point3(0, 0, 0);
    vec3 camera_x = vec3(viewport_width, 0, 0);
    vec3 camera_y = vec3(0, viewport_height, 0);
    vec3 bottom_left_corner = origin - camera_x / 2 - camera_y / 2 - vec3(0, 0, focal_length);
    // std::cout << "#BLC = " << bottom_left_corner << '\n';
    //Render

    std::cout << "P3\n"
              << width << " " << height << "\n255\n";

    for (int j = height - 1; j >= 0; --j)
    {
        fprintf(stderr, "\rScanlines remaining: %d", j);
        for (int i = 0; i < width; ++i)
        {
            auto u = double(i) / (width - 1);
            auto v = double(j) / (height - 1);
            bottom_left_corner = origin - camera_x / 2 - camera_y / 2 - vec3(0, 0, focal_length);
            ray r(origin, bottom_left_corner + u * camera_x + v * camera_y - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    // std::cout << "#BLC = " << bottom_left_corner << '\n';
    fprintf(stderr, "\nDone\n");
}