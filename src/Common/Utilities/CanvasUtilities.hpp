/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    Size GetCanvasSize();

    float CalculateAspectRatio();

    float ConvertWidthToHeight(float width);

    float ConvertHeightToWidth(float height);
}