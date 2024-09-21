#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>

#include "Lumen.h"

int main()
{
    // Scene objects
    lumen::HitList world;

    auto matGround = std::make_shared<lumen::Lambertian>(lumen::color(0.6f, 1.0f, 0.733f));
    auto matCentral = std::make_shared<lumen::Lambertian>(lumen::color(1.0f, 0.549f, 0.0f));
    auto matLeft = std::make_shared<lumen::Dielectric>(1.5f); // std::make_shared<lumen::Metal>(lumen::color(0.8f, 0.8f, 0.8f), 0.3f);
    auto matBubble = std::make_shared<lumen::Dielectric>(1.0f / 1.5f);
    auto matRight = std::make_shared<lumen::Metal>(lumen::color(0.949f, 0.447f, 0.373f), 0.3f);

    world.add(std::make_shared<lumen::Sphere>
    (matGround, lumen::point3(0, -100.5, -1), 100, "GROUND_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matCentral, lumen::point3(0, 0, -1), 0.5f, "CENTER_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matLeft, lumen::point3(-1, 0, -1), 0.5f, "LEFT_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matBubble, lumen::point3(-1, 0, -1), 0.4f, "BUBBLE_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matRight, lumen::point3(1, 0, -1), 0.5f, "RIGHT_SPHERE"));

    lumen::Camera cam;
    cam.lookFrom = lumen::point3(0.0f, 0.0f, 1.0f);
    cam.vfov = 90.0f;
    cam.scene.aspectRatio = 16.0f / 9.0f;
    cam.scene.image_width = 800u;
    cam.scene.spp         = 20;
    cam.scene.maxDepth    = 10;
    cam.initialize();

    cam.render(world);
    
    std::cerr << "\nCompleted!\n";

    return 0;
}
