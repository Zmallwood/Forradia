/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */
#pragma once

#include <algorithm>
#include <filesystem>
#include <fmt/core.h>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <ranges>
#include <set>
#include <string>
#include <vector>

// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
// clang-format on

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
