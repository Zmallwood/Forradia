//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

// Status: Incomplete.
// TODO:

#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia
{
    class GUILabel;
}

namespace Forradia::Theme0
{
    class GUIQuestPanel : public GUIMovablePanel
    {
      public:
        GUIQuestPanel() : GUIMovablePanel("GUIQuestPanel", 0.8f, 0.2f, 0.2f, 0.14f)
        {
            this->Initialize();
        }

      protected:
        void UpdateDerived() override;

      private:
        void Initialize();

        SharedPtr<GUILabel> m_questTitleTextPanel;

        SharedPtr<GUILabel> m_questNameTextPanel;

        SharedPtr<GUILabel> m_questDescriptionTextPanel;

        SharedPtr<GUILabel> m_questStatusTextPanel;
    };
}