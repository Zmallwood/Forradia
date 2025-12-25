/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include <string>
// clang-format on

namespace Forradia
{
    /**
     *  Replace all instances of a character in a string with another character.
     *
     *  @param text String to replace characters in.
     *  @param replace Character to replace.
     *  @param replaceWith Character to replace with.
     *  @return Replaced string.
     */
    auto replace(std::string_view text, char replace, char replaceWith) -> std::string;
}
