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
#include "Hitmat.hpp"

namespace Raytracer {
    class Material {
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray &rayon_in, const HitMat &rec, Color &color, Ray &scatter) const = 0;
        virtual std::string getName() const = 0;
    };

    class Lambertian : public Material {
    public:
        Lambertian(const Color &albedo) : albedo(albedo) {}

        bool scatter(const Ray &r_in, const HitMat &rec, Color &attenuation, Ray &scattered) const override {
            (void) r_in;
            auto scatter_direction = rec.normal + random_unit_vector();
            if (scatter_direction.near_zero())
                scatter_direction = rec.normal;
            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }
        [[nodiscard]] std::string getName() const override { return "Lambertian"; }

    private:
        Color albedo;
    };

    class Transparent : public Material {
    public:
        double ref_idx;
        Color _color;

        Transparent(const Color &color, double ref_idx) : ref_idx(ref_idx), _color(color) {}
        static double reflectance(double cosine, double ref_idx) {
            double r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }

        bool scatter(const Ray &ray_in, const HitMat &rec, Color &attenuation, Ray &scattered) const override {
            attenuation = _color; // Color of the refracted light is influenced by the material's inherent color
            double etai_over_etat = rec.front_face ? (1.0 / ref_idx) : ref_idx;

            vec3 unit_direction = unit_vector(ray_in.direction());
            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
            bool cannot_refract = etai_over_etat * sin_theta > 1.0;

            vec3 direction;

            if (cannot_refract || reflectance(cos_theta, etai_over_etat) > random_double()) {
                direction = reflect(unit_direction, rec.normal);
            } else {
                direction = refract(unit_direction, rec.normal, etai_over_etat);
            }

            scattered = Ray(rec.p, direction);
            return true;
        }

        [[nodiscard]] std::string getName() const override { return "Transparent"; }
    };
};
