//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

// Std.

#include <iostream>

#include <map>

#include <filesystem>

// External.

#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

#include <GL/gl.h>

#include "assimp/Importer.hpp"

#include "assimp/postprocess.h"

#include "assimp/scene.h"

// Internal.

#include "Aliases.hpp"

#include "Geometry/Size.hpp"

#include "StringUtilities.hpp"

#include "FilePathUtilities.hpp"

#include "HashUtilities.hpp"

#include "SDLDeleter.hpp"

#include "Geometry/GLMTypes/GLMMesh.hpp"