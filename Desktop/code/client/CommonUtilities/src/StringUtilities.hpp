/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#pragma once
#include "Aliases.hpp"

namespace Forradia {
/**
 * Replace all instances of a character in a string with another character.
 *
 * @param text String to replace characters in.
 * @param replace Character to replace.
 * @param replaceWith Character to replace with.
 * @return Replaced string.
 */
auto Replace(StringView text, char replace, char replaceWith) -> String;
}