/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/GUICore/GUIPanel.hpp"
// clang-format on

namespace ForradiaEngine
{
    class GUILabel;
}

namespace ForradiaEngine::JewelryMakerTheme
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
        constexpr static float k_margin{0.01F};
        constexpr static float k_levelTextLabelY{0.04F};
        constexpr static float k_wellBeingTextLabelY{0.095F};
        std::shared_ptr<GUILabel> m_wellBeingValueTextLabel{};
    };
}
