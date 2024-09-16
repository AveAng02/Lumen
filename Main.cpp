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

    auto matGround = std::make_shared<lumen::Lambertian>(lumen::color(0.8f, 0.8f, 0.0f));
    auto matCentral = std::make_shared<lumen::Lambertian>(lumen::color(0.1f, 0.2f, 0.5f));
    auto matLeft = std::make_shared<lumen::Dielectric>(1.5f); // std::make_shared<lumen::Metal>(lumen::color(0.8f, 0.8f, 0.8f), 0.3f);
    auto matRight = std::make_shared<lumen::Metal>(lumen::color(0.8f, 0.6f, 0.2f), 0.1f);

    world.add(std::make_shared<lumen::Sphere>
    (matGround, lumen::point3(0, -100.5, -1), 100, "GROUND_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matCentral, lumen::point3(0, 0, -1), 0.5f, "CENTER_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matLeft, lumen::point3(-1, 0, -1), 0.5f, "LEFT_SPHERE"));

    world.add(std::make_shared<lumen::Sphere>
    (matRight, lumen::point3(1, 0, -1), 0.5f, "RIGHT_SPHERE"));

    lumen::Camera cam;
    cam.scene.spp = 100;
    cam.scene.maxDepth = 50;

    cam.render(world);
    
    std::cerr << "\nCompleted!\n";

    return 0;
}
