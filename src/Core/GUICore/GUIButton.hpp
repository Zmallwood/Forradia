/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    class GUIButton : public GUIPanel
    {
    public:
        GUIButton(float x,
                  float y,
                  float width,
                  float height,
                  StringView text,
                  std::function<void()> action,
                  StringView backgroundImage = k_backgroundImage,
                  StringView hoveredBackgroundImage = k_hoveredBackgroundImage);

    protected:
        virtual void UpdateDerived() override;

        virtual void RenderDerived() const override;

    private:
        inline static const std::string k_backgroundImage{"GUIButtonBackground"};
        inline static const std::string k_hoveredBackgroundImage{"GUIButtonHoveredBackground"};

        std::string m_text;
        std::function<void()> m_action;
        std::string m_backgroundImage;
        std::string m_hoveredBackgroundImage;
    };
}
