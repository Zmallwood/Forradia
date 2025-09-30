/*
 * Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details)
 */

#include "GUIButton.hpp"
#include "core/cursor/Cursor.hpp"
#include "core/input/mouse/MouseInput.hpp"
#include "core/rendering/text/TextRenderer.hpp"

namespace Forradia {
  void GUIButton::UpdateDerived() {
    GUIPanel::UpdateDerived();

    auto mousePosition{GetNormalizedMousePosition()};

    auto isHovered{GetBounds().Contains(mousePosition)};

    if (isHovered) {
      SetBackgroundImage(m_hoveredBackgroundImage);

      GetSingleton<Cursor>().SetCursorStyle(CursorStyles::HoveringClickableGUI);

      if (GetSingleton<MouseInput>()
              .GetLeftMouseButtonRef()
              .GetHasBeenFiredPickResult()) {
        m_action();
      }
    } else {
      SetBackgroundImage(m_backgroundImage);
    }
  }

  void GUIButton::RenderDerived() const {
    GUIPanel::RenderDerived();

    auto bounds{GetBounds()};

    GetSingleton<TextRenderer>().DrawString(m_text, bounds.x + bounds.width / 2,
                                            bounds.y + bounds.height / 2,
                                            FontSizes::_20, true);
  }
}
