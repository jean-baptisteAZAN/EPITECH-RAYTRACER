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
#include "Hitmat.hpp"

namespace Raytracer {

    class Metal : public Material {
    public:
        Metal(const Color &albedo, double fuzziness) : albedo(albedo), fuzz(fuzziness < 1 ? fuzziness : 1) {}

        bool scatter(const Ray &ray_in, const HitMat &rec, Color &attenuation, Ray &scattered) const override {
            vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
            reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
        std::string getName() const override { return "Metal"; }

    private:
        Color albedo;
        double fuzz;
    };
}
