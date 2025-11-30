//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIPanel.hpp"

#include "GUIInteractionMenuEntry.hpp"

namespace AAK
{
    namespace Forradia::Theme0
    {
        class Robot;

        class GUIInteractionMenu : public GUIPanel
        {
          public:
            GUIInteractionMenu() : GUIPanel("GUIInteractionMenu", 0.0f, 0.0f, 0.2f, 0.14f)
            {
                this->Initialize();
            }

            void BuildMenu();

            auto &GetTimedActionsRef()
            {
                return m_timedActions;
            }

            auto GetClickedRobot() const
            {
                return m_clickedRobot;
            }

            auto GetClickedCoordinate() const
            {
                return m_clickedCoordinate;
            }

          protected:
            void Initialize();

            virtual void UpdateDerived() override;

            virtual void RenderDerived() const override;

          private:
            static constexpr float k_indentWidth{0.01f};

            static constexpr float k_lineHeight{0.025f};

            const int k_renderIDActionsString{Hash("GUIInteractionMenuActionsString")};

            const int k_maxNumMenuEntries{40};

            Vector<int> m_renderIDsMenuEntryStrings;

            Vector<GUIInteractionMenuEntry> m_entries;

            Point m_clickedCoordinate{-1, -1};

            SharedPtr<Robot> m_clickedRobot;

            std::map<int, int> m_timedActions;
        };
    }
}