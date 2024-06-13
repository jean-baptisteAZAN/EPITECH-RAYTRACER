/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** Engine.cpp
*/

#include "Engine.hpp"

namespace Raytracer {
    std::mutex pixel_mutex;

    Engine::Engine(const std::string &path, const std::string &outputPath) : configFilePath(path) {
        struct stat fileInfo;
        if (stat(configFilePath.c_str(), &fileInfo) != 0) {
            throw std::runtime_error("Failed to get file info");
        }
        lastModified = fileInfo.st_mtime;
        loadConfig(configFilePath);
        outputFileName = outputPath;
    }

    bool Engine::checkConfigChanged() {
        struct stat fileInfo;
        if (stat(configFilePath.c_str(), &fileInfo) != 0) {
            throw std::runtime_error("Failed to get file info");
        }
        time_t modifiedTime = fileInfo.st_mtime;
        if (modifiedTime != lastModified) {
            lastModified = modifiedTime;
            return true;
        }
        return false;
    }

    void Engine::reloadConfig() {
        shapes.clear();
        lights.clear();
        pixels.clear();
        loadConfig(configFilePath);
    }

    void Engine::loadLightConfig(const libconfig::Setting &light) {
        int count2 = light.getLength();

        for (int i = 0; i < count2; ++i) {
            const libconfig::Setting &object = light[i];
            std::string type;
            if (!object.lookupValue("type", type)) {
                continue;
            }
            libconfig::Setting &colorSetting = object["color"];
            vec3 color = {colorSetting[0], colorSetting[1], colorSetting[2]};
            if (type == "front") {
                std::cout << "Front light" << std::endl;
                libLoader.loadLibrary("plugins/FrontLight.so");
                createLightFunc = libLoader.getFunction<CreateLightFunc>("plugins/FrontLight.so", "createLight");
                lights.push_back(createLightFunc(color, vec3(0, 0, 1)));
            }
            if (type == "point") {
                std::cout << "Point light" << std::endl;
                libconfig::Setting &positionSetting = object["position"];
                if (!colorSetting.isList() || colorSetting.getLength() != 3 ||
                    !positionSetting.isList() || positionSetting.getLength() != 3) {
                    throw ConfigException(
                            "Format incorrect pour la couleur ou la position à l'index " + std::to_string(i));
                    continue;
                }
                vec3 position = {positionSetting[0], positionSetting[1], positionSetting[2]};
                libLoader.loadLibrary("plugins/PointLight.so");
                createLightFunc = libLoader.getFunction<CreateLightFunc>("plugins/PointLight.so", "createLight");
                lights.push_back(createLightFunc(color, position));
            }
        }
    }

