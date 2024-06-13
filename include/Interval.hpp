/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** color.h
*/

#pragma once

#include "vec3.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Material.hpp"
#include <memory>

namespace Raytracer {
    class Interval {
    public:
        double minimum;
        double maximum;

        Interval() : minimum(std::numeric_limits<double>::infinity()), maximum(-std::numeric_limits<double>::infinity()) {}

        Interval(double minimum, double maximum) : minimum(minimum), maximum(maximum) {}

        double size() const {
            return maximum - minimum;
        }

        bool contains(double x) const {
            return minimum <= x && x <= maximum;
        }

        bool surrounds(double x) const {
            return minimum < x && x < maximum;
        }

        static const Interval empty, universe;
    };

}