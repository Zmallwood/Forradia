/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "Aliases.hpp"

namespace Forradia {
/// Print out a string of text, without a following line break.
///
/// @param text Text to print.
auto Print(StringView text) -> void;

/// Print out a string of text, with an added line break at the end.
///
/// @param text Text to print.
auto PrintLine(StringView text) -> void;
}