    void Engine::loadObjectConfig(const libconfig::Setting &objects) {
        int count = objects.getLength();

        for (int i = 0; i < count; ++i) {
            const libconfig::Setting &object = objects[i];
            std::string type;
            std::string materialType;
            if (!object.lookupValue("type", type)) {
                continue;
            }
            Color color = {object["color"][0], object["color"][1], object["color"][2]};
            point3 position = {object["position"][0], object["position"][1], object["position"][2]};
            std::string libName = "plugins/" + type + ".so";
            if (!libLoader.loadLibrary(libName)) {
                std::cerr << "Failed to load library " << libName << std::endl;
                continue;
            }
            std::shared_ptr<Material> material = nullptr;
            if (object.lookupValue("material", materialType)) {
                if (materialType == "Metal") {
                    material = std::make_shared<Metal>(
                            Color(object["albedo"][0], object["albedo"][1],
                                  object["albedo"][2]),
                            object["fuzz"]
                    );
                } else if (materialType == "Lambertian") {
                    material = std::make_shared<Lambertian>(
                            Color(object["albedo"][0], object["albedo"][1],
                                  object["albedo"][2])
                    );
                } else if (materialType == "Mirror") {
                    material = std::make_shared<Mirror>(
                            Color(object["albedo"][0], object["albedo"][1],
                                  object["albedo"][2])
                    );
                }
            }
            if (type == "Sphere") {
                double radius = object["radius"];
                CreateObjectFunc createFunc = libLoader.getFunction<CreateObjectFunc>(libName, "createObject");
                shapes.push_back(createFunc(position, radius, color, material));
            } else if (type == "Plane") {
                vec3 normal = {object["normal"][0], object["normal"][1], object["normal"][2]};
                double size = object["size"];
                CreatePlaneFunc createFunc = libLoader.getFunction<CreatePlaneFunc>(libName, "createObject");
                shapes.push_back(createFunc(position, normal, size, color, material));
            } else if (type == "Cones") {
                vec3 axis = {object["axis"][0], object["axis"][1], object["axis"][2]};
                double angle = object["angle"];
                double size = object["size"];
                CreateConesFunc createFunc = libLoader.getFunction<CreateConesFunc>(libName, "createCones");
                shapes.push_back(createFunc(axis, position, angle, size, color, material));
            } else if (type == "Cylinder") {
                vec3 axis = {object["axis"][0], object["axis"][1], object["axis"][2]};
                double radius = object["radius"];
                double height = object["height"];
                vec3 rotation = {object["rotation"][0], object["rotation"][1], object["rotation"][2]};
                CreateCylinderFunc createFunc = libLoader.getFunction<CreateCylinderFunc>(libName, "createCylinder");
                shapes.push_back(createFunc(position, axis, radius, height, color, material, rotation));
            } else if (type == "Torus") {
                double majorRadius = object["majorRadius"];
                double minorRadius = object["minorRadius"];
                CreateTorusFunc createFunc = libLoader.getFunction<CreateTorusFunc>(libName, "createObject");
                shapes.push_back(createFunc(position, majorRadius, minorRadius, color, material));
            } else if (type == "Triangle") {
                point3 v0 = {object["v0"][0], object["v0"][1], object["v0"][2]};
                point3 v1 = {object["v1"][0], object["v1"][1], object["v1"][2]};
                point3 v2 = {object["v2"][0], object["v2"][1], object["v2"][2]};
                CreateTriangleFunc createFunc = libLoader.getFunction<CreateTriangleFunc>(libName, "createObject");
                shapes.push_back(createFunc(v0, v1, v2, color, material));
            } else if (type == "Cube") {
                vec3 scale = {object["scale"][0], object["scale"][1], object["scale"][2]};
                vec3 rotation = {object["rotation"][0], object["rotation"][1], object["rotation"][2]};
                double size = object["size"];
                CreateCubeFunc createFunc = libLoader.getFunction<CreateCubeFunc>(libName, "createCube");
                shapes.push_back(createFunc(position, scale, rotation, color, size, material));
            }
        }
    }

    void Engine::loadConfig(const std::string &configFile) {
        libconfig::Config cfg;
        try {
            cfg.readFile(configFile.c_str());
            const libconfig::Setting &root = cfg.getRoot();
            loadLightConfig(root["light"]);
            loadObjectConfig(root["objects"]);
            setupCamera(root["camera"]);
        } catch (const libconfig::FileIOException &fioex) {
            throw ConfigException("Erreur lors de la lecture du fichier de configuration");
        } catch (const libconfig::ParseException &pex) {
            throw ConfigException(
                    "Erreur de syntaxe dans le fichier de configuration à la ligne " +
                    std::to_string(pex.getLine()));
        } catch (const libconfig::SettingNotFoundException &nfex) {
            throw ConfigException("Erreur de configuration : " + std::string(nfex.getPath()));
        }
    }

