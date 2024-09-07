#include "Lumen/include/Camera.h"
#include "include/Pass.h"

namespace lumen
{
    void Camera::render(const HitList& world)
    {
        ray hitRay;
        color pixelCol;

        std::ofstream ofs("../output/output_normal.ppm", std::ios_base::out | std::ios_base::binary);
        ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for(int i = 0, j = 0; i < image_height; i++)
        {
            for(j = 0; j < image_width; j++)
            {
                auto pXCentre = pXRef + (i * deltaU) + (j * deltaV);
                auto rayDirection = pXCentre - camera_center;
                hitRay = lumen::ray(pXCentre, rayDirection);

                pixelCol = lumen::ray_normal_color(hitRay, world);
                
                lumen::write_color(ofs, pixelCol);
            }
        }
    }

    void Camera::initialize()
    {
        aspectRatio = 16.0 / 9.0;
        image_width = 400u;
        image_height = image_width / aspectRatio;

        // Camera
        // Camera position = (0,0,0)
        auto focal_length = 1.0;
        auto vpW = 2.0;  // view port height
        auto vpH = vpW / aspectRatio; // view port width
        camera_center = lumen::point3(0, 0, 1);

        // Vectors on the view port edges
        auto horizontal = lumen::vec3(vpW, 0, 0); // view port u
        auto vertical = lumen::vec3(0, -vpH, 0);  // view port v

        // Pitch between pixels in horizontal and vertical directions
        deltaV = horizontal / image_width;
        deltaU = vertical / image_height;

        // Location of upper left corner of the view port
        auto vpReference = camera_center - lumen::vec3(0, 0, focal_length) 
                            - horizontal/2 - vertical/2;
        pXRef = vpReference + 0.5 * (deltaU + deltaV); // Location of upper left pixel
    }

    /*
    color Camera::ray_color(const ray& r, const HitList& world)
    {
        hitRecord rec;

        if(world.hit(r, 0, INF, rec))
        {
            return rec.geoPtr->geoColor;
        }

        vec3 unit_direc = unit(r.direction());
        auto t = 0.5 * (unit_direc.y() + 1.0);
        return (1.0 - t) * color(1,1,1) + t*color(0.5,0.7,1);
    }

    color Camera::ray_normal_color(const ray& r, const HitList& world)
    {
        hitRecord rec;

        if(world.hit(r, 0, INF, rec))
        {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unit_direc = unit(r.direction());
        auto t = 0.5 * (unit_direc.y() + 1.0);
        return (1.0 - t)*color(1,1,1) + t*color(0.5,0.7,1);
    }
    */
}
