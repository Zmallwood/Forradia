/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "GUIComponent.hpp"

namespace Forradia
{
    class GUIPanel : public GUIComponent
    {
    public:
        GUIPanel(float x,
                 float y,
                 float width,
                 float height,
                 StringView backgroundImage = k_defaultBackgroundImage);

    protected:
        virtual void RenderDerived() const override;

        void SetBackgroundImage(StringView value)
        {
            m_backgroundImage = value;
        }

    private:
        inline static const String k_defaultBackgroundImage{"GUIPanelBackground"};

        String m_backgroundImage;
    };
}
