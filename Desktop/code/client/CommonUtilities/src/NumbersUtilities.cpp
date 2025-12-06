//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "NumbersUtilities.hpp"
#include "Constants.hpp"

namespace Forradia
{
    float InvertSpeed(float speed)
    {
        // Calculate the inverse of the movement speed.

        if (speed)
        {
            // If the movement speed is not zero, invert it and return.

            return k_oneSecMillis / speed;
        }
        else
        {
            // If the movement speed is zero, avoid division by zero and return zero directly
            // instead.

            return 0.0f;
        }
    }

    int Normalize(int value)
    {
        // Calculate the absolute value.

        auto absValue{std::abs(value)};

        auto normalized{0};

        // Calculate the normalized value.

        if (value)
        {
            normalized = value / absValue;
        }

        return normalized;
    }

    float Ceil(float number, float numDecimalPlaces)
    {
        // Calculate the ceiled value with a given number of decimal places.

        auto p{std::pow(10.0, numDecimalPlaces)};

        return std::ceil(number * p) / p;
    }
}