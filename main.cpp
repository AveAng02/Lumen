
#include<cmath>
#include<iostream>


using std::sqrt;

class vec3 
{
    public:
        vec3() : e(0,0,0) {}
        vec3(double e0, double e1, double e2) : e(e0, e1, e2) {}

        double x() const 
        {
            return e[0];
        }

        double y() const
        {
            return e[1];
        }

        double z() const
        {
            return e[2];
        }

        vec3 operator-() const
        {
            return vec3(-e[0], -e[1], -e[2]);
        }

        double e[3];
}


int main()
{
    // Dimentions

    const int image_width = 256;
    const int image_height = 256;

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int ir = 0, ig = 0, ib = 0, i = 0, j = 0; j < image_height; j++)
    {
        std::cerr << "\n" << j << " Scanlines completed " << std::flush;
        
        for(i = 0; i < image_width; i++)
        {
            ir = static_cast<int>(255.999 * double(i) / (image_width - 1));
            ig = static_cast<int>(255.999 * 0.1);
            ib = static_cast<int>(255.999 * double(j) / (image_height - 1));

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    std::cerr << "\nCompleted!\n";
}
