//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    class GUIMovablePanel : public GUIPanel
    {
      public:
        GUIMovablePanel(StringView uniqueName, float x,
                        float y, float width, float height)
            : GUIPanel(uniqueName, x, y, width, height)
        {
        }

      protected:
        void UpdateDerived() override;

        void StartMove();

        void StopMove();

        virtual RectF GetDragArea();

        auto GetIsBeingMoved() const
        {
            return m_isBeingMoved;
        }

        auto GetMoveStartingPosition() const
        {
            return m_moveStartingPosition;
        }

        auto GetMoveStartingMousePosition() const
        {
            return m_moveStartingMousePosition;
        }

      private:
        bool m_isBeingMoved{false};

        PointF m_moveStartingPosition{-1, -1};

        PointF m_moveStartingMousePosition{-1, -1};
    };
}