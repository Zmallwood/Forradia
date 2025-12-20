/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <filesystem>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "FilePathUtilities.hpp"
#include "Geometry/GLMTypes/GLMMesh.hpp"
#include "Geometry/Size.hpp"
#include "Hash.hpp"
#include "MessageUtilities.hpp"
#include "SDLDeleter.hpp"
#include "StringUtilities.hpp"
