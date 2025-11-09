//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIPanel.hpp"

namespace Forradia::Theme0
{
    class Robot;

    class GUIInteractionMenu : public GUIPanel
    {
      public:
        GUIInteractionMenu() : GUIPanel("GUIInteractionMenu", 0.0f, 0.0f, 0.2f, 0.14f)
        {
            Initialize();
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

      protected:
        void Initialize();

        virtual void UpdateDerived() override;

        virtual void RenderDerived() const override;

      private:
        static constexpr float k_indentWidth{0.01f};

        static constexpr float k_lineHeight{0.025f};

        class GUIInteractionMenuEntry
        {
          public:
            GUIInteractionMenuEntry(StringView label, Function<void()> action)
                : m_label(label), m_action(action)
            {
            }

            auto GetLabel() const
            {
                return m_label;
            }

            auto GetAction() const
            {
                return m_action;
            }

          private:
            String m_label;

            Function<void()> m_action;
        };

        const int k_renderIDActionsString{Hash("GUIInteractionMenuActionsString")};

        const int k_maxNumMenuEntries{40};

        Vector<int> m_renderIDsMenuEntryStrings;

        Vector<GUIInteractionMenuEntry> m_entries;

        Point m_clickedCoordinate{-1, -1};

        SharedPtr<Robot> m_clickedRobot;

        std::map<int, int> m_timedActions;
    };
}