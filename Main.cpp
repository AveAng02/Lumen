
#include <cmath>
#include <iostream>


#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "Pass.h"



int main()
{
    // Scene objects
    lumen::SPHERE sp1(lumen::point3(-1, 0, -2), 1, lumen::color(1,0,0), "RED_SPHERE");

    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);


    // Camera
    // Camera position = (0,0,0)
    auto origin = lumen::point3(0,0,0);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;
    auto focus = lumen::vec3(0, 0, focal_length);

    auto horizontal = lumen::vec3(viewport_width, 0, 0);
    auto vertical = lumen::vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - focus;




    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int ir = 0, ig = 0, ib = 0, i = 0, j = 0; j < image_height; j++)
    {
        std::cerr << "\n" << j << " Scanlines completed " << std::flush;
        
        for(i = 0; i < image_width; i++)
        {
            // color pixelCol(double(i) / (image_width - 1), 0.1, double(j) / (image_height - 1));

            auto u = double(i) / (image_width - 1);
            auto v = double(j) / (image_height - 1);

            lumen::ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            lumen::color pixelCol = lumen::ray_normal_color(r, sp1);
            lumen::write_color(std::cout, pixelCol);

            /*
            ir = static_cast<int>(255.999 * double(i) / (image_width - 1));
            ig = static_cast<int>(255.999 * 0.1);
            ib = static_cast<int>(255.999 * double(j) / (image_height - 1));

            std::cout << ir << " " << ig << " " << ib << "\n";
            */
        }
    }

    std::cerr << "\n" << " AR : " << aspect_ratio << std::flush;

    std::cerr << "\nCompleted!\n";
}
