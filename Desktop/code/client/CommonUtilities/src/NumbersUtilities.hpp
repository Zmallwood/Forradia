/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace Forradia
{
    /**
        Calculate the inverse of the speed.

        @param speed Speed to invert.
        @return The inverse of the speed.
     */
    auto InvertSpeed(float speed) -> float;

    /**
        Calculate the normalized value.

        @param value Value to normalize.
        @return The normalized value.
     */
    auto Normalize(int value) -> int;

    /**
        Calculate the ceiled value with a given number of decimal places.

        @param number The value to ceil.
        @param numDecimalPlaces The number of decimal places.
        @return The ceiled value.
     */
    auto Ceil(float number, float numDecimalPlaces) -> float;
}
