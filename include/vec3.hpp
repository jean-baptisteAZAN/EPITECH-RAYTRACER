//
// Created by Jean-Baptiste  Azan on 22/04/2024.
//

#ifndef B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_VEC3_HPP
#define B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_VEC3_HPP

#include <cmath>
#include <iostream>
#include <random>

using std::sqrt;

namespace Raytracer {

    class vec3 {
    public:
        double e[3];

        vec3() : e{0, 0, 0} {}

        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

        double x() const { return e[0]; }

        double y() const { return e[1]; }

        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

        double operator[](int i) const { return e[i]; }

        double &operator[](int i) { return e[i]; }

        vec3 &operator+=(const vec3 &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3 &operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3 &operator/=(double t) {
            return *this *= 1 / t;
        }

        double length() const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        bool near_zero() const {
            auto s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }

    };

    using point3 = vec3;

    inline std::ostream &operator<<(std::ostream &out, const vec3 &v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    inline vec3 operator+(const vec3 &u, const vec3 &v) {
        return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    inline vec3 operator-(const vec3 &u, const vec3 &v) {
        return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    inline vec3 operator*(const vec3 &u, const vec3 &v) {
        return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    inline vec3 operator*(double t, const vec3 &v) {
        return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
    }

    inline vec3 operator*(const vec3 &v, double t) {
        return t * v;
    }

    inline vec3 operator/(const vec3 &v, double t) {
        return (1 / t) * v;
    }

    inline double dot(const vec3 &u, const vec3 &v) {
        return u.e[0] * v.e[0]
               + u.e[1] * v.e[1]
               + u.e[2] * v.e[2];
    }

    inline vec3 cross(const vec3 &u, const vec3 &v) {
        return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                    u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    inline vec3 unit_vector(const vec3 &v) {
        return v / v.length();
    }

    inline double random_double() {
        return rand() / (RAND_MAX + 1.0);
    }

    inline double random_double(double min, double max) {
        return min + (max - min) * random_double();
    }

    static vec3 random(double min, double max) {
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    inline vec3 reflect(const vec3 &v, const vec3 &n) {
        return v - 2 * dot(v, n) * n;
    }

    inline vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat) {
        auto cos_theta = fmin(dot(-uv, n), 1.0);
        vec3 r_out_perp =  etai_over_etat * (uv + cos_theta * n);
        vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
        return r_out_perp + r_out_parallel;
    }

    inline double schlick(double cosine, double ref_idx) {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }

    inline vec3 random_in_unit_sphere() {
        while (true) {
            auto p = Raytracer::random(-1, 1);
            if (p.length_squared() < 1)
                return p;
        }
    }

    inline vec3 random_unit_vector() {
        return unit_vector(random_in_unit_sphere());
    }
}
#endif //B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_VEC3_HPP
