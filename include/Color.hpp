/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** color.h
*/

#pragma once

#include "vec3.hpp"

namespace Raytracer {

    class Color : public vec3 {
    public:
        Color() = default;

        Color(double e0, double e1, double e2) : vec3(e0, e1, e2) {}

        Color(const vec3 &v) : vec3(v) {}

        static void write_color(std::ostream &out, const Color &pixel_color) {
            auto r = pixel_color.x();
            auto g = pixel_color.y();
            auto b = pixel_color.z();

            int rbyte = int(255.999 * r);
            int gbyte = int(255.999 * g);
            int bbyte = int(255.999 * b);
            out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
        }
    };
}