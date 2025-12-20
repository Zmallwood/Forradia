/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUI.hpp"
#include <ranges>

namespace Forradia {
    auto GUI::MouseHoveringGUI() const -> bool {
        if (!dynamic_cast<const GUIComponent *>(this)->GetVisible())
            return false;

        auto result{false};

        auto childComponents{this->GetChildComponents()};

        // for (auto it = childComponents.rbegin(); it != childComponents.rend(); ++it)
        for (auto &childComponent : std::ranges::reverse_view(childComponents))
            result |= childComponent->MouseHoveringGUI();

        return result;
    }
}
