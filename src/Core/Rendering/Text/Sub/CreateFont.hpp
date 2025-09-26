/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "FontSizes.hpp"

namespace Forradia
{
    std::shared_ptr<TTF_Font> CreateFont(std::string_view fontFilePath,
                                         FontSizes fontSize);
}