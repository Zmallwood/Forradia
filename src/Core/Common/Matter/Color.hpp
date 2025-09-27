/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class Color
    {
    public:
        SDL_Color ToSDLColor() const;

        float r{0.0f};
        float g{0.0f};
        float b{0.0f};
        float a{0.0f};
    };
}