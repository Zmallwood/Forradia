//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia
{
    class GUIWindow : public GUIMovablePanel
    {
      public:
        GUIWindow(float x, float y, float width,
                  float height, StringView windowTitle)
            : GUIMovablePanel(x, y, width, height)
        {
            Initialize(windowTitle);
        }

      protected:
        void RenderDerived() const override;

        RectF GetDragArea() override;

        auto GetGUIWindowTitleBar() const
        {
            return m_guiWindowTitleBar;
        }

      private:
        void Initialize(StringView windowTitle);

        class GUIWindowTitleBar : public GUIPanel
        {
          public:
            GUIWindowTitleBar(GUIWindow &parentWindow,
                              StringView windowTitle)
                : m_parentWindow(parentWindow),
                  k_windowTitle(windowTitle),
                  GUIPanel(0.0f, 0.0f, 0.0f, 0.0f,
                           "gui_win_title_bar_bg")
            {
                Initialize();
            }

            void RenderDerived() const override;

            RectF GetBounds() const override;

          private:
            void Initialize();

            inline static const float k_h{0.04f};

            const String k_windowTitle;

            GUIWindow &m_parentWindow;
        };

        SharedPtr<GUIWindowTitleBar> m_guiWindowTitleBar;
    };
}