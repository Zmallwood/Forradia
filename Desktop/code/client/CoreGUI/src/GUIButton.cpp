/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUIButton.hpp"
#include "Cursor.hpp"
#include "MouseUtilities.hpp"
#include "SDLDevice.hpp"
#include "Singleton.hpp"
#include "TextRenderer.hpp"

namespace Forradia {
  auto GUIButton::OnMouseDown(Uint8 mouseButton) -> bool {
    if (!dynamic_cast<const GUIComponent *>(this)->GetVisible())
      return false;

    auto mousePos{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};
    if (GetBounds().Contains(mousePos)) {
      m_action();
      return true;
    }

    return false;
  }

  auto GUIButton::UpdateDerived() -> void {
    dynamic_cast<GUIComponent *>(this)->GUIPanel::UpdateDerived();

    auto mousePosition{GetNormallizedMousePosition(_<SDLDevice>().GetWindow())};
    auto hovered{GetBounds().Contains(mousePosition)};

    if (hovered) {
      this->SetBackgroundImage(m_hoveredBackgroundImage);
      _<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);
      //      if (_<MouseInput>().GetLeftMouseButtonRef().HasBeenFiredPickResult())
      //        m_action();
    } else {
      SetBackgroundImage(m_backgroundImage);
    }
  }

  auto GUIButton::RenderDerived() const -> void {
    GUIPanel::RenderDerived();

    auto bounds{this->GetBounds()};
    _<TextRenderer>().DrawString(k_renderIDText, m_text, bounds.x + bounds.width / 2,
                                 bounds.y + bounds.height / 2, FontSizes::_20, true);
  }
}
