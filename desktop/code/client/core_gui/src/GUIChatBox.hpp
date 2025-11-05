//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

#include "GUIPanel.hpp"

namespace Forradia
{
    class GUIChatBox : public GUIPanel
    {
      public:
        GUIChatBox()
            : GUIPanel("ChatBox", 0.0f, 0.8f, 0.4f, 0.2f,
                       k_defaultBackgroundImageDerived)
        {
        }

        void RenderDerived() const override;

        void Print(StringView text);

        void EnableInput();

        void SubmitInput();

        auto GetInputActive() const
        {
            return m_inputActive;
        }

      private:
        constexpr static StringView
            k_defaultBackgroundImageDerived{
                "GUIChatBoxBackground"};

        inline static const float k_lineHeight{0.025f};

        inline static const float k_separatorHeight{0.003f};

        inline static const float k_margin{0.008f};

        const int k_renderIDSeparator{
            Hash("RenderIDSeparator")};

        const int k_renderIDInputCursor{
            Hash("RenderIDInputCursor")};

        Vector<String> m_lines;

        String m_input;

        bool m_inputActive{false};
    };
}