/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    void RenderTextSurface(SDL_Surface *surface,
                           float x,
                           float y,
                           Size textDimensions,
                           bool centerAlign);
}