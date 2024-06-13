/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** Primitive.hpp
*/
#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "Material.hpp"
#include "Interval.hpp"

namespace Raytracer {
    class IShape {
    public:
        virtual bool hit(const Ray &r, Interval ray_t, double &t_hit, vec3 &hit_normal, Color &hit_color, HitMat &rec) const = 0;

        virtual ~IShape() {}
    };
}