    void Engine::setupCamera(const libconfig::Setting &camera_s) {
        try {
            const libconfig::Setting &cameraSettings = camera_s[0];

            if (!cameraSettings.exists("position") || !cameraSettings.exists("resolution") ||
                !cameraSettings.exists("rotation") || !cameraSettings.exists("fieldOfView")) {
                std::cerr << "Camera settings are incomplete.\n";
                return;
            }

            const libconfig::Setting &positionSetting = cameraSettings["position"];
            const libconfig::Setting &resolutionSetting = cameraSettings["resolution"];
            const libconfig::Setting &fieldOfViewSetting = cameraSettings["fieldOfView"];

            double posX, posY, posZ;
            if (!positionSetting.lookupValue("x", posX) ||
                !positionSetting.lookupValue("y", posY) ||
                !positionSetting.lookupValue("z", posZ)) {
                std::cerr << "Position settings must be numeric.\n";
                return;
            }

            camera.cameraCenter = point3(posX, posY, posZ);
            camera.fieldOfView = fieldOfViewSetting;

            if (!resolutionSetting.isGroup()) {
                std::cerr << "Resolution setting must be a group.\n";
                return;
            }
            camera.imageWidth = resolutionSetting["width"];
            camera.imageHeight = resolutionSetting["height"];
            camera.aspectRatio = camera.imageWidth / camera.imageHeight;
            camera.calculateViewport();
            window.create(sf::VideoMode(camera.imageWidth, camera.imageHeight), "SFML Raytracer");
            pixels = sf::VertexArray(sf::Points, camera.imageWidth * camera.imageHeight);
            window.setFramerateLimit(60);
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Missing a required setting: " << nfex.getPath() << std::endl;
        } catch (const libconfig::SettingTypeException &tex) {
            std::cerr << "Type mismatch in the configuration settings: " << tex.getPath() << std::endl;
        }
    }

    Color Engine::rayTrace(const Ray &ray, int depth) {
        if (depth <= 0)
            return Color(0, 0, 0);

        Color pixelColor = backgroundColor;
        double nearest_t = std::numeric_limits<double>::infinity();
        Interval ray_t(0.001, std::numeric_limits<double>::infinity());

        for (const auto &shape: shapes) {
            double t_hit;
            vec3 hit_normal;
            Color hit_color;
            HitMat rec;
            Ray scattered;
            Color attenuation;

            if (shape->hit(ray, ray_t, t_hit, hit_normal, hit_color, rec) && t_hit < nearest_t && t_hit > 0.0001) {
                nearest_t = t_hit;
                vec3 hit_point = ray.at(t_hit);
                pixelColor = backgroundColor;
                if (rec.mat_ptr && rec.mat_ptr->scatter(ray, rec, attenuation, scattered)) {
                    pixelColor += attenuation * rayTrace(scattered, depth - 1);
                }
                for (const auto &light: lights) {
                    vec3 light_direction = light->getDirection(hit_point);
                    light_direction = unit_vector(light_direction);
                    bool shadowed = false;
                    Ray shadow_ray(hit_point + hit_normal * 0.001,
                                   light_direction);
                    for (const auto &blocker: shapes) {
                        if (blocker.get() != shape.get() &&
                            blocker->hit(shadow_ray, ray_t, t_hit, hit_normal, hit_color, rec)) {
                            shadowed = true;
                            break;
                        }
                    }
                    if (!shadowed) {
                        double diffuse_light_intensity = std::max(dot(hit_normal, light_direction), 0.0);
                        Color light_intensity = light->getIntensity(hit_point);
                        pixelColor += hit_color * light_intensity * diffuse_light_intensity;
                    }
                }
            }
        }
        pixelColor.e[0] = std::min(pixelColor.e[0], 1.0);
        pixelColor.e[1] = std::min(pixelColor.e[1], 1.0);
        pixelColor.e[2] = std::min(pixelColor.e[2], 1.0);
        return pixelColor;
    }


    void Engine::run() {
        while (window.isOpen()) {
            if (checkConfigChanged()) {
                std::cout << "Configuration file has changed. Reloading and restarting rendering..." << std::endl;
                reloadConfig();
            }
            render();
            processEvents();
        }
        saveToPPM(outputFileName);
    }

