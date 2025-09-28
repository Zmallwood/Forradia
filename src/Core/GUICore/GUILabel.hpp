/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#pragma once

#include "GUIComponent.hpp"

namespace Forradia
{
    class GUILabel : public GUIComponent
    {
    public:
        GUILabel(float x,
                 float y,
                 float width,
                 float height,
                 StringView text)
            : GUIComponent(x, y, width, height),
              m_text(text) {}

    protected:
        virtual void RenderDerived() const override;

    private:
        String m_text;
    };
}
