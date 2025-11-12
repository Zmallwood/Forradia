//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia
{
    ///
    /// Calculate the inverse of the movement speed.
    ///
    /// @param movementSpeed Movement speed to invert.
    /// @return The inverse of the movement speed.
    ///
    float InvertMovementSpeed(float movementSpeed);

    ///
    /// Calculate the normalized value.
    ///
    /// @param value Value to normalize.
    /// @return The normalized value.
    ///
    int Normalize(int value);

    ///
    /// Calculate the ceiled value with a given number of decimal places.
    ///
    /// @param number The value to ceil.
    /// @param numDecimalPlaces The number of decimal places.
    /// @return The ceiled value.
    ///
    float Ceil(float number, float numDecimalPlaces);
}