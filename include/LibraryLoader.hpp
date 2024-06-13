/*
** EPITECH PROJECT, 2024
** B-OOP-400-LIL-4-1-raytracer-theo.lemaire
** File description:
** color.h
*/

#pragma once

#include <dlfcn.h>
#include <iostream>
#include <string>
#include <unordered_map>

namespace Raytracer {
    class LibraryLoader {
    private:
        std::unordered_map<std::string, void*> handles;

    public:
        LibraryLoader() {}

        ~LibraryLoader() {
            for (auto& handle : handles) {
                if (handle.second) {
                    dlclose(handle.second);
                }
            }
        }

        bool loadLibrary(const std::string &libraryPath) {
            if (handles.find(libraryPath) != handles.end()) {
                return true;
            }

            void *handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
            if (!handle) {
                std::cerr << "Cannot load library: " << dlerror() << '\n';
                return false;
            }

            dlerror();

            handles[libraryPath] = handle;
            return true;
        }

        template<typename Func>
        Func getFunction(const std::string &libraryPath, const std::string &funcName) {
            if (!loadLibrary(libraryPath)) {
                return nullptr;
            }

            void *funcPtr = dlsym(handles[libraryPath], funcName.c_str());
            const char *error = dlerror();
            if (error) {
                std::cerr << "Cannot load symbol '" << funcName << "': " << error << '\n';
                return nullptr;
            }
            return reinterpret_cast<Func>(funcPtr);
        }
    };
}
