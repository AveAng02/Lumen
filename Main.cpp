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

    world.add(std::make_shared<lumen::SPHERE>(lumen::point3(0, 0, -1), 0.5, lumen::color(1,0,0), "RED_SPHERE"));
    world.add(std::make_shared<lumen::SPHERE>(lumen::point3(0, -101.5, -1), 100, lumen::color(0,0,1), "BIG_BLUE_SPHERE"));

    lumen::Camera cam;

    cam.render(world);
    
    std::cerr << "\nCompleted!\n";

    return 0;
}
