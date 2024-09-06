#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>

#include "Lumen.h"

#define BEAUTY_PASS
// #define NORMAL_PASS

int main()
{
#ifdef BEAUTY_PASS
    std::ofstream ofs("../output/output_beauty.ppm", std::ios_base::out | std::ios_base::binary);
#endif // BEAUTY_PASS

#ifdef NORMAL_PASS
    std::ofstream ofs("../output/output_normal.ppm", std::ios_base::out | std::ios_base::binary);
#endif // NORMAL_PASS
    
    // Image File
    double aspectRatio = 16.0 / 9.0;
    int image_width = 400u;
    int image_height = image_width / aspectRatio;
    
    ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    // Scene objects
    lumen::HitList world;

    world.add(std::make_shared<lumen::SPHERE>(lumen::point3(0, 0, -1), 0.5, lumen::color(1,0,0), "RED_SPHERE"));
    world.add(std::make_shared<lumen::SPHERE>(lumen::point3(0, -101.5, -1), 100, lumen::color(0,0,1), "BIG_BLUE_SPHERE"));

    // Camera
    // Camera position = (0,0,0)
    auto focal_length = 1.0;
    auto vpW = 2.0;  // view port height
    auto vpH = vpW / aspectRatio; // view port width
    auto camera_center = lumen::point3(0, 0, 1);

    // Vectors on the view port edges
    auto horizontal = lumen::vec3(vpW, 0, 0); // view port u
    auto vertical = lumen::vec3(0, -vpH, 0);  // view port v

    // Pitch between pixels in horizontal and vertical directions
    auto deltaV = horizontal / image_width;
    auto deltaU = vertical / image_height;

    // Location of upper left corner of the view port
    auto vpReference = camera_center - lumen::vec3(0, 0, focal_length) 
                        - horizontal/2 - vertical/2;
    auto pXRef = vpReference + 0.5 * (deltaU + deltaV); // Location of upper left pixel

    lumen::ray hitRay;
    lumen::color pixelCol;

    // Render

    // std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int i = 0, j = 0; i < image_height; i++)
    {
        // std::cerr << "\n" << j << " Scanlines completed " << std::flush;
        
        for(j = 0; j < image_width; j++)
        {
            auto pXCentre = pXRef + (i * deltaU) + (j * deltaV);
            auto rayDirection = pXCentre - camera_center;
            hitRay = lumen::ray(pXCentre, rayDirection);

            #ifdef BEAUTY_PASS
                pixelCol = lumen::ray_color(hitRay, world);
            #endif // BEAUTY_PASS

            #ifdef NORMAL_PASS
                pixelCol = lumen::ray_normal_color(hitRay, world);
            #endif // NORMAL_PASS
            
            lumen::write_color(ofs, pixelCol);
        }
    }

    std::cerr << "\nCompleted!\n";
}
