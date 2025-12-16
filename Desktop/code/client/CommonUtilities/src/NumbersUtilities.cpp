//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Complete.
// TODO:

#include "NumbersUtilities.hpp"
#include "Constants.hpp"

namespace Forradia {
    float InvertSpeed(float speed) {
        if (speed) {
            return k_oneSecMillis / speed;
        } else {
            return 0.0f;
        }
    }

    int Normalize(int value) {
        auto absValue{std::abs(value)};
        auto normalized{0};
        if (value) {
            normalized = value / absValue;
        }
        return normalized;
    }

    float Ceil(float number, float numDecimalPlaces) {
        auto p{std::pow(10.0, numDecimalPlaces)};
        return std::ceil(number * p) / p;
    }
}