#pragma once

#include <iostream>

class vec3 {
public:
    vec3();
    vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    double r() const;
    double g() const;
    double b() const;

    vec3 operator-() const;

    double operator[](int i) const;
    double& operator[](int i);

    vec3& operator+=(const vec3& v);
    vec3& operator*=(double t);
    vec3& operator/=(double t);

    vec3 operator+(const vec3& v) const;
    vec3 operator-(const vec3& v) const;
    vec3 operator*(const vec3& v) const;
    vec3 operator*(double t) const;
    vec3 operator/(double t) const;

    bool operator==(const vec3& v) const;
    bool operator!=(const vec3& v) const;

    friend vec3 operator*(double t, const vec3& v);
    friend vec3 operator/(double t, const vec3& v);

    double length() const;
    double length_squared() const;
    vec3 to(const vec3& v) const;

    static double dot(const vec3& u, const vec3& v);
    static vec3 cross(const vec3& u, const vec3& v);
    static vec3 unit_vector(const vec3& v);
    static vec3 random();
    static vec3 random_unit_vector();
    static vec3 random_in_semi_sphere(const vec3& normal);
    static vec3 reflect(const vec3& v, const vec3& n);

    friend std::ostream& operator<<(std::ostream& out, const vec3& v);

private:
    double e[3];
};

using point3 = vec3;
