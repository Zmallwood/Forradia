//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIComponent.hpp"

namespace Forradia
{
    class GUILabel : public GUIComponent
    {
      public:
        GUILabel(StringView uniqueName, float x, float y, float width, float height,
                 StringView text = "", bool centerAlign = false,
                 Color color = Palette::GetColor<Hash("WheatTransparent")>())
            : GUIComponent(x, y, width, height), k_renderIDText(Hash(uniqueName)), m_text(text),
              m_centerAlign(centerAlign), m_color(color)
        {
        }

        void SetText(StringView value)
        {
            m_text = value;
        }

      protected:
        virtual void RenderDerived() const override;

      private:
        const int k_renderIDText;

        String m_text;

        bool m_centerAlign{false};

        Color m_color;
    };
}