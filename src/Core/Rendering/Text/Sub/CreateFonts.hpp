/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "FontSizes.hpp"

namespace Forradia
{
    std::map<FontSizes, std::shared_ptr<TTF_Font>> CreateFonts(std::vector<FontSizes> fontSizes,
                                                               std::string_view relativeFontPath);
}