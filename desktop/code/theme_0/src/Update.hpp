/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "Common.hpp"

namespace Forradia
{
#define _HIDE_FROM_OUTLINER_UPDATE_TOP_1_                                      \
    namespace Theme0                                                           \
    {
    _HIDE_FROM_OUTLINER_UPDATE_TOP_1_
#define _HIDE_FROM_OUTLINER_UPDATE_TOP_2_                                      \
    namespace GameplayCore                                                     \
    {
    _HIDE_FROM_OUTLINER_UPDATE_TOP_2_
    void UpdateKeyboardActions();

    void UpdateMouseActions();

    void UpdateKeyboardMovement();

    void UpdateMouseMovement();

    void UpdateCreaturesMovement();

    void UpdateNPCs();

    class TileHovering
    {
      public:
        void Update();

        auto GetHoveredCoordinate() const
        {
            return m_hoveredCoordinate;
        }

      private:
        Point m_hoveredCoordinate{-1, -1};
    };
#define _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_1_ }
    _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_1_
#define _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_2_ }
    _HIDE_FROM_OUTLINER_UPDATE_BOTTOM_2_
}