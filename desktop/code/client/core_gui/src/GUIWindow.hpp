//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIMovablePanel.hpp"

namespace Forradia
{
    class GUIWindowTitleBar;

    class GUIWindow : public GUIMovablePanel
    {
      public:
        GUIWindow(StringView uniqueName, float x, float y, float width, float height,
                  StringView windowTitle)
            : GUIMovablePanel(uniqueName, x, y, width, height)
        {
            this->Initialize(uniqueName.data() + String("WindowTitleBar"), windowTitle);
        }

      protected:
        void RenderDerived() const override;

        RectF GetDraggableArea() override;

        auto GetGUIWindowTitleBar() const
        {
            return m_guiWindowTitleBar;
        }

      private:
        void Initialize(StringView uniqueName, StringView windowTitle);

        SharedPtr<GUIWindowTitleBar> m_guiWindowTitleBar;
    };
}