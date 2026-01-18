/*********************************************************************
 * Copyright 2026 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

#include "GUI.hpp"
#include <ranges>

namespace ForradiaEngine
{
    auto GUI::mouseHoveringGUI() const -> bool
    {
        If(!dynamic_cast<const GUIComponent *>(this)->getVisible())
        {
            return false;
        }

        auto result{false};

        auto childComponents{this->getChildComponents()};

        for (auto &childComponent : std::ranges::reverse_view(childComponents))
        {
            result |= childComponent->mouseHoveringGUI();
        }

        return result;
    }
}
