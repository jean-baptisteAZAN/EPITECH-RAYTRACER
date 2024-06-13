/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** Mirror.hpp
*/

#pragma once

#include "vec3.hpp"
#include "Ray.hpp"
#include "Color.hpp"
#include "Material.hpp"
#include "Hitmat.hpp"

namespace Raytracer {

        class Mirror : public Material {
        public:
            Mirror(const Color &color) : albedo(color) {}

            virtual bool scatter(const Ray &ray_in, const HitMat &rec, Color &attenuation, Ray &scattered) const override {
                attenuation = albedo;
                vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
                scattered = Ray(rec.p, reflected);
                return true;
            }
            [[nodiscard]] std::string getName() const override { return "Mirror"; }
        private:
            Color albedo;
        };
}
