/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** color.h
*/

#pragma once

#include "vec3.hpp"
#include "Vector.hpp"

namespace Raytracer {
    class Camera {
    public:
        Camera() = default;

        void calculateViewport() {
            const double rad = fieldOfView * M_PI / 180.0;
            focalLength = 1.0;
            viewportHeight = 2.0 * tan(rad / 2) * focalLength;
            viewportWidth = viewportHeight * aspectRatio;
            viewportU = vec3(viewportWidth, 0, 0);
            viewportV = vec3(0, -viewportHeight, 0);
            viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
        }

        point3 cameraCenter;
        double fieldOfView;
        double focalLength;
        double viewportHeight, viewportWidth;
        vec3 viewportU, viewportV;
        vec3 viewportUpperLeft;
        int aspectRatio;
        int imageWidth;
        int imageHeight;
    };
}
