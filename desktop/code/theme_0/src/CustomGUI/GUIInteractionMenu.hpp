//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUICore/GUIPanel.hpp"

namespace Forradia
{
    namespace Theme0
    {
        class GUIInteractionMenu : public GUIPanel
        {
          public:
            GUIInteractionMenu()
                : GUIPanel(0.0f, 0.0f, 0.2f, 0.14f)
            {
                Initialize();
            }

            void BuildMenu();

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
                GUIInteractionMenuEntry(
                    StringView label,
                    Function<void()> action)
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

            Vector<GUIInteractionMenuEntry> m_entries;

            Point m_clickedCoordinate{-1, -1};
        };
    }
}