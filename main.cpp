
#include <cmath>
#include <iostream>
#include <vec3.h>


// Color Utility Functions

void write_color(std::ostream &out, color pixel)
{
    // Printing the translated value of  pixel between [0,255]
    out << static_cast<int>(255.999 * pixel.x()) << " "
        << static_cast<int>(255.999 * pixel.y()) << " "
        << static_cast<int>(255.999 * pixel.z()) << "\n";
}


// Ray Class

class ray
{
    public:
        ray() {}

        ray(const point3 origin, const vec3& direction): o(origin), d(direction) {}

        point3 origin() const
        {
            return o;
        }

        vec3 direction() const
        {
            return d;
        }

        point3 at(const double t) const
        {
            return o + t*d;
        }

    public:
        point3 o;
        vec3 d;
};



// SPHERE 

struct SPHERE
{
    point3 center;
    double radius;
    color sph_color;
    std::string name;

    SPHERE()
    {
        this->center = point3(0,0,0);
        this->radius = 0.0;
        this->sph_color = color(0,0,0);
        this->name = "SPHERE";
    }

    SPHERE(point3 center_, double radius_, color col_, std::string name_)
    {
        this->center = center_;
        this->radius = radius_;
        this->sph_color = col_;
        this->name = name_;
    }
};

double hit_sphere(const SPHERE sp, const ray& r)
{
    vec3 oc = r.origin() - sp.center;
    auto a = r.direction() * r.direction();
    auto b = 2.0 * oc * r.direction();
    auto c = oc*oc - sp.radius*sp.radius;
    auto D = b*b - 4*a*c;

    return (D > 0)? ((-b - sqrt(D)) / (2.0*a)) : -1 ;
}




// Defining Ray Color

color ray_color(const ray& r, SPHERE sp)
{
    if(hit_sphere(sp, r) >= 0.0)
    {
        return sp.sph_color;
    }

    vec3 unit_direc = unit(r.direction());

    auto t = 0.5 * (unit_direc.y() + 1.0);

    return (1.0 - t)*color(1,1,1) + t*color(0.5,0.7,1);
}





// Normal

color ray_normal_color(const ray& r, SPHERE sp)
{
    auto t = hit_sphere(sp, r);
    
    if(t > 0.0)
    {
        vec3 normal = unit(r.at(t) - sp.center);
        return 0.5*color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    vec3 unit_direc = unit(r.direction());

    t = 0.5 * (unit_direc.y() + 1.0);

    return (1.0 - t)*color(1,1,1) + t*color(0.5,0.7,1);
}





// Main

int main()
{
    // Scene objects
    SPHERE sp1(point3(-1, 0, -2), 1, color(1,0,0), "RED_SPHERE");

    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);


    // Camera
    // Camera position = (0,0,0)
    auto origin = point3(0,0,0);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;
    auto focus = vec3(0, 0, focal_length);

    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
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

            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixelCol = ray_normal_color(r, sp1);
            write_color(std::cout, pixelCol);

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
