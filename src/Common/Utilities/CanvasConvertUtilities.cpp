/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "CanvasConvertUtilities.hpp"
#include "CanvasUtilities.hpp"

namespace Forradia
{
    float ConvertWidthToHeight(float width)
    {
        return width * CalculateAspectRatio();
    }

    float ConvertHeightToWidth(float height)
    {
        return height / CalculateAspectRatio();
    }
}