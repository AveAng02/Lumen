#pragma once

#include <iostream>
#include <cmath>

// vec3 class

class vec3 
{
    public:
        double e[3];
        vec3();
        vec3(double e0, double e1, double e2);
        double x() const;
        double y() const;
        double z() const;
        vec3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);
        vec3& operator+=(const vec3 &v);
        vec3& operator*=(const double t);
        vec3& operator/=(const double t);
        double length_squared() const;
        double length() const;
};

using point3 = vec3;
using color = vec3;

// vec3 Functionalities
std::ostream& operator<<(std::ostream &out, const vec3 &v);
std::istream& operator>>(std::istream &in, vec3 &v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const double t, const vec3& v);
vec3 operator*(const vec3& v, const double t);
vec3 operator/(const double t, const vec3& v);
vec3 operator/(const vec3& v, const double t);
double operator*(const vec3& u, const vec3& v);
vec3 operatorX(const vec3& u, const vec3& v);
vec3 unit(const vec3& v);