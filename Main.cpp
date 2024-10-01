#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>

#include "src/Lumen.h"

int main()
{
    // Scene objects
    lumen::HitList world;

    auto matGround = std::make_shared<lumen::Lambertian>
                    (lumen::color(0.6f, 1.0f, 0.733f));
    auto matCentral = std::make_shared<lumen::Lambertian>
                    (lumen::color(1.0f, 0.549f, 0.0f));
    auto matLeft = std::make_shared<lumen::Dielectric>(1.3333f); 
    // auto matLeft = std::make_shared<lumen::Metal>(lumen::color(0.8f, 0.8f, 0.8f), 0.3f);
    auto matBubble = std::make_shared<lumen::Dielectric>(1.0f / 1.5f);
    auto matRight = std::make_shared<lumen::Metal>
                    (lumen::color(0.949f, 0.447f, 0.373f), 0.3f);

    world.add(std::make_shared<lumen::Sphere>
    (matGround, lumen::point3(0, -100.5, -1), 100, "GROUND_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matCentral, lumen::point3(0, 0, -1.2f), 0.5f, "CENTER_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matLeft, lumen::point3(-1, 0, -1), 0.5f, "LEFT_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matBubble, lumen::point3(-1, 0, -1), 0.4f, "BUBBLE_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matRight, lumen::point3(1, 0, -1), 0.5f, "RIGHT_SPHERE"));
    

    lumen::Camera cam;
    cam.vfov = 90.0f;
    cam.lookFrom = lumen::point3(-2,2,1);
    cam.lookAt   = lumen::point3(0,0,-1);
    cam.vup      = lumen::vec3(0,1,0);
    cam.aspectRatio = 16.0f / 9.0f;
    cam.image_width = 800u;
    cam.spp         = 100;
    cam.maxDepth    = 50;
    cam.initialize();

    lumen::renderMultiThread(world, cam);
    // lumen::renderSingleThread(world, cam);
    
    std::cerr << "Completed!\n";

    return 0;
}
