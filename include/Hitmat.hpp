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
    class Material;

    class HitMat {
    public:
        point3 p;
        vec3 normal;
        double t;
        bool front_face;
        Color hit_color;
        std::shared_ptr<Material> mat_ptr;

        std::shared_ptr<Material> get() const {
            return mat_ptr;
        }

        void set_face_normal(const Ray &r, const vec3 &outward_normal) {
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };
}