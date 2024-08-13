#pragma once

#include <cmath>
#include <iostream>

class vec3
{
public:
    vec3();
    vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    vec3 operator-() const;
    double operator[](int i) const;
    double &operator[](int i);

    vec3 &operator+=(const vec3 &v);
    vec3 &operator*=(double t);
    vec3 &operator/=(double t);

    vec3 operator+(const vec3 &v) const;
    vec3 operator-(const vec3 &v) const;
    vec3 operator*(const vec3 &v) const;
    vec3 operator*(double t) const;
    vec3 operator/(double t) const;

    static double dot(const vec3 &u, const vec3 &v);
    static vec3 cross(const vec3 &u, const vec3 &v);
    static vec3 unit_vector(const vec3 &v);

    double length() const;
    double length_squared() const;

    friend std::ostream &operator<<(std::ostream &out, const vec3 &v);

private:
    double e[3];
};

using point3 = vec3;