    void Engine::processEvents() {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                bool needRerender = false;

                switch (event.key.code) {
                    case sf::Keyboard::Z:
                        camera.cameraCenter += vec3(0, 0, -0.1);
                        needRerender = true;
                        break;
                    case sf::Keyboard::S:
                        camera.cameraCenter += vec3(0, 0, 0.1);
                        needRerender = true;
                        break;
                    case sf::Keyboard::Q:
                        camera.cameraCenter += vec3(-0.1, 0, 0);
                        needRerender = true;
                        break;
                    case sf::Keyboard::D:
                        camera.cameraCenter += vec3(0.1, 0, 0);
                        needRerender = true;
                        break;
                    case sf::Keyboard::B:
                        camera.fieldOfView += 1.0;
                        if (camera.fieldOfView > 120) camera.fieldOfView = 120;
                        needRerender = true;
                        break;
                    case sf::Keyboard::N:
                        camera.fieldOfView -= 1.0;
                        if (camera.fieldOfView < 1) camera.fieldOfView = 1;
                        needRerender = true;
                        break;
                    default:
                        break;
                }
                if (needRerender) {
                    camera.calculateViewport();
                    render();
                }
            }
        }
    }


    void Engine::render2(int i, int j, Color *pixelColor) {
        for (int s = 0; s < samples_per_pixel; ++s) {
            float u = (i + ((float) 1.0 / RAND_MAX)) / (camera.imageWidth - 1);
            float v = (j + ((float) 1.0 / RAND_MAX)) / (camera.imageHeight - 1);
            vec3 rayDirection = camera.viewportUpperLeft + (camera.viewportU * u) +
                                (camera.viewportV * v) - camera.cameraCenter;
            rayDirection = unit_vector(rayDirection);
            Ray ray(camera.cameraCenter, rayDirection);
            *pixelColor += rayTrace(ray, 5);
        }
    }

    void Engine::renderPixel(int start, int end) {
        for (int index = start; index < end; ++index) {
            int i = index % camera.imageWidth;
            int j = index / camera.imageWidth;
            if (i < 0 || i >= camera.imageWidth || j < 0 || j >= camera.imageHeight) {
                continue;
            }
            Color pixelColor(0, 0, 0);
            render2(i, j, &pixelColor);
            pixelColor.e[0] = std::clamp(pixelColor.e[0], 0.0, 1.0);
            pixelColor.e[1] = std::clamp(pixelColor.e[1], 0.0, 1.0);
            pixelColor.e[2] = std::clamp(pixelColor.e[2], 0.0, 1.0);
            unsigned int pixelIndex = i + j * camera.imageWidth;
            if (pixelIndex < pixels.getVertexCount()) {
                pixels[pixelIndex].position = sf::Vector2f(static_cast<float>(i), static_cast<float>(j));
                pixels[pixelIndex].color = sf::Color(
                    static_cast<int>(pixelColor.e[0] * 255),
                    static_cast<int>(pixelColor.e[1] * 255),
                    static_cast<int>(pixelColor.e[2] * 255)
                );
            }
        }
    }

    void Engine::render() {
        unsigned int num_threads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads(num_threads);
        const unsigned int total_pixels = 10000;
        const unsigned int pixels_per_thread = total_pixels / num_threads;

        for (unsigned int t = 0; t < num_threads; ++t) {
            unsigned int start = lastRenderedPixelIndex + t * pixels_per_thread;
            unsigned int end = start + pixels_per_thread;
            if (t == num_threads - 1) {
                end = lastRenderedPixelIndex + total_pixels;
            }
            threads[t] = std::thread(&Engine::renderPixel, this, start, end);
        }
        for (auto &thread: threads)
            thread.join();
        lastRenderedPixelIndex = (lastRenderedPixelIndex + total_pixels) % (camera.imageWidth * camera.imageHeight);
        if (lastRenderedPixelIndex == 0) {
            rendered = true;
        }
        window.clear();
        window.draw(pixels);
        window.display();
    }

    void Engine::saveToPPM(const std::string &filename) {
        std::ofstream outFile(filename);
        outFile << "P3\n" << camera.imageWidth << " " << camera.imageHeight << "\n255\n";
        for (int j = 0; j < camera.imageHeight; ++j) {
            for (int i = 0; i < camera.imageWidth; ++i) {
                sf::Color col = pixels[i + j * camera.imageWidth].color;
                outFile << static_cast<int>(col.r) << " "
                        << static_cast<int>(col.g) << " "
                        << static_cast<int>(col.b) << "\n";
            }
        }
        outFile.close();
    }
}
