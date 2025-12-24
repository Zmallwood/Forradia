/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <array>
#include <fstream>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/projection.hpp>
#include <nlohmann/json.hpp>

#include "CanvasUtilities.hpp"
#include "Geometry/Point.hpp"
#include "Hash.hpp"
#include "MouseUtilities.hpp"
#include "NumbersUtilities.hpp"
#include "RandomizationUtilities.hpp"
#include "TimeUtilities.hpp"