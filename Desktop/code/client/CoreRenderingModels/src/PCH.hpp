/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <unordered_map>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/gtx/transform.hpp>
// clang-format off
#include <GL/glew.h>
#include <GL/gl.h>
// clang-format on

#include "CanvasUtilities.hpp"
#include "Geometry/GLMTypes/GLMMesh.hpp"
#include "Geometry/Point3F.hpp"
#include "Hash.hpp"
