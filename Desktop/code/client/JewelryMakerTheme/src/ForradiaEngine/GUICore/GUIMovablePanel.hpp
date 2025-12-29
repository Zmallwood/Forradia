/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIPanel.hpp"

namespace ForradiaEngine
{
    /**
     *  A panel that can be moved by the mouse.
     */
    class GUIMovablePanel : public GUIPanel
    {
      public:
        /**
         *  Constructor.
         *
         *  @param uniqueName A unique name for the movable panel.
         *  @param xPos The x-coordinate of the movable panel.
         *  @param yPos The y-coordinate of the movable panel.
         *  @param width The width of the movable panel.
         *  @param height The height of the movable panel.
         */
        GUIMovablePanel(std::string_view uniqueName, float xPos, float yPos, float width,
                        float height)
            : GUIPanel(uniqueName, xPos, yPos, width, height)
        {
        }

        /**
         *  Handles the mouse down event.
         *
         *  @param mouseButton The mouse button that was pressed.
         *  @return True if the mouse down event was handled, false otherwise.
         */
        auto onMouseDown(Uint8 mouseButton) -> bool override;

        /**
         *  Handles the mouse up event.
         *
         *  @param mouseButton The mouse button that was released.
         *  @param clickSpeed The speed of the click.
         *  @return True if the mouse up event was handled, false otherwise.
         */
        auto onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool override;

      protected:
        /**
         *  Update tasks specific to the movable panel, called by the GUIComponent base class.
         */
        auto updateDerived() -> void override;

        /**
         *  Starts the move of the movable panel.
         */
        auto startMove() -> void;

        /**
         *  Stops the move of the movable panel.
         */
        auto stopMove() -> void;

        /**
         *  Gets the draggable area of the movable panel.
         *
         *  @return The draggable area of the movable panel.
         */
        virtual auto getDraggableArea() const -> RectF;

        /**
         *  Gets whether the movable panel is being moved.
         *
         *  @return Whether the movable panel is being moved.
         */
        auto getIsBeingMoved() const
        {
            return m_isBeingMoved;
        }

        /**
         *  Gets the starting position of the move of the movable panel.
         *
         *  @return The starting position of the move of the movable panel.
         */
        auto getMoveStartingPosition() const
        {
            return m_moveStartingPosition;
        }

        /**
         *  Gets the starting mouse position of the move of the movable panel.
         *
         *  @return The starting mouse position of the move of the movable panel.
         */
        auto getMoveStartingMousePosition() const
        {
            return m_moveStartingMousePosition;
        }

      private:
        bool m_isBeingMoved{false};
        PointF m_moveStartingPosition{-1, -1};
        PointF m_moveStartingMousePosition{-1, -1};
    };
}
