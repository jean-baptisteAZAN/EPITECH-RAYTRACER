/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** ILight.hpp
*/
#pragma once

#include "vec3.hpp"
#include "Color.hpp"

namespace Raytracer {
    class ILight {
    public:
        virtual vec3 getDirection(const point3 &hit_point) const = 0;

        virtual Color getIntensity(const point3 &hit_point) const = 0;

        virtual ~ILight() {}
    };
}