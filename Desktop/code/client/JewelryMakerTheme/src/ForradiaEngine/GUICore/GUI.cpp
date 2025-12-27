/*********************************************************************
 * Copyright 2025 Andreas Åkerberg                                   *
 * This code is licensed under MIT license (see LICENSE for details) *
 *********************************************************************/

/* Includes */ // clang-format off
    #include "GUI.hpp"
    
    #include <ranges>
// clang-format on

namespace ForradiaEngine
{
    auto GUI::mouseHoveringGUI() const -> bool
    {
        if (!dynamic_cast<const GUIComponent *>(this)->getVisible())
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
