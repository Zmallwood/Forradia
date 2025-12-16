/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once

namespace Forradia {
/// Calculate the inverse of the speed.
///
/// @param speed Speed to invert.
/// @return The inverse of the speed.
float InvertSpeed(float speed);

/// Calculate the normalized value.
///
/// @param value Value to normalize.
/// @return The normalized value.
int Normalize(int value);

/// Calculate the ceiled value with a given number of decimal places.
///
/// @param number The value to ceil.
/// @param numDecimalPlaces The number of decimal places.
/// @return The ceiled value.
float Ceil(float number, float numDecimalPlaces);
}