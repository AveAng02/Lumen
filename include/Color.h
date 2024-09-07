#include <string>

#include "Vec3.h"
#include "MathUtils.h"

namespace lumen
{
    // Color Utility Functions
    void write_color(std::ostream &out, color pixel)
    {
        uint32_t r = static_cast<int>(255.999 * clamp(pixel[0], 0.0f, 1.0f));
        uint32_t g = static_cast<int>(255.999 * clamp(pixel[1], 0.0f, 1.0f));
        uint32_t b = static_cast<int>(255.999 * clamp(pixel[2], 0.0f, 1.0f));

        // Printing the translated value of  pixel between [0,255]
        out << r << " " << g << " " << b << "\n";
    }

    void write_color(std::ostream &out, std::string str)
    {
        // Printing the translated value of  pixel between [0,255]
        out << str << "\n";
    }
}

