/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** main.cpp
*/
#include <SFML/Graphics.hpp>
#include "include/vec3.hpp"
#include "include/Color.hpp"
#include "include/Ray.hpp"
#include "Lights/FrontLight.hpp"
#include "Shapes/Sphere.hpp"
#include "Engine/Engine.hpp"

int main(int ac, char **av)
{
    std::string tempFilename;
    if (ac > 3 || ac < 2) {
        std::cout << "Usage: ./raytracer [config_file]" << std::endl;
        return 84;
    }
    if (!av[2])
        tempFilename = "output.ppm";
    else
        tempFilename = av[2];
    try {
        Raytracer::Engine engine(av[1], tempFilename);
        engine.run();
    } catch (const std::exception& e) {
        std::cerr << "Une erreur est survenue : " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
