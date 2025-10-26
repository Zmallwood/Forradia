//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIButton.hpp"

#include "SDLDevice.hpp"

#include "MinorComponents/Cursor.hpp"

#include "Input/Mouse/MouseInput.hpp"

#include "Rendering.hpp"

namespace Forradia
{
    void GUIButton::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        auto mousePosition{GetNormallizedMousePosition(
            _<SDLDevice>().GetWindow())};

        auto hovered{GetBounds().Contains(mousePosition)};

        if (hovered)
        {
            this->SetBackgroundImage(
                m_hoveredBackgroundImage);

            _<Cursor>().SetCursorStyle(
                CursorStyles::HoveringClickableGUI);

            if (_<MouseInput>()
                    .GetLeftMouseButtonRef()
                    .HasBeenFiredPickResult())
            {
                m_action();
            }
        }
        else
        {
            SetBackgroundImage(m_backgroundImage);
        }
    }

    void GUIButton::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        auto bounds{this->GetBounds()};

        _<TextRenderer>().DrawString(
            m_text, bounds.x + bounds.width / 2,
            bounds.y + bounds.height / 2, FontSizes::_20,
            true);
    }
}