/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include <string>

namespace ForradiaEngine::JewelryMakerTheme
{
    /**
     *  Gets the name from a hash code, i.e. it reverses the Hash function.
     *
     *  @param hashCode The hash code to get the name from.
     *  @return The name from the hash code.
     */
    auto getNameFromAnyHash(int hashCode) -> std::string;
}
