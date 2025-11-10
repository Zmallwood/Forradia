//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    class GUIWindow;

    class GUIWindowTitleBar : public GUIPanel
    {
      public:
        GUIWindowTitleBar(StringView uniqueName, GUIWindow &parentWindow, StringView windowTitle)
            : m_parentWindow(parentWindow), k_windowTitle(windowTitle),
              k_renderIDWindowTitleText(Hash(uniqueName.data() + String("WindowTitleText"))),
              GUIPanel(uniqueName, 0.0f, 0.0f, 0.0f, 0.0f, "GUIWindowTitleBarBackground")
        {
            Initialize(uniqueName);
        }

        void RenderDerived() const override;

        RectF GetBounds() const override;

      private:
        void Initialize(StringView uniqueName);

        inline static const float k_h{0.04f};

        const String k_windowTitle;

        const int k_renderIDWindowTitleText;

        GUIWindow &m_parentWindow;
    };
}