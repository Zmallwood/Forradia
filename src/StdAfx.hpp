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

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Common/Matter/Point.hpp"
#include "Common/Matter/PointF.hpp"
#include "Common/Matter/Size.hpp"
#include "Common/Matter/SizeF.hpp"
#include "Common/Matter/Color.hpp"
#include "Common/Matter/Colors.hpp"

#include "Common/Constants.hpp"
#include "Common/Singleton.hpp"
#include "Common/SDLDeleter.hpp"
#include "Common/Utilities/RandomizeUtilities.hpp"
#include "Common/Utilities/StringUtilities.hpp"
#include "Common/Utilities/CanvasUtilities.hpp"
#include "Common/Utilities/TimeUtilities.hpp"
#include "Common/Utilities/NumbersUtilities.hpp"
#include "Common/Utilities/MouseUtilities.hpp"
#include "Common/Hash.hpp"
