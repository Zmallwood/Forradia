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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/projection.hpp>

#include "Common/Utilities/CanvasUtilities.hpp"
#include "Common/Matter/Geometry/Point.hpp"
#include "Common/General/Hash.hpp"
#include "Common/Utilities/MouseUtilities.hpp"
#include "Common/Utilities/NumbersUtilities.hpp"
#include "Common/Utilities/RandomizationUtilities.hpp"
#include "Common/Utilities/TimeUtilities.hpp"