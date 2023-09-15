#include "vec3.h"

#include <iostream>
#include <cmath>


// Class definitions

vec3::vec3() 
{
    e[0] = 0;
    e[1] = 0;
    e[2] = 0;
}

vec3::vec3(double e0, double e1, double e2) 
{
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
}

double vec3::x() const 
{
    return e[0];
}

double vec3::y() const 
{
    return e[1];
}

double vec3::z() const 
{
    return e[2];
}

vec3 vec3::operator-() const 
{
    return vec3(-e[0], -e[1], -e[2]);
}

double vec3::operator[](int i) const 
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

double& vec3::operator[](int i) 
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

vec3& vec3::operator+=(const vec3 &v) 
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3& vec3::operator*=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vec3& vec3::operator/=(const double t)
{
    return *this *= 1/t;
}

double vec3::length_squared() const
{
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

double vec3::length() const
{
    return sqrt(length_squared());
}


// Vec3 Functionalities

std::ostream& operator<<(std::ostream &out, const vec3 &v)
{
    return out << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

std::istream& operator>>(std::istream &in, vec3 &v)
{
    return in >> v[0] >> v[1] >> v[2];
}

vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
}

vec3 operator-(const vec3& u, const vec3& v)
{
    return vec3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
}

vec3 operator*(const double t, const vec3& v)
{
    return vec3(t*v[0], t*v[1], t*v[2]);
}

vec3 operator*(const vec3& v, const double t)
{
    return vec3(t*v[0], t*v[1], t*v[2]);
}

vec3 operator/(const double t, const vec3& v)
{
    return vec3(v[0]/t, v[1]/t, v[2]/t);
}

vec3 operator/(const vec3& v, const double t)
{
    return vec3(v[0]/t, v[1]/t, v[2]/t);
}

double operator*(const vec3& u, const vec3& v)
{
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

vec3 operatorX(const vec3& u, const vec3& v)
{
    return vec3(u[1]*v[2] - u[2]*v[1],
                v[0]*u[2] - u[0]*v[2],
                u[0]*v[1] - u[1]*v[0]);
}

vec3 unit(const vec3& v)
{
    return v / v.length();
}