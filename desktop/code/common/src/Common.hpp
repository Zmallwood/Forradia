//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "Aliases.hpp"
#include "Matter/Geometry/PointF.hpp"
#include "Matter/Geometry/Size.hpp"

struct SDL_Window;
typedef uint8_t Uint8;

namespace Forradia
{
    String GetFileExtension(StringView path);

    String GetFileNameNoExtension(StringView path);

    PointF GetNormallizedMousePosition(
        SharedPtr<SDL_Window> window);

    float InvertMovementSpeed(float movementSpeed);

    int Normalize(int value);

    float Ceil(float number, float k);

    void Randomize();

    int GetRandomInt(int upperLimit);

    String Replace(StringView text, char replace,
                   char replaceWith);

    int GetTicks();

    ///
    /// Compute hash code from a given input text, which
    /// gets computed the same every game start.
    ///
    /// @param text Text to compute hash code for.
    /// @return Computed hash code.
    ///
    int Hash(StringView text);

    ///
    /// Print out a string of text, without a following line
    /// break.
    ///
    /// @param text Text to print.
    ///
    void Print(StringView text);

    ///
    /// Print out a string of text, with an added line break
    /// at the end.
    ///
    /// @param text Text to print.
    ///
    void PrintLine(StringView text);
}