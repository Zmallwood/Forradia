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

#include "core/common/aliases.hpp"

#include "core/common/matter.hpp"
#include "core/common/colors.hpp"

#include "core/common/constants.hpp"
#include "core/common/singleton.hpp"
#include "core/common/sdl_deleter.hpp"
#include "core/common/utilities/cast_utilities.hpp"
#include "core/common/utilities/randomize_utilities.hpp"
#include "core/common/utilities/string_utilities.hpp"
#include "core/common/utilities/file_path_utilities.hpp"
#include "core/common/utilities/canvas_utilities.hpp"
#include "core/common/utilities/canvas_convert_utilities.hpp"
#include "core/common/utilities/time_utilities.hpp"
#include "core/common/utilities/numbers_utilities.hpp"
#include "core/common/utilities/mouse_utilities.hpp"
#include "core/common/hash.hpp"
#include "core/common/print.hpp"
