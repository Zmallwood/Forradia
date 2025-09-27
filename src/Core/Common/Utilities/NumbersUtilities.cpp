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
}