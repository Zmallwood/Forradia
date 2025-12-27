/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#pragma once

#include "ForradiaEngine/GUICore/GUIMovablePanel.hpp"

namespace ForradiaEngine
{
    class GUILabel;
}

namespace ForradiaEngine::JewelryMakerTheme
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
        GUIQuestPanel()
            : GUIMovablePanel("GUIQuestPanel", k_bounds.x, k_bounds.y, k_bounds.width,
                              k_bounds.height)
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

        constexpr static RectF k_bounds{0.79F, 0.2F, 0.2F, 0.14F};
        std::shared_ptr<GUILabel> m_questTitleTextPanel{};
        std::shared_ptr<GUILabel> m_questNameTextPanel{};
        std::shared_ptr<GUILabel> m_questDescriptionTextPanel{};
        std::shared_ptr<GUILabel> m_questStatusTextPanel{};
    };
}
