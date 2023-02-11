
#include<cmath>
#include<iostream>


using std::sqrt;

// vec3 class

class vec3 
{
    public:
        vec3() 
        {
            e[0] = 0;
            e[1] = 0;
            e[2] = 0;
        }

        vec3(double e0, double e1, double e2) 
        {
            e[0] = e0;
            e[1] = e1;
            e[2] = e2;
        }

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

        double operator[](int i) const
        {
            if(i < 3 && i >=0)
            {
                return e[i];
            }
            else
            {
                std::cerr << "Invalid Access Specifier" << std::flush;
            }

            return -1; // TO FIX
        }

        double& operator[](int i)
        {
            if(i < 3 && i >=0)
            {
                return e[i];
            }
            else
            {
                std::cerr << "Invalid Access Specifier" << std::flush;
            }
        }

        vec3& operator+=(const vec3 &v)
        {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(const double t)
        {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t)
        {
            return *this *= 1/t;
        }

        double length_squared() const
        {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double length() const
        {
            return sqrt(length_squared());
        }

        double e[3];
};

using point3 = vec3;
using color = vec3;

// vec3 Functionalities

inline std::ostream& operator<<(std::ostream &out, const vec3 &v)
{
    return out << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

inline std::istream& operator>>(std::istream &in, vec3 &v)
{
    return in >> v[0] >> v[1] >> v[2];
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

inline vec3 operator*(const double t, const vec3& v)
{
    return vec3(t*v[0], t*v[1], t*v[2]);
}

inline vec3 operator*(const vec3& v, const double t)
{
    return vec3(t*v[0], t*v[1], t*v[2]);
}

inline vec3 operator/(const double t, const vec3& v)
{
    return vec3(v[0]/t, v[1]/t, v[2]/t);
}

inline vec3 operator/(const vec3& v, const double t)
{
    return vec3(v[0]/t, v[1]/t, v[2]/t);
}

inline double operator*(const vec3& u, const vec3& v)
{
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

inline vec3 operatorX(const vec3& u, const vec3& v)
{
    return vec3(u[1]*v[2] - u[2]*v[1],
                v[0]*u[2] - u[0]*v[2],
                u[0]*v[1] - u[1]*v[0]);
}

inline vec3 unit(const vec3& v)
{
    return v / v.length();
}


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






// Defining Ray Color

color ray_color(const ray& r)
{
    vec3 unit_direc = unit(r.direction());

    auto t = 0.5 * (unit_direc.y() + 1.0);

    return (1.0 - t)*color(1,1,1) + t*color(0.5,0.7,1);
}



// Main

int main()
{
    // Image
    const auto aspect_ratio = 16 / 9;
    const int image_width = 256;
    const int image_height = 256;


    // Camera
    // Camera position = (0,0,0)
    auto origin = point3(0,0,0);

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);




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
            color pixelCol = ray_color(r);
            write_color(std::cout, pixelCol);

            /*
            ir = static_cast<int>(255.999 * double(i) / (image_width - 1));
            ig = static_cast<int>(255.999 * 0.1);
            ib = static_cast<int>(255.999 * double(j) / (image_height - 1));

            std::cout << ir << " " << ig << " " << ib << "\n";
            */
        }
    }

    std::cerr << "\nCompleted!\n";
}
