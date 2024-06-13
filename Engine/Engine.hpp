//
// Created by Jean-Baptiste  Azan on 23/04/2024.
//

#ifndef B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_ENGINE_HPP
#define B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_ENGINE_HPP

#include "../include/Color.hpp"
#include "../include/Ray.hpp"
#include "../include/Vector.hpp"
#include "../include/IShape.hpp"
#include "../include/Camera.hpp"
#include "../include/ILight.hpp"
#include "../include/Hitmat.hpp"
#include "../include/Material.hpp"
#include "../include/Metal.hpp"
#include "../include/Mirror.hpp"
#include "../include/LibraryLoader.hpp"
#include "../Lights/FrontLight.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <fstream>
#include <libconfig.h++>
#include <exception>
#include <thread>
#include <mutex>
#include <algorithm>
#include <filesystem>
#include <chrono>
#include <sys/stat.h>

namespace Raytracer {

    typedef std::unique_ptr<ILight> (*CreateLightFunc)(vec3 position, Color color);

    typedef std::unique_ptr<IShape> (*CreateObjectFunc)(const point3 &center, double radius, const Color &color,
                                                        std::shared_ptr<Material> m);

    typedef std::unique_ptr<IShape> (*CreateConesFunc)(const vec3 &v, const vec3 &a, double ang, double size,
                                                       const Color &color, std::shared_ptr<Material> m);

    typedef std::unique_ptr<IShape> (*CreatePlaneFunc)(const point3 &position, const vec3 &normal, double size,
                                                       const Color &color, std::shared_ptr<Material> m);

    typedef std::unique_ptr<IShape> (*CreateTriangleFunc)(const point3 &v0, const point3 &v1, const point3 &v2,
                                                          const Color &color, std::shared_ptr<Material> m);

    typedef std::unique_ptr<IShape> (*CreateCylinderFunc)(const point3 &, const vec3 &, double, double, const Color &,
                                                          std::shared_ptr<Material> m, vec3 rotation);

    typedef std::unique_ptr<IShape> (*CreateTorusFunc)(const point3 &center, double majorRadius, double minorRadius,
                                                       const Color &color, std::shared_ptr<Material> m);

    typedef std::unique_ptr<IShape> (*CreateCubeFunc)(vec3 position, vec3 scale, vec3 rotation, Color color,
                                                      double size, std::shared_ptr<Material> mat);

    class Engine {
    private:

        void processEvents();

        void render2(int i, int j, Color *pixelColor);

        void render();

        void saveToPPM(const std::string &filename);

        sf::RenderWindow window;
        sf::Event event;
        std::vector<std::unique_ptr<IShape>> shapes;
        std::vector<std::unique_ptr<ILight>> lights;
        sf::VertexArray pixels;
        Raytracer::Camera camera;
        Color backgroundColor = Color(0.0, 0.0, 0.0);
        int samples_per_pixel = 4;


        std::string configFilePath;
        time_t lastModified;
        std::string outputFileName;
        int lastRenderedPixelIndex = 0;
        bool rendered = false;

        class ConfigException : public std::exception {
        public:
            ConfigException(const std::string &message) : _message(message) {}

            const char *what() const noexcept override {
                return _message.c_str();
            }

        private:
            std::string _message;
        };

    public:

        Raytracer::LibraryLoader libLoader;

        Engine(const std::string &path, const std::string &outputFileName);

        ~Engine() {
            shapes.clear();
            lights.clear();
        }

        void run();

        bool isShadowed(const vec3 &hit_point, const vec3 &light_direction, const IShape *current_shape);

        void renderPixel(int start, int end);

        void setupCamera(const libconfig::Setting &objects);

        Color rayTrace(const Ray &ray, int depth);

        void loadConfig(const std::string &configFile);

        bool checkConfigChanged();

        void reloadConfig();

        void loadObjectConfig(const libconfig::Setting &objects);

        void loadLightConfig(const libconfig::Setting &light);

        std::unique_ptr<ILight> (*createLightFunc)(vec3 position, Color color);

        CreateObjectFunc createObjectFunc;
        CreatePlaneFunc createPlaneFunc;
        CreateConesFunc createConesFunc;
        CreateTriangleFunc createTriangleFunc;
        CreateCylinderFunc createCylinderFunc;
        CreateTorusFunc createTorusFunc;

        std::vector<std::string> logBuffer;

        void addLog(const std::string &log) {
            logBuffer.push_back(log);
        }

        void getLogs() {
            std::cout << "Logs:" << std::endl;
            for (const auto &log: logBuffer) {
                std::cout << log << std::endl;
            }
        }
    };
}
#endif //B_OOP_400_LIL_4_1_RAYTRACER_THEO_LEMAIRE_ENGINE_HPP
