//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#include "GUIButton.hpp"

#include "SDLDevice.hpp"

#include "Cursor.hpp"

#include "Mouse/MouseInput.hpp"

#include "TextRenderer.hpp"

namespace Forradia
{
    void GUIButton::UpdateDerived()
    {
        GUIPanel::UpdateDerived();

        // Get normalized mouse position to compare against
        // GUI bounds.

        auto mousePosition{GetNormallizedMousePosition(
            _<SDLDevice>().GetWindow())};

        // Check if the mouse is hovering this button.

        auto hovered{GetBounds().Contains(mousePosition)};

        if (hovered)
        {
            // Show hovered background when pointer is over
            // the button.

            this->SetBackgroundImage(
                m_hoveredBackgroundImage);

            // Change cursor to indicate the button is
            // clickable.

            _<Cursor>().SetCursorStyle(
                CursorStyles::HoveringClickableGUI);

            // Trigger the assigned action on mouse
            // left-button click.

            if (_<MouseInput>()
                    .GetLeftMouseButtonRef()
                    .HasBeenFiredPickResult())
            {
                m_action();
            }
        }
        else
        {
            // Revert to default background when not
            // hovered.

            SetBackgroundImage(m_backgroundImage);
        }
    }

    void GUIButton::RenderDerived() const
    {
        GUIPanel::RenderDerived();

        // Retrieve current bounds to position the label.

        auto bounds{this->GetBounds()};

        // Draw centered button text using the shared text
        // renderer.

        _<TextRenderer>().DrawString(
            k_renderIDText, m_text,
            bounds.x + bounds.width / 2,
            bounds.y + bounds.height / 2, FontSizes::_20,
            true);
    }
}