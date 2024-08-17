#include "vec3.h"

vec3::vec3() : e{0, 0, 0} {}
vec3::vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

double vec3::r() const { return e[0]; }
double vec3::g() const { return e[1]; }
double vec3::b() const { return e[2]; }

vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }
double vec3::operator[](int i) const { return e[i]; }
double &vec3::operator[](int i) { return e[i]; }

vec3 &vec3::operator+=(const vec3 &v)
{
    for (size_t i = 0; i < 3; i++)
        e[i] += v.e[i];
    return *this;
}

vec3 &vec3::operator*=(double t)
{
    for (size_t i = 0; i < 3; i++)
        e[i] *= t;
    return *this;
}

vec3 &vec3::operator/=(double t)
{
    for (size_t i = 0; i < 3; i++)
        e[i] /= t;
    return *this;
}

vec3 vec3::operator+(const vec3 &v) const
{
    return vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
}

vec3 vec3::operator-(const vec3 &v) const
{
    return vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
}

vec3 vec3::operator*(const vec3 &v) const
{
    return vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
}

vec3 vec3::operator*(double t) const
{
    return vec3(e[0] * t, e[1] * t, e[2] * t);
}

vec3 vec3::operator/(double t) const
{
    return vec3(e[0] / t, e[1] / t, e[2] / t);
}

vec3 operator*(double t, const vec3 &v)
{
    return v * t;
}

vec3 operator/(double t, const vec3 &v)
{
    return v / t;
}

double vec3::dot(const vec3 &u, const vec3 &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

vec3 vec3::cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

vec3 vec3::unit_vector(const vec3 &v)
{
    return v / v.length();
}

double vec3::length() const
{
    return std::sqrt(length_squared());
}

double vec3::length_squared() const
{
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

vec3 vec3::to(const vec3 &v) const
{
    return v - *this;
}

vec3 vec3::random() { return vec3(math::random_double(), math::random_double(), math::random_double()); }
vec3 vec3::random_in_semi_sphere(const vec3 &normal)
{
    vec3 random = vec3::random();
    if (vec3::dot(random, normal) > 0.0)
        return random;
    else
        return -random;
}

std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
