/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <set>
#include <filesystem>
#include <algorithm>
#include <vector>
#include <functional>
#include <ranges>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <fmt/core.h>

#include "core/common/Aliases.hpp"

#include "core/common/matter/Point.hpp"
#include "core/common/matter/PointF.hpp"
#include "core/common/matter/Size.hpp"
#include "core/common/matter/SizeF.hpp"
#include "core/common/matter/RectF.hpp"
#include "core/common/matter/Color.hpp"
#include "core/common/matter/Colors.hpp"

#include "core/common/Constants.hpp"
#include "core/common/Singleton.hpp"
#include "core/common/SDLDeleter.hpp"
#include "core/common/utilities/CastUtilities.hpp"
#include "core/common/utilities/RandomizeUtilities.hpp"
#include "core/common/utilities/StringUtilities.hpp"
#include "core/common/utilities/FilePathUtilities.hpp"
#include "core/common/utilities/CanvasUtilities.hpp"
#include "core/common/utilities/CanvasConvertUtilities.hpp"
#include "core/common/utilities/TimeUtilities.hpp"
#include "core/common/utilities/NumbersUtilities.hpp"
#include "core/common/utilities/MouseUtilities.hpp"
#include "core/common/Hash.hpp"
#include "core/common/Print.hpp"
