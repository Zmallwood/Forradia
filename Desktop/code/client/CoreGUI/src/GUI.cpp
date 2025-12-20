/* Copyright 2025 Andreas Åkerberg
 * This code is licensed under MIT license (see LICENSE for details) */

#include "GUI.hpp"

namespace Forradia {
  auto GUI::MouseHoveringGUI() const -> bool {
    if (!dynamic_cast<const GUIComponent *>(this)->GetVisible())
      return false;

    auto result{false};

    auto childComponents{this->GetChildComponents()};

    for (auto it = childComponents.rbegin(); it != childComponents.rend(); ++it)
      result |= (*it)->MouseHoveringGUI();

    return result;
  }
}
