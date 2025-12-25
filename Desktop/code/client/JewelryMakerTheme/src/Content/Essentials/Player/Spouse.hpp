/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

namespace ForradiaEngine::Theme0
{
    /**
     *  Represents the spouse of the player.
     */
    class Spouse
    {
      public:
        bool isPlaced() const;

      private:
        Point m_position{-1, -1};
    };
}