#pragma once

#include <vector>
#include <string>
#include <fstream>


#include "Vec3.h"


namespace lumen
{
    class Picture
    {
    public:

        Picture(std::string fileName_)
        : fileName(fileName_)
        {

        }

        ~Picture() {}

    private:
        std::string fileName;
        std::ifstream imgFile;
        std::vector<color> pixels;
    }
}


