/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace ForradiaEngine
{
    /**
     *  Randomize the seed.
     */
    auto randomize() -> void;

    /**
     *  Generate a random integer.
     *
     *  @param upperLimit Upper limit.
     *  @return Random integer.
     */
    auto getRandomInt(int upperLimit) -> int;
}
