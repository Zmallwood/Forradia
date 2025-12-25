/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "NumbersUtilities.hpp"
#include "ForradiaEngine/Common/General/Constants.hpp"
#include <cmath>

namespace Forradia
{
    auto invertSpeed(float speed) -> float
    {
        auto result{0.0F};

        if (speed != 0.0F)
        {
            result = k_oneSecMillis / speed;
        }

        return result;
    }

    auto normalize(int value) -> int
    {
        auto absValue{std::abs(value)};
        auto normalized{0};

        if (value != 0)
        {
            normalized = value / absValue;
        }

        return normalized;
    }

    auto ceil(float number, float numDecimalPlaces) -> float
    {
        const auto powBase{10.0F};

        auto factor{std::pow(powBase, numDecimalPlaces)};

        return std::ceil(number * factor) / factor;
    }
}
