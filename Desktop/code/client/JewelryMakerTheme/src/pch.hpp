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
#include <functional>
#include <ranges>
#include <numbers>
#include <cmath>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/projection.hpp>

#include "ForradiaEngine/Common/Utilities.hpp"
#include "ForradiaEngine/Common/Matter/Geometry.hpp"
#include "ForradiaEngine/Common/Matter/Coloring.hpp"
#include "ForradiaEngine/Common/General.hpp"