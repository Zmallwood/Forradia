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

#include "Core/Common/Aliases.hpp"

#include "Core/Common/Matter/Point.hpp"
#include "Core/Common/Matter/PointF.hpp"
#include "Core/Common/Matter/Size.hpp"
#include "Core/Common/Matter/SizeF.hpp"
#include "Core/Common/Matter/RectF.hpp"
#include "Core/Common/Matter/Color.hpp"
#include "Core/Common/Matter/Colors.hpp"

#include "Core/Common/Constants.hpp"
#include "Core/Common/Singleton.hpp"
#include "Core/Common/SDLDeleter.hpp"
#include "Core/Common/Utilities/CastUtilities.hpp"
#include "Core/Common/Utilities/RandomizeUtilities.hpp"
#include "Core/Common/Utilities/StringUtilities.hpp"
#include "Core/Common/Utilities/FilePathUtilities.hpp"
#include "Core/Common/Utilities/CanvasUtilities.hpp"
#include "Core/Common/Utilities/CanvasConvertUtilities.hpp"
#include "Core/Common/Utilities/TimeUtilities.hpp"
#include "Core/Common/Utilities/NumbersUtilities.hpp"
#include "Core/Common/Utilities/MouseUtilities.hpp"
#include "Core/Common/Hash.hpp"
#include "Core/Common/Print.hpp"
