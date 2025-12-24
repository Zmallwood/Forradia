/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    class GUILabel;
}

namespace Forradia::Theme0
{
    /**
     *  Represents the player status box.
     */
    class GUIPlayerStatusBox : public GUIPanel
    {
      public:
        /**
         *  Constructor.
         */
        GUIPlayerStatusBox() : GUIPanel("GUIPlayerStatusBox", 0.0f, 0.0f, 0.2f, 0.14f)
        {
            this->initialize();
        }

      protected:
        /**
         *  Initializes the player status box.
         */
        auto initialize() -> void;

        /**
         *  Does update logic that is specific to the player status box.
         */
        auto updateDerived() -> void override;

        /**
         *  Does render logic that is specific to the player status box.
         */
        auto renderDerived() const -> void override;

      private:
        const int k_renderIDNameString{hash("GUIPlayerStatusBoxName")};
        const int k_renderLevelString{hash("GUIPlayerStatusBoxLevel")};
        const int k_renderWellBeingString{hash("GUIPlayerStatusBoxWellBeing")};
        const int k_renderWellBeingValueString{hash("GUIPlayerStatusBoxWellBeingValue")};
        std::shared_ptr<GUILabel> m_wellBeingValueTextLabel{};
    };
}
