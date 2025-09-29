/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "NumbersUtilities.hpp"

namespace Forradia
{
    float InvertMovementSpeed(float number)
    {
        if (number)
        {
            return k_oneSecondMillis / number;
        }
        else
        {
            return 0.0f;
        }
    }

    int Normalize(int value)
    {
        auto absValue{std::abs(value)};

        auto normalized{0};

        if (value)
        {
            normalized = value / absValue;
        }

        return normalized;
    }

    float Ceil(float number, float k)
    {
        auto p{std::pow(10.0, k)};

        return std::ceil(number * p) / p;
    }
}