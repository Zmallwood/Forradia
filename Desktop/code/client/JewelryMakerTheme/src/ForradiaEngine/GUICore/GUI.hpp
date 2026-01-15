/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIComponent.hpp"

namespace ForradiaEngine
{
    /**
     *  The root GUI class which is created for every scene.
     */
    class GUI : public GUIComponent
    {
      public:
        /**
         *  Constructor.
         */
        GUI() : GUIComponent(0.0F, 0.0F, 1.0F, 1.0F)
        {
        }

        /**
         *  Checks if the mouse is hovering over any component in the GUI.
         *
         *  @return True if the mouse is hovering over any component in the GUI, false otherwise.
         */
        [[nodiscard]] auto mouseHoveringGUI() const -> bool override;
    };
}
