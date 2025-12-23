/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIButton.hpp"
#include "Cursor.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"
#include "TextRenderer.hpp"

namespace Forradia
{
    auto GUIButton::OnMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        if (!dynamic_cast<const GUIComponent *>(this)->GetVisible())
        {
            return false;
        }

        auto mousePos{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};

        if (dynamic_cast<const GUIComponent *>(this)->GetBounds().Contains(mousePos))
        {
            m_action();

            return true;
        }

        return false;
    }

    auto GUIButton::UpdateDerived() -> void
    {
        dynamic_cast<GUIComponent *>(this)->GUIComponent::UpdateDerived();

        auto mousePosition{GetNormalizedMousePosition(SDLDevice::Instance().GetWindow())};
        auto hovered{dynamic_cast<const GUIComponent *>(this)->GetBounds().Contains(mousePosition)};

        if (hovered)
        {
            dynamic_cast<GUIPanel *>(this)->SetBackgroundImage(m_hoveredBackgroundImage);
            Cursor::Instance().SetCursorStyle(CursorStyles::HoveringClickableGUI);
        }
        else
        {
            dynamic_cast<GUIPanel *>(this)->SetBackgroundImage(m_backgroundImage);
        }
    }

    auto GUIButton::RenderDerived() const -> void
    {
        dynamic_cast<const GUIPanel *>(this)->GUIPanel::RenderDerived();

        auto bounds{dynamic_cast<const GUIComponent *>(this)->GetBounds()};

        TextRenderer::Instance().DrawString(k_renderIDText, m_text, bounds.x + bounds.width / 2,
                                            bounds.y + bounds.height / 2, FontSizes::_20, true);
    }
}
