/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once
#include "GUIPanel.hpp"

namespace Forradia {
    /**
     * A panel that can be moved by the mouse.
     */
    class GUIMovablePanel : public GUIPanel {
      public:
        /**
         * Constructor.
         *
         * @param uniqueName An unique name for the movable panel.
         * @param x The x-coordinate of the movable panel.
         * @param y The y-coordinate of the movable panel.
         * @param width The width of the movable panel.
         * @param height The height of the movable panel.
         */
        GUIMovablePanel(std::string_view uniqueName, float x, float y, float width, float height)
            : GUIPanel(uniqueName, x, y, width, height) {
        }

        virtual auto OnMouseDown(Uint8 mouseButton) -> bool override;

        virtual auto OnMouseUp(Uint8 mouseButton, int clickSpeed) -> bool override;

      protected:
        /**
         * Update tasks specific to the movable panel, called by the GUIComponent base class.
         */
        auto UpdateDerived() -> void override;

        /**
         * Starts the move of the movable panel.
         */
        auto StartMove() -> void;

        /**
         * Stops the move of the movable panel.
         */
        auto StopMove() -> void;

        /**
         * Gets the draggable area of the movable panel.
         *
         * @return The draggable area of the movable panel.
         */
        virtual auto GetDraggableArea() const -> RectF;

        /**
         * Gets whether the movable panel is being moved.
         *
         * @return Whether the movable panel is being moved.
         */
        auto GetIsBeingMoved() const {
            return m_isBeingMoved;
        }

        /**
         * Gets the starting position of the move of the movable panel.
         *
         * @return The starting position of the move of the movable panel.
         */
        auto GetMoveStartingPosition() const {
            return m_moveStartingPosition;
        }

        /**
         * Gets the starting mouse position of the move of the movable panel.
         *
         * @return The starting mouse position of the move of the movable panel.
         */
        auto GetMoveStartingMousePosition() const {
            return m_moveStartingMousePosition;
        }

      private:
        bool m_isBeingMoved{false};
        PointF m_moveStartingPosition{-1, -1};
        PointF m_moveStartingMousePosition{-1, -1};
    };
}
