/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

namespace Forradia
{
    class GUIWindow;

    class GUIWindowTitleBar
    {
    public:
        GUIWindowTitleBar(GUIWindow &parentWindow,
                          StringView windowTitleText)
            : m_parentWindow(parentWindow),
              k_windowTitleText(windowTitleText) {}

        void Render() const;

        RectF GetBounds() const;

    private:
        inline static const float k_height{0.04f};
        const String k_windowTitleText;

        GUIWindow &m_parentWindow;
    };
}