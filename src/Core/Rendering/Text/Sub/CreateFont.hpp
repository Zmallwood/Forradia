/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "FontSizes.hpp"

namespace Forradia
{
    SharedPtr<TTF_Font> CreateFont(StringView fontFilePath,
                                   FontSizes fontSize);
}