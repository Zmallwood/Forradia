//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include <SDL2/SDL.h>

#include <glm/gtx/transform.hpp>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

#include "Aliases.hpp"
#include "Functions.hpp"
#include "SDLDeleter.hpp"
#include "Constants.hpp"
#include "Singleton.hpp"
#include "Geometry/Point3F.hpp"
#include "Geometry/RectF.hpp"
#include "Coloring/Color.hpp"
#include "Coloring/Colors.hpp"
#include "CanvasUtilities.hpp"
#include "FilePathUtilities.hpp"
#include "MouseUtilities.hpp"
#include "RandomizationUtilities.hpp"
#include "StringUtilities.hpp"
#include "TimeUtilities.hpp"
#include "HashUtilities.hpp"
#include "MessageUtilities.hpp"
#include "Geometry/GLMTypes/GLMMesh.hpp"