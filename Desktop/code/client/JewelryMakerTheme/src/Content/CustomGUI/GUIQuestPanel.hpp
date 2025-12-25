/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

/* Includes */ // clang-format off
    #include "ForradiaEngine/GUICore/GUIMovablePanel.hpp"
// clang-format on

namespace Forradia
{
    class GUILabel;
}

namespace Forradia::Theme0
{
    /**
     *  Represents the quest panel.
     */
    class GUIQuestPanel : public GUIMovablePanel
    {
      public:
        /**
         *  Constructor.
         */
        GUIQuestPanel() : GUIMovablePanel("GUIQuestPanel", 0.79f, 0.2f, 0.2f, 0.14f)
        {
            this->initialize();
        }

      protected:
        /**
         *  Does update logic that is specific to the quest panel.
         */
        auto updateDerived() -> void override;

      private:
        auto initialize() -> void;

        std::shared_ptr<GUILabel> m_questTitleTextPanel{};
        std::shared_ptr<GUILabel> m_questNameTextPanel{};
        std::shared_ptr<GUILabel> m_questDescriptionTextPanel{};
        std::shared_ptr<GUILabel> m_questStatusTextPanel{};
    };
}
