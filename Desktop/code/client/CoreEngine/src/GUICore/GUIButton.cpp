/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUIButton.hpp"
#include "MinorComponents/Cursor.hpp"
#include "MouseUtilities.hpp"
#include "GraphicsDevices/SDLDevice.hpp"
#include "Rendering/Text/TextRenderer.hpp"

namespace Forradia
{
    auto GUIButton::onMouseUp(Uint8 mouseButton, int clickSpeed) -> bool
    {
        if (!dynamic_cast<const GUIComponent *>(this)->getVisible())
        {
            return false;
        }

        auto mousePos{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        if (dynamic_cast<const GUIComponent *>(this)->getBounds().contains(mousePos))
        {
            m_action();

            return true;
        }

        return false;
    }

    auto GUIButton::updateDerived() -> void
    {
        dynamic_cast<GUIComponent *>(this)->GUIComponent::updateDerived();

        auto mousePosition{getNormalizedMousePosition(SDLDevice::instance().getWindow())};

        if (dynamic_cast<const GUIComponent *>(this)->getBounds().contains(mousePosition))
        {
            dynamic_cast<GUIPanel *>(this)->setBackgroundImage(m_hoveredBackgroundImage);
            Cursor::instance().setCursorStyle(CursorStyles::HoveringClickableGUI);
        }
        else
        {
            dynamic_cast<GUIPanel *>(this)->setBackgroundImage(m_backgroundImage);
        }
    }

    auto GUIButton::renderDerived() const -> void
    {
        dynamic_cast<const GUIPanel *>(this)->GUIPanel::renderDerived();

        auto bounds{dynamic_cast<const GUIComponent *>(this)->getBounds()};

        TextRenderer::instance().drawString(k_renderIDText, m_text, bounds.x + bounds.width / 2,
                                            bounds.y + bounds.height / 2, FontSizes::_20, true);
    }
}
