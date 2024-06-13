/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** Ray.hpp
*/
#pragma once

#include "vec3.hpp"

namespace Raytracer {

    class Ray {
    public:
        double t_min, t_max;
        Ray() {}

        Ray(const point3 &origin, const vec3 &direction) : orig(origin), dir(direction) {}

        const point3 &origin() const { return orig; }

        const vec3 &direction() const { return dir; }

        point3 at(double t) const {
            return orig + t * dir;
        }

    private:
        point3 orig;
        vec3 dir;
    };
}
