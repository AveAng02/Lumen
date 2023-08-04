#pragma once

#include <iostream>
#include <cmath>